#include "helper.h"
#include "../lib/helper.h"
#include "../lib/linkedlist.h"
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

void print_usage() {
  printf("1: Print address book\n");
  printf("2: Add to address book\n");
  printf("3: Add address at position\n");
  printf("4: Find address at position\n");
  printf("5: Find address by field and keyword\n");
  printf("6: Delete address at position\n");
  printf("7: Get address book size\n");
  printf("8: Delete address book\n");
  printf("9: Exit\n\n");
}

int get_user_option() {
  int c;
  printf("Enter your choice: ");
  while (1) {
    if (scanf("%d", &c) == 1 && getchar() == '\n') {
      return c;
    } else {
      printf("Invalid index. Please enter a non-negative integer: ");
      clear_input_buffer();
    }
  }
}

void find_by_index(Node *head) {
  int index = get_user_option();
  Node *temp = find_node_at_index(head, index);
  if (temp != NULL) {
    printf("Address found at position - %d\n", index);
    display_person(temp);
  } else {
    printf("No address found at position - %d\n\n", index);
  }
  return;
}

void find_by_keyword(Node *head) {
  char *field = NULL;
  char *value = malloc((sizeof(char) * BUFFER_SIZE) + 1);
  if (value == NULL) {
    err_n_die("Failed to allocate memory for keyword. Error code: %d", errno);
  }
  struct Node *temp_head = NULL;

  printf("1: Search by name\n");
  printf("2: Search by surname\n");
  printf("3: Search by email\n");
  printf("4: Search by phone number\n");
  printf("5: Exit search\n\n");

  switch (get_user_option()) {
  case 1:
    field = "name";
    break;
  case 2:
    field = "surname";
    break;
  case 3:
    field = "email";
    break;
  case 4:
    field = "phone_number";
    break;
  case 5:
    return;
  default:
    printf("Your selected option doesn't exist\n");
    break;
  }

  GET_INPUT("Enter the search keyword: ", value);

  temp_head = find_node_by_data(head, field, value);

  if (temp_head != NULL) {
    display_list(temp_head);
  } else {
    printf("No address was found by the keyword - %s\n\n", value);
  }
  if (value != NULL) {
    free(value);
  }

  free_linked_list(&temp_head);
}

int read_csv_file(const char *filename, Node **head) {
  FILE *file = fopen(filename, "r");
  if (file == NULL) {
    printf("CSV file '%s' not found. Continuing without it.\n", filename);
    return 2;
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

  return 0;
}
