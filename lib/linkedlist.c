#include "linkedlist.h"
#include <errno.h>
#include <signal.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

extern int stop_loop;

void err_n_die(const char *fmt, ...) {
  int errno_save;
  va_list ap;

  errno_save = errno;

  va_start(ap, fmt);
  vfprintf(stderr, fmt, ap);
  fprintf(stdout, "\n");
  fflush(stdout);

  if (errno_save != 0) {
    fprintf(stdout, "(errno = %d) : %s\n", errno_save, strerror(errno_save));
    fprintf(stdout, "\n");
    fflush(stdout);
  }
  va_end(ap);
  exit(EXIT_FAILURE);
}

void clear_input_buffer() {
  int c;
  while ((c = getchar()) != '\n' && c != EOF) {
    continue;
  }
}

void signal_handler(int signal) {
  if (signal == SIGINT) {
    stop_loop = 1;
    printf("\nCTRL+C received. Exiting...\n");
  }
}

Node *create_node(Person data) {
  Node *new_node = (Node *)malloc(sizeof(Node));
  if (new_node == NULL) {
    err_n_die("Failed to allocate memory for new node. Error code: %d", errno);
  }
  new_node->data = data;
  new_node->next = NULL;
  return new_node;
}

Person create_person_input() {
  Person data;
  GET_INPUT("Enter name: ", name);
  GET_INPUT("Enter surname: ", surname);
  GET_INPUT("Enter email: ", email);
  GET_INPUT("Enter phone number: ", phone_number);

  return data;
}

void handle_user_input(Node **head) {
  int choice;
  Person new_person;
  int index;

  printf("1. Add at head\n");
  printf("2. Add at index\n");
  printf("Enter your choice: ");

  if (scanf("%d", &choice) == 1 && getchar() == '\n') {
    switch (choice) {
    case 1:
      new_person = create_person_input();
      add_node_at_head(head, new_person);
      break;
    case 2:
      printf("Enter index: ");
      while (scanf("%d", &index) != 1 || index < 0) {
        printf("Invalid index. Please enter a non-negative integer: ");
        clear_input_buffer();
      }

      clear_input_buffer();

      new_person = create_person_input();
      add_node_at_index(head, new_person, index);
      break;
    default:
      printf("Invalid choice\n");
    }
  } else {
    printf("Invalid choice. Please enter a non-negative integer.\n");
    clear_input_buffer();
  }
}

void display_nodes(Node *head) {
  Node *curr = head;
  while (curr != NULL) {
    printf("Name: %s\n", curr->data.name);
    printf("Surname: %s\n", curr->data.surname);
    printf("Email: %s\n", curr->data.email);
    printf("Phone Number: %s\n\n", curr->data.phone_number);
    curr = curr->next;
  }
}

void add_node_at_head(Node **head, Person data) {
  Node *new_node = create_node(data);
  new_node->next = *head;
  *head = new_node;
}

void add_node_at_index(Node **head, Person data, int index) {
  if (*head == NULL) {
    return;
  }

  if (index > (get_length(*head) - 1))
    return;

  if (index == 0) {
    add_node_at_head(head, data);
    return;
  }

  Node *new_node = create_node(data);
  Node *curr = *head;
  Node *prev = NULL;

  for (int i = 0; i < index && curr != NULL; i++) {
    prev = curr;
    curr = curr->next;
  }

  prev->next = new_node;
  new_node->next = curr;
}

void delete_node_at_index(Node **head, int index) {
  if (*head == NULL) {
    return;
  }

  if (index > (get_length(*head) - 1))
    return;

  Node *curr = *head;
  Node *prev = NULL;

  if (index == 0) {
    *head = curr->next;
    free(curr);
    return;
  }

  for (int i = 0; i < index && curr != NULL; i++) {
    prev = curr;
    curr = curr->next;
  }

  if (curr == NULL) {
    return;
  }

  prev->next = curr->next;
  free(curr);
}

int get_length(Node *head) {
  int len = 0;
  Node *curr = head;
  while (curr != NULL) {
    len++;
    curr = curr->next;
  }
  return len;
}

void free_linked_list(Node **head) {
  Node *curr = *head;
  Node *next;

  while (curr != NULL) {
    next = curr->next;
    free(curr);
    curr = next;
  }

  *head = NULL;
}

Node *find_node_at_index(Node *head, int index) {
  if (index > (get_length(head) - 1))
    return NULL;

  Node *curr = head;

  for (int i = 0; i < index && curr != NULL; i++) {
    curr = curr->next;
  }
  return curr;
}

Node *find_node_by_data(Node *head, char *field, char *value) {
  Node *curr = head;
  while (curr != NULL) {
    Person data = curr->data;
    if (strcmp(field, "name") == 0 && strcmp(data.name, value) == 0) {
      return curr;
    }
    if (strcmp(field, "surname") == 0 && strcmp(data.surname, value) == 0) {
      return curr;
    }
    if (strcmp(field, "email") == 0 && strcmp(data.email, value) == 0) {
      return curr;
    }
    if (strcmp(field, "phone_number") == 0 &&
        strcmp(data.phone_number, value) == 0) {
      return curr;
    }
    curr = curr->next;
  }
  return NULL;
}

int read_csv_file(const char *filename, Node **head) {
  FILE *file = fopen(filename, "r");
  if (file == NULL) {
    printf("CSV file '%s' not found. Continuing without it.\n", filename);
    return 0;
  }

  char line[MAX_FILE_LINE_LENGTH];
  int line_count = 0;

  while (fgets(line, sizeof(line), file) != NULL && line_count < MAX_PERSONS) {
    if (strcmp(line, "\n") == 0) {
      continue;
    }

    char *ptr = strchr(line, '\n');
    if (ptr) {
      *ptr = '\0';
    }

    char *token;
    char *fields[MAX_CSV_FIELDS];
    int field_count = 0;

    token = strtok(line, ",");
    while (token != NULL && field_count < MAX_CSV_FIELDS) {
      fields[field_count] = token;
      field_count++;
      token = strtok(NULL, ",");
    }

    if (field_count == MAX_CSV_FIELDS) {
      Person p;

      strncpy(p.name, fields[0], sizeof(p.name) - 1);
      p.name[sizeof(p.name) - 1] = '\0';

      strncpy(p.surname, fields[1], sizeof(p.surname) - 1);
      p.surname[sizeof(p.surname) - 1] = '\0';

      strncpy(p.email, fields[2], sizeof(p.email) - 1);
      p.email[sizeof(p.email) - 1] = '\0';

      strncpy(p.phone_number, fields[3], sizeof(p.phone_number) - 1);
      p.phone_number[sizeof(p.phone_number) - 1] = '\0';

      add_node_at_head(head, p);
    }

    line_count++;
  }

  fclose(file);

  if (line_count == 0) {
    printf("No valid entries found in CSV file '%s'.\n", filename);
  } else {
    printf("CSV file '%s' successfully read. %d entries added.\n", filename,
           line_count);
  }

  return 1;
}
