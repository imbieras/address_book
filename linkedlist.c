#include "linkedlist.h"
#include <errno.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

Node *create_node(Person data) {
  Node *new_node = (Node *)malloc(sizeof(Node));
  if (new_node == NULL) {
    err_n_die("Failed to allocate memory for new node. Error code: %d", errno);
  }
  new_node->data = data;
  new_node->next = NULL;
  return new_node;
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
  if (index == 0) {
    add_node_at_head(head, data);
    return;
  }

  Node *new_node = create_node(data);
  Node *curr = *head;

  for (int i = 0; i < index - 1 && curr->next != NULL; i++) {
    curr = curr->next;
  }

  new_node->next = curr->next;
  curr->next = new_node;
}

void delete_node_at_index(Node **head, int index) {
  if (*head == NULL) {
    return;
  }

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
