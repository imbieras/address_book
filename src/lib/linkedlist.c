#include "linkedlist.h"
#include "../helper.h"
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Node *create_node(Person data) {
  Node *new_node = (Node *)malloc(sizeof(Node));
  if (new_node == NULL) {
    err_n_die("Failed to allocate memory for new node. Error code: %d", errno);
  }
  new_node->data = data;
  new_node->next = NULL;
  return new_node;
}

void display_person(Node *node) {
  printf("Name: %s\n", node->data.name);
  printf("Surname: %s\n", node->data.surname);
  printf("Email: %s\n", node->data.email);
  printf("Phone Number: %s\n\n", node->data.phone_number);
}

int display_list(Node *head) {
  Node *curr = head;
  int i = 1;
  int count = 0;

  if (curr == NULL) {
    printf("List is empty\n\n");
    return 0;
  }

  while (curr != NULL) {
    printf("Entry %d -> ", i);
    display_person(curr);
    curr = curr->next;
    i++;
    count++;
  }

  return count;
}

int add_node_at_head(Node **head, Person data) {
  Node *new_node = create_node(data);
  if (new_node == NULL) {
    printf("Unable to create new address\n\n");
    return 1;
  }

  new_node->next = *head;
  *head = new_node;

  return 0;
}

int add_node_at_index(Node **head, Person data, int index) {
  if (*head == NULL) {
    return 1;
  }

  if ((index < 0) || (index > (get_length(*head) - 1))) {
    printf("Index is out of bounds\n\n");
    return 1;
  }

  if (index == 0) {
    return add_node_at_head(head, data);
  }

  Node *new_node = create_node(data);
  if (new_node == NULL) {
    printf("Unable to create new address\n\n");
    return 1;
  }

  Node *curr = *head;
  Node *prev = NULL;

  for (int i = 0; i < index && curr != NULL; i++) {
    prev = curr;
    curr = curr->next;
  }

  prev->next = new_node;
  new_node->next = curr;

  return 0;
}

int delete_node_at_index(Node **head, int index) {
  if (*head == NULL) {
    return 1;
  }

  if ((index < 0) || (index > (get_length(*head) - 1))) {
    printf("Index is out of bounds\n\n");
    return 1;
  }

  Node *curr = *head;
  Node *prev = NULL;

  if (index == 0) {
    *head = curr->next;
    free(curr);
    return 0;
  }

  for (int i = 0; i < index && curr != NULL; i++) {
    prev = curr;
    curr = curr->next;
  }

  if (curr == NULL) {
    return 1;
  }

  prev->next = curr->next;
  free(curr);

  return 0;
}

int get_length(Node *head) {
  if (head == NULL) {
    return 0;
  }

  int len = 0;
  Node *curr = head;
  while (curr != NULL) {
    len++;
    curr = curr->next;
  }
  return len;
}

int free_linked_list(Node **head) {
  if (*head == NULL) {
    return 1;
  }

  Node *curr = *head;
  Node *next;

  while (curr != NULL) {
    next = curr->next;
    free(curr);
    curr = next;
  }

  *head = NULL;

  return 0;
}

Node *copy_node(Node *src) {
  if (src == NULL) {
    return NULL;
  }

  Node *copy = (Node *)malloc(sizeof(Node));
  if (copy == NULL) {
    return NULL;
  }

  strcpy(copy->data.name, src->data.name);
  strcpy(copy->data.surname, src->data.surname);
  strcpy(copy->data.email, src->data.email);
  strcpy(copy->data.phone_number, src->data.phone_number);
  copy->next = NULL;

  return copy;
}

Node *find_node_at_index(Node *head, int index) {
  if (head == NULL) {
    printf("List is empty\n\n");
    return NULL;
  }

  if ((index < 0) || (index > (get_length(head) - 1))) {
    printf("Index is out of bounds\n\n");
    return NULL;
  }

  Node *curr = head;

  for (int i = 0; i < index && curr->next != NULL; i++) {
    curr = curr->next;
  }

  return curr;
}

Node *find_node_by_data(Node *head, char *field, char *value) {
  if (head == NULL || field == NULL || value == NULL) {
    printf("Invalid input: NULL pointer(s)\n\n");
    return NULL;
  }

  if (strcmp(field, "name") != 0 && strcmp(field, "surname") != 0 &&
      strcmp(field, "email") != 0 && strcmp(field, "phone_number") != 0) {
    printf("Invalid field: %s\n\n", field);
    return NULL;
  }

  Node *temp_head = NULL;
  Node *node = NULL;
  Node *curr = head;
  int found = 0;

  while (curr != NULL) {
    Person data = curr->data;
    if (strcmp(field, "name") == 0 && strcmp(data.name, value) == 0) {
      found = 1;
    }
    if (strcmp(field, "surname") == 0 && strcmp(data.surname, value) == 0) {
      found = 1;
    }
    if (strcmp(field, "email") == 0 && strcmp(data.email, value) == 0) {
      found = 1;
    }
    if (strcmp(field, "phone_number") == 0 &&
        strcmp(data.phone_number, value) == 0) {
      found = 1;
    }

    if (found) {
      found = 0;
      node = copy_node(curr);
      if (node != NULL) {
        add_node_at_head(&temp_head, node->data);
        free(node);
      } else {
        free_linked_list(&temp_head);
        return NULL;
      }
    }
    curr = curr->next;
  }

  return temp_head;
}
