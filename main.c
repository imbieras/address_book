#include "linkedlist.h"
#include <errno.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char **argv) {
  Node *head = NULL;

  if (argc != 2) {
    err_n_die("Usage: %s <*.csv>", argv[0]);
  }

  if (!read_csv_file(argv[1], &head)) {
    printf("Failed to read CSV file. Continuing without it.\n");
  }

  Person p1 = {"John", "Doe", "john.doe@example.com", "123456789"};
  Person p2 = {"Jane", "Smith", "jane.smith@example.com", "987654321"};
  Person p3 = {"Alice", "Johnson", "alice.johnson@example.com", "456789123"};

  add_node_at_head(&head, p1);
  add_node_at_head(&head, p2);
  add_node_at_head(&head, p3);

  printf("All Nodes:\n");
  display_nodes(head);

  Person p4 = {"Bob", "Brown", "bob.brown@example.com", "555555555"};
  add_node_at_index(&head, p4, 2);

  printf("After Adding at Index 2:\n");
  display_nodes(head);

  delete_node_at_index(&head, 1);

  printf("After Deleting at Index 1:\n");
  display_nodes(head);

  Node *found_node = find_node_at_index(head, 1);
  if (found_node != NULL) {
    printf("Found Node at Index 1:\n");
    printf("Name: %s\n", found_node->data.name);
    printf("Surname: %s\n", found_node->data.surname);
    printf("Email: %s\n", found_node->data.email);
    printf("Phone Number: %s\n", found_node->data.phone_number);
  }

  Node *found_node_by_email =
      find_node_by_data(head, "email", "john.doe@example.com");
  if (found_node_by_email != NULL) {
    printf("Found Node by Email:\n");
    printf("Name: %s\n", found_node_by_email->data.name);
    printf("Surname: %s\n", found_node_by_email->data.surname);
    printf("Email: %s\n", found_node_by_email->data.email);
    printf("Phone Number: %s\n", found_node_by_email->data.phone_number);
  }

  free_linked_list(&head);

  return 0;
}
