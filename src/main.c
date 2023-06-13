#include "../lib/linkedlist.h"
#include <errno.h>
#include <linux/limits.h>
#include <pwd.h>
#include <signal.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>

#define SEPARATOR_LINE "--------------------------------------------------"
#define PRINT_SEPARATOR() printf("%s\n", SEPARATOR_LINE)

int stop_loop = 0;

int main(void) {
  signal(SIGINT, signal_handler);

  char *homedir;
  if ((homedir = getenv("HOME")) == NULL) {
    homedir = getpwuid(getuid())->pw_dir;
  }

  char *address_file_path = malloc((PATH_MAX * sizeof(char)) + 1);
  if (address_file_path == NULL) {
    err_n_die("Failed to allocate memory for address file path. Error code: %d",
              errno);
  }
  snprintf(address_file_path, PATH_MAX, "%s%s", homedir, "/addresses.csv");

  Node *head = NULL;

  if (!read_csv_file(address_file_path, &head)) {
    printf("Failed to read CSV file. Continuing without it.\n");
  }

  Person p1 = {"Raina", "Arquit", "Raina.Arquit@example.com", "37039559962"};
  Person p2 = {"Briney", "Ardeha", "Briney.Ardeha@example.com", "37013377064"};
  Person p3 = {"Kimmy", "Gilbertson", "Kimmy.Gilbertson@example.com",
               "37061591270"};

  add_node_at_head(&head, p1);
  add_node_at_head(&head, p2);
  add_node_at_head(&head, p3);

  printf("All Nodes:\n");
  display_nodes(head);

  PRINT_SEPARATOR();

  Person p4 = {"Maud", "Gaulin", "Maud.Gaulin@example.com", "37000666859"};
  add_node_at_index(&head, p4, 2);

  printf("After Adding at Index 2:\n");
  display_nodes(head);

  PRINT_SEPARATOR();

  delete_node_at_index(&head, 1);

  printf("After Deleting at Index 1:\n");
  display_nodes(head);

  PRINT_SEPARATOR();

  Node *found_node = find_node_at_index(head, 1);
  if (found_node != NULL) {
    printf("Found Node at Index 1:\n");
    printf("Name: %s\n", found_node->data.name);
    printf("Surname: %s\n", found_node->data.surname);
    printf("Email: %s\n", found_node->data.email);
    printf("Phone Number: %s\n", found_node->data.phone_number);
  }

  PRINT_SEPARATOR();

  Node *found_node_by_email =
      find_node_by_data(head, "email", "Maud.Gaulin@example.com");
  if (found_node_by_email != NULL) {
    printf("Found Node by Email:\n");
    printf("Name: %s\n", found_node_by_email->data.name);
    printf("Surname: %s\n", found_node_by_email->data.surname);
    printf("Email: %s\n", found_node_by_email->data.email);
    printf("Phone Number: %s\n", found_node_by_email->data.phone_number);
  }

  PRINT_SEPARATOR();

  while (!stop_loop) {
    handle_user_input(&head);
    PRINT_SEPARATOR();
    display_nodes(head);
    PRINT_SEPARATOR();
  }

  free(address_file_path);
  free_linked_list(&head);
  return 0;
}
