#include "../helper.h"
#include "linkedlist.h"
#include <stdio.h>
#include <stdlib.h>
#include <unity.h>

int stop_loop = 0;

void setUp(void) {}

void tearDown(void) {}

void test_create_node_single_data(void) {
  Person test_person;
  snprintf(test_person.name, sizeof(test_person.name), "John");
  snprintf(test_person.surname, sizeof(test_person.surname), "Doe");
  snprintf(test_person.email, sizeof(test_person.email),
           "john.doe@example.com");
  snprintf(test_person.phone_number, sizeof(test_person.phone_number),
           "123-456-7890");

  Node *new_node = create_node(test_person);

  TEST_ASSERT_NOT_NULL(new_node);
  TEST_ASSERT_EQUAL_STRING("John", new_node->data.name);
  TEST_ASSERT_EQUAL_STRING("Doe", new_node->data.surname);
  TEST_ASSERT_EQUAL_STRING("john.doe@example.com", new_node->data.email);
  TEST_ASSERT_EQUAL_STRING("123-456-7890", new_node->data.phone_number);

  free(new_node);
}

void test_create_node_empty_data(void) {
  Person test_person;
  test_person.name[0] = '\0';
  test_person.surname[0] = '\0';
  test_person.email[0] = '\0';
  test_person.phone_number[0] = '\0';

  Node *new_node = create_node(test_person);

  TEST_ASSERT_NOT_NULL(new_node);
  TEST_ASSERT_EQUAL_STRING("", new_node->data.name);
  TEST_ASSERT_EQUAL_STRING("", new_node->data.surname);
  TEST_ASSERT_EQUAL_STRING("", new_node->data.email);
  TEST_ASSERT_EQUAL_STRING("", new_node->data.phone_number);

  free(new_node);
}

void test_create_node_long_data(void) {
  Person test_person;
  snprintf(test_person.name, BUFFER_SIZE, "%s",
           "Lorem ipsum dolor sit amet, consectetur adipiscing elit. Morbi "
           "ultrices neque fermentum, volutpat purus fusce.");
  snprintf(test_person.surname, BUFFER_SIZE, "%s",
           "Lorem ipsum dolor sit amet, consectetur adipiscing elit. Morbi "
           "ultrices neque fermentum, volutpat purus fusce.");
  snprintf(test_person.email, BUFFER_SIZE, "%s",
           "Lorem ipsum dolor sit amet, consectetur adipiscing elit. Morbi "
           "ultrices neque fermentum, volutpat purus fusce.");
  snprintf(test_person.phone_number, BUFFER_SIZE, "%s",
           "Lorem ipsum dolor sit amet, consectetur adipiscing elit. Morbi "
           "ultrices neque fermentum, volutpat purus fusce.");

  Node *new_node = create_node(test_person);

  TEST_ASSERT_NOT_NULL(new_node);
  TEST_ASSERT_EQUAL_STRING("Lorem ipsum dolor sit amet, consectetur adipiscing "
                           "elit. Morbi ultrices neque fermentum, volutpat p",
                           new_node->data.name);
  TEST_ASSERT_EQUAL_STRING("Lorem ipsum dolor sit amet, consectetur adipiscing "
                           "elit. Morbi ultrices neque fermentum, volutpat p",
                           new_node->data.surname);
  TEST_ASSERT_EQUAL_STRING("Lorem ipsum dolor sit amet, consectetur adipiscing "
                           "elit. Morbi ultrices neque fermentum, volutpat p",
                           new_node->data.email);
  TEST_ASSERT_EQUAL_STRING("Lorem ipsum dolor sit amet, consectetur adipiscing "
                           "elit. Morbi ultrices neque fermentum, volutpat p",
                           new_node->data.phone_number);

  free(new_node);
}

void test_display_list_empty(void) {
  Node *head = NULL;

  int count = display_list(head);

  TEST_ASSERT_EQUAL_INT(0, count);
}

void test_display_list_single_node(void) {
  Person test_person;
  snprintf(test_person.name, sizeof(test_person.name), "John");
  snprintf(test_person.surname, sizeof(test_person.surname), "Doe");
  snprintf(test_person.email, sizeof(test_person.email),
           "john.doe@example.com");
  snprintf(test_person.phone_number, sizeof(test_person.phone_number),
           "123-456-7890");

  Node *head = create_node(test_person);

  int count = display_list(head);

  TEST_ASSERT_EQUAL_INT(1, count);

  free_linked_list(&head);
}

void test_display_list_multiple_nodes(void) {
  Person test_person1;
  snprintf(test_person1.name, sizeof(test_person1.name), "Alice");
  snprintf(test_person1.surname, sizeof(test_person1.surname), "Smith");
  snprintf(test_person1.email, sizeof(test_person1.email),
           "alice.smith@example.com");
  snprintf(test_person1.phone_number, sizeof(test_person1.phone_number),
           "987-654-3210");

  Person test_person2;
  snprintf(test_person2.name, sizeof(test_person2.name), "Bob");
  snprintf(test_person2.surname, sizeof(test_person2.surname), "Johnson");
  snprintf(test_person2.email, sizeof(test_person2.email),
           "bob.johnson@example.com");
  snprintf(test_person2.phone_number, sizeof(test_person2.phone_number),
           "555-123-4567");

  Node *head = create_node(test_person1);
  add_node_at_head(&head, test_person2);

  int count = display_list(head);

  TEST_ASSERT_EQUAL_INT(2, count);

  free_linked_list(&head);
}

void test_add_node_at_head_single_node(void) {
  Person test_person;
  snprintf(test_person.name, sizeof(test_person.name), "Alice");
  snprintf(test_person.surname, sizeof(test_person.surname), "Smith");
  snprintf(test_person.email, sizeof(test_person.email),
           "alice.smith@example.com");
  snprintf(test_person.phone_number, sizeof(test_person.phone_number),
           "987-654-3210");

  Node *head = NULL;

  int result = add_node_at_head(&head, test_person);

  TEST_ASSERT_EQUAL_INT(0, result);
  TEST_ASSERT_NOT_NULL(head);
  TEST_ASSERT_EQUAL_STRING("Alice", head->data.name);
  TEST_ASSERT_EQUAL_STRING("Smith", head->data.surname);
  TEST_ASSERT_EQUAL_STRING("alice.smith@example.com", head->data.email);
  TEST_ASSERT_EQUAL_STRING("987-654-3210", head->data.phone_number);

  free_linked_list(&head);
}

void test_add_node_at_head_multiple_nodes(void) {
  Person test_person1;
  snprintf(test_person1.name, sizeof(test_person1.name), "Alice");
  snprintf(test_person1.surname, sizeof(test_person1.surname), "Smith");
  snprintf(test_person1.email, sizeof(test_person1.email),
           "alice.smith@example.com");
  snprintf(test_person1.phone_number, sizeof(test_person1.phone_number),
           "987-654-3210");

  Person test_person2;
  snprintf(test_person2.name, sizeof(test_person2.name), "Bob");
  snprintf(test_person2.surname, sizeof(test_person2.surname), "Johnson");
  snprintf(test_person2.email, sizeof(test_person2.email),
           "bob.johnson@example.com");
  snprintf(test_person2.phone_number, sizeof(test_person2.phone_number),
           "555-123-4567");

  Node *head = NULL;

  int result1 = add_node_at_head(&head, test_person1);
  int result2 = add_node_at_head(&head, test_person2);

  TEST_ASSERT_EQUAL_INT(0, result1);
  TEST_ASSERT_EQUAL_INT(0, result2);

  TEST_ASSERT_NOT_NULL(head);
  TEST_ASSERT_EQUAL_STRING("Bob", head->data.name);
  TEST_ASSERT_EQUAL_STRING("Johnson", head->data.surname);
  TEST_ASSERT_EQUAL_STRING("bob.johnson@example.com", head->data.email);
  TEST_ASSERT_EQUAL_STRING("555-123-4567", head->data.phone_number);

  TEST_ASSERT_NOT_NULL(head->next);
  TEST_ASSERT_EQUAL_STRING("Alice", head->next->data.name);
  TEST_ASSERT_EQUAL_STRING("Smith", head->next->data.surname);
  TEST_ASSERT_EQUAL_STRING("alice.smith@example.com", head->next->data.email);
  TEST_ASSERT_EQUAL_STRING("987-654-3210", head->next->data.phone_number);

  free_linked_list(&head);
}

void test_add_node_at_index_empty_list(void) {
  Node *head = NULL;
  Person test_person;
  snprintf(test_person.name, sizeof(test_person.name), "Alice");
  snprintf(test_person.surname, sizeof(test_person.surname), "Smith");
  snprintf(test_person.email, sizeof(test_person.email),
           "alice.smith@example.com");
  snprintf(test_person.phone_number, sizeof(test_person.phone_number),
           "987-654-3210");

  int result = add_node_at_index(&head, test_person, 0);

  TEST_ASSERT_EQUAL_INT(1, result);
  TEST_ASSERT_NULL(head);
}

void test_add_node_at_index_invalid_index(void) {
  Person test_person;
  snprintf(test_person.name, sizeof(test_person.name), "Alice");
  snprintf(test_person.surname, sizeof(test_person.surname), "Smith");
  snprintf(test_person.email, sizeof(test_person.email),
           "alice.smith@example.com");
  snprintf(test_person.phone_number, sizeof(test_person.phone_number),
           "987-654-3210");

  Node *head = create_node(test_person);

  int result = add_node_at_index(&head, test_person, 2);

  TEST_ASSERT_EQUAL_INT(1, result);
  TEST_ASSERT_NOT_NULL(head);
  TEST_ASSERT_NULL(head->next);

  free_linked_list(&head);
}

void test_add_node_at_index_single_node(void) {
  Person test_person1;
  snprintf(test_person1.name, sizeof(test_person1.name), "Alice");
  snprintf(test_person1.surname, sizeof(test_person1.surname), "Smith");
  snprintf(test_person1.email, sizeof(test_person1.email),
           "alice.smith@example.com");
  snprintf(test_person1.phone_number, sizeof(test_person1.phone_number),
           "987-654-3210");

  Person test_person2;
  snprintf(test_person2.name, sizeof(test_person2.name), "Bob");
  snprintf(test_person2.surname, sizeof(test_person2.surname), "Johnson");
  snprintf(test_person2.email, sizeof(test_person2.email),
           "bob.johnson@example.com");
  snprintf(test_person2.phone_number, sizeof(test_person2.phone_number),
           "555-123-4567");

  Node *head = create_node(test_person1);

  int result = add_node_at_index(&head, test_person2, 0);

  TEST_ASSERT_EQUAL_INT(0, result);
  TEST_ASSERT_NOT_NULL(head);
  TEST_ASSERT_EQUAL_STRING("Bob", head->data.name);
  TEST_ASSERT_EQUAL_STRING("Johnson", head->data.surname);
  TEST_ASSERT_EQUAL_STRING("bob.johnson@example.com", head->data.email);
  TEST_ASSERT_EQUAL_STRING("555-123-4567", head->data.phone_number);

  TEST_ASSERT_NOT_NULL(head->next);
  TEST_ASSERT_EQUAL_STRING("Alice", head->next->data.name);
  TEST_ASSERT_EQUAL_STRING("Smith", head->next->data.surname);
  TEST_ASSERT_EQUAL_STRING("alice.smith@example.com", head->next->data.email);
  TEST_ASSERT_EQUAL_STRING("987-654-3210", head->next->data.phone_number);

  free_linked_list(&head);
}

void test_add_node_at_index_multiple_nodes(void) {
  Person test_person1;
  snprintf(test_person1.name, sizeof(test_person1.name), "Alice");
  snprintf(test_person1.surname, sizeof(test_person1.surname), "Smith");
  snprintf(test_person1.email, sizeof(test_person1.email),
           "alice.smith@example.com");
  snprintf(test_person1.phone_number, sizeof(test_person1.phone_number),
           "987-654-3210");

  Person test_person2;
  snprintf(test_person2.name, sizeof(test_person2.name), "Bob");
  snprintf(test_person2.surname, sizeof(test_person2.surname), "Johnson");
  snprintf(test_person2.email, sizeof(test_person2.email),
           "bob.johnson@example.com");
  snprintf(test_person2.phone_number, sizeof(test_person2.phone_number),
           "555-123-4567");

  Person test_person3;
  snprintf(test_person3.name, sizeof(test_person3.name), "Carol");
  snprintf(test_person3.surname, sizeof(test_person3.surname), "Williams");
  snprintf(test_person3.email, sizeof(test_person3.email),
           "carol.williams@example.com");
  snprintf(test_person3.phone_number, sizeof(test_person3.phone_number),
           "222-987-6543");

  Node *head = create_node(test_person1);
  add_node_at_head(&head, test_person2);

  int result = add_node_at_index(&head, test_person3, 1);

  TEST_ASSERT_EQUAL_INT(0, result);
  TEST_ASSERT_NOT_NULL(head);
  TEST_ASSERT_EQUAL_STRING("Bob", head->data.name);
  TEST_ASSERT_EQUAL_STRING("Johnson", head->data.surname);
  TEST_ASSERT_EQUAL_STRING("bob.johnson@example.com", head->data.email);
  TEST_ASSERT_EQUAL_STRING("555-123-4567", head->data.phone_number);

  TEST_ASSERT_NOT_NULL(head->next);
  TEST_ASSERT_EQUAL_STRING("Carol", head->next->data.name);
  TEST_ASSERT_EQUAL_STRING("Williams", head->next->data.surname);
  TEST_ASSERT_EQUAL_STRING("carol.williams@example.com",
                           head->next->data.email);
  TEST_ASSERT_EQUAL_STRING("222-987-6543", head->next->data.phone_number);

  TEST_ASSERT_NOT_NULL(head->next->next);
  TEST_ASSERT_EQUAL_STRING("Alice", head->next->next->data.name);
  TEST_ASSERT_EQUAL_STRING("Smith", head->next->next->data.surname);
  TEST_ASSERT_EQUAL_STRING("alice.smith@example.com",
                           head->next->next->data.email);
  TEST_ASSERT_EQUAL_STRING("987-654-3210", head->next->next->data.phone_number);

  free_linked_list(&head);
}

void test_delete_node_at_index_empty_list(void) {
  Node *head = NULL;

  int result = delete_node_at_index(&head, 0);

  TEST_ASSERT_EQUAL_INT(1, result);
  TEST_ASSERT_NULL(head);
}

void test_delete_node_at_index_invalid_index(void) {
  Person test_person;
  snprintf(test_person.name, sizeof(test_person.name), "Alice");
  snprintf(test_person.surname, sizeof(test_person.surname), "Smith");
  snprintf(test_person.email, sizeof(test_person.email),
           "alice.smith@example.com");
  snprintf(test_person.phone_number, sizeof(test_person.phone_number),
           "987-654-3210");

  Node *head = create_node(test_person);

  int result = delete_node_at_index(&head, 1);

  TEST_ASSERT_EQUAL_INT(1, result);
  TEST_ASSERT_NOT_NULL(head);

  free_linked_list(&head);
}

void test_delete_node_at_index_single_node(void) {
  Person test_person;
  snprintf(test_person.name, sizeof(test_person.name), "Alice");
  snprintf(test_person.surname, sizeof(test_person.surname), "Smith");
  snprintf(test_person.email, sizeof(test_person.email),
           "alice.smith@example.com");
  snprintf(test_person.phone_number, sizeof(test_person.phone_number),
           "987-654-3210");

  Node *head = create_node(test_person);

  int result = delete_node_at_index(&head, 0);

  TEST_ASSERT_EQUAL_INT(0, result);
  TEST_ASSERT_NULL(head);

  free_linked_list(&head);
}

void test_delete_node_at_index_multiple_nodes(void) {
  Person test_person1;
  snprintf(test_person1.name, sizeof(test_person1.name), "Alice");
  snprintf(test_person1.surname, sizeof(test_person1.surname), "Smith");
  snprintf(test_person1.email, sizeof(test_person1.email),
           "alice.smith@example.com");
  snprintf(test_person1.phone_number, sizeof(test_person1.phone_number),
           "987-654-3210");

  Person test_person2;
  snprintf(test_person2.name, sizeof(test_person2.name), "Bob");
  snprintf(test_person2.surname, sizeof(test_person2.surname), "Johnson");
  snprintf(test_person2.email, sizeof(test_person2.email),
           "bob.johnson@example.com");
  snprintf(test_person2.phone_number, sizeof(test_person2.phone_number),
           "555-123-4567");

  Node *head = create_node(test_person1);
  add_node_at_head(&head, test_person2);

  int result = delete_node_at_index(&head, 1);

  TEST_ASSERT_EQUAL_INT(0, result);
  TEST_ASSERT_NOT_NULL(head);
  TEST_ASSERT_EQUAL_STRING("Bob", head->data.name);
  TEST_ASSERT_EQUAL_STRING("Johnson", head->data.surname);
  TEST_ASSERT_EQUAL_STRING("bob.johnson@example.com", head->data.email);
  TEST_ASSERT_EQUAL_STRING("555-123-4567", head->data.phone_number);

  TEST_ASSERT_NULL(head->next);

  free_linked_list(&head);
}

void test_get_length_empty_list(void) {
  Node *head = NULL;

  int length = get_length(head);

  TEST_ASSERT_EQUAL_INT(0, length);
}

void test_get_length_single_node(void) {
  Person test_person;
  snprintf(test_person.name, sizeof(test_person.name), "Alice");
  snprintf(test_person.surname, sizeof(test_person.surname), "Smith");
  snprintf(test_person.email, sizeof(test_person.email),
           "alice.smith@example.com");
  snprintf(test_person.phone_number, sizeof(test_person.phone_number),
           "987-654-3210");

  Node *head = create_node(test_person);

  int length = get_length(head);

  TEST_ASSERT_EQUAL_INT(1, length);

  free_linked_list(&head);
}

void test_get_length_multiple_nodes(void) {
  Person test_person1;
  snprintf(test_person1.name, sizeof(test_person1.name), "Alice");
  snprintf(test_person1.surname, sizeof(test_person1.surname), "Smith");
  snprintf(test_person1.email, sizeof(test_person1.email),
           "alice.smith@example.com");
  snprintf(test_person1.phone_number, sizeof(test_person1.phone_number),
           "987-654-3210");

  Person test_person2;
  snprintf(test_person2.name, sizeof(test_person2.name), "Bob");
  snprintf(test_person2.surname, sizeof(test_person2.surname), "Johnson");
  snprintf(test_person2.email, sizeof(test_person2.email),
           "bob.johnson@example.com");
  snprintf(test_person2.phone_number, sizeof(test_person2.phone_number),
           "555-123-4567");

  Node *head = create_node(test_person1);
  add_node_at_head(&head, test_person2);

  int length = get_length(head);

  TEST_ASSERT_EQUAL_INT(2, length);

  free_linked_list(&head);
}

void test_free_linked_list_empty_list(void) {
  Node *head = NULL;

  int result = free_linked_list(&head);

  TEST_ASSERT_EQUAL_INT(1, result);
  TEST_ASSERT_NULL(head);
}

void test_free_linked_list_single_node(void) {
  Person test_person;
  snprintf(test_person.name, sizeof(test_person.name), "Alice");
  snprintf(test_person.surname, sizeof(test_person.surname), "Smith");
  snprintf(test_person.email, sizeof(test_person.email),
           "alice.smith@example.com");
  snprintf(test_person.phone_number, sizeof(test_person.phone_number),
           "987-654-3210");

  Node *head = create_node(test_person);

  int result = free_linked_list(&head);

  TEST_ASSERT_EQUAL_INT(0, result);
  TEST_ASSERT_NULL(head);
}

void test_free_linked_list_multiple_nodes(void) {
  Person test_person1;
  snprintf(test_person1.name, sizeof(test_person1.name), "Alice");
  snprintf(test_person1.surname, sizeof(test_person1.surname), "Smith");
  snprintf(test_person1.email, sizeof(test_person1.email),
           "alice.smith@example.com");
  snprintf(test_person1.phone_number, sizeof(test_person1.phone_number),
           "987-654-3210");

  Person test_person2;
  snprintf(test_person2.name, sizeof(test_person2.name), "Bob");
  snprintf(test_person2.surname, sizeof(test_person2.surname), "Johnson");
  snprintf(test_person2.email, sizeof(test_person2.email),
           "bob.johnson@example.com");
  snprintf(test_person2.phone_number, sizeof(test_person2.phone_number),
           "555-123-4567");

  Node *head = create_node(test_person1);
  add_node_at_head(&head, test_person2);

  int result = free_linked_list(&head);

  TEST_ASSERT_EQUAL_INT(0, result);
  TEST_ASSERT_NULL(head);
}

void test_copy_node_valid(void) {
  Person test_person;
  snprintf(test_person.name, sizeof(test_person.name), "Alice");
  snprintf(test_person.surname, sizeof(test_person.surname), "Smith");
  snprintf(test_person.email, sizeof(test_person.email),
           "alice.smith@example.com");
  snprintf(test_person.phone_number, sizeof(test_person.phone_number),
           "987-654-3210");

  Node *original_node = create_node(test_person);

  Node *copied_node = copy_node(original_node);

  TEST_ASSERT_NOT_NULL(copied_node);
  TEST_ASSERT_EQUAL_STRING(original_node->data.name, copied_node->data.name);
  TEST_ASSERT_EQUAL_STRING(original_node->data.surname,
                           copied_node->data.surname);
  TEST_ASSERT_EQUAL_STRING(original_node->data.email, copied_node->data.email);
  TEST_ASSERT_EQUAL_STRING(original_node->data.phone_number,
                           copied_node->data.phone_number);

  free_linked_list(&original_node);
  free_linked_list(&copied_node);
}

void test_copy_node_null_input(void) {
  Node *original_node = NULL;

  Node *copied_node = copy_node(original_node);

  TEST_ASSERT_NULL(copied_node);

  free_linked_list(&copied_node);
}

void test_find_node_at_index_empty_list(void) {
  Node *head = NULL;

  Node *result = find_node_at_index(head, 0);

  TEST_ASSERT_NULL(result);
}

void test_find_node_at_index_invalid_index(void) {
  Person test_person;
  snprintf(test_person.name, sizeof(test_person.name), "Alice");
  snprintf(test_person.surname, sizeof(test_person.surname), "Smith");
  snprintf(test_person.email, sizeof(test_person.email),
           "alice.smith@example.com");
  snprintf(test_person.phone_number, sizeof(test_person.phone_number),
           "987-654-3210");

  Node *head = create_node(test_person);

  Node *result = find_node_at_index(head, 1);

  TEST_ASSERT_NULL(result);

  free_linked_list(&head);
}

void test_find_node_at_index_valid(void) {
  Person test_person1;
  snprintf(test_person1.name, sizeof(test_person1.name), "Alice");
  snprintf(test_person1.surname, sizeof(test_person1.surname), "Smith");
  snprintf(test_person1.email, sizeof(test_person1.email),
           "alice.smith@example.com");
  snprintf(test_person1.phone_number, sizeof(test_person1.phone_number),
           "987-654-3210");

  Person test_person2;
  snprintf(test_person2.name, sizeof(test_person2.name), "Bob");
  snprintf(test_person2.surname, sizeof(test_person2.surname), "Johnson");
  snprintf(test_person2.email, sizeof(test_person2.email),
           "bob.johnson@example.com");
  snprintf(test_person2.phone_number, sizeof(test_person2.phone_number),
           "555-123-4567");

  Node *head = create_node(test_person1);
  add_node_at_head(&head, test_person2);

  Node *result1 = find_node_at_index(head, 0);

  TEST_ASSERT_NOT_NULL(result1);
  TEST_ASSERT_EQUAL_STRING("Bob", result1->data.name);
  TEST_ASSERT_EQUAL_STRING("Johnson", result1->data.surname);

  Node *result2 = find_node_at_index(head, 1);

  TEST_ASSERT_NOT_NULL(result2);
  TEST_ASSERT_EQUAL_STRING("Alice", result2->data.name);
  TEST_ASSERT_EQUAL_STRING("Smith", result2->data.surname);

  free_linked_list(&head);
}

void test_find_node_by_data_empty_list(void) {
  Node *head = NULL;
  char field[] = "name";
  char value[] = "Alice";

  Node *result = find_node_by_data(head, field, value);

  TEST_ASSERT_NULL(result);
}

void test_find_node_by_data_invalid_field(void) {
  Person test_person;
  snprintf(test_person.name, sizeof(test_person.name), "Alice");
  snprintf(test_person.surname, sizeof(test_person.surname), "Smith");
  snprintf(test_person.email, sizeof(test_person.email),
           "alice.smith@example.com");
  snprintf(test_person.phone_number, sizeof(test_person.phone_number),
           "987-654-3210");

  Node *head = create_node(test_person);
  char field[] = "age";

  Node *result = find_node_by_data(head, field, "30");

  TEST_ASSERT_NULL(result);

  free_linked_list(&head);
}

void test_find_node_by_data_valid(void) {
  Person test_person1;
  snprintf(test_person1.name, sizeof(test_person1.name), "Alice");
  snprintf(test_person1.surname, sizeof(test_person1.surname), "Smith");
  snprintf(test_person1.email, sizeof(test_person1.email),
           "alice.smith@example.com");
  snprintf(test_person1.phone_number, sizeof(test_person1.phone_number),
           "987-654-3210");

  Person test_person2;
  snprintf(test_person2.name, sizeof(test_person2.name), "Bob");
  snprintf(test_person2.surname, sizeof(test_person2.surname), "Johnson");
  snprintf(test_person2.email, sizeof(test_person2.email),
           "bob.johnson@example.com");
  snprintf(test_person2.phone_number, sizeof(test_person2.phone_number),
           "555-123-4567");

  Node *head = create_node(test_person1);
  add_node_at_head(&head, test_person2);

  Node *result1 = find_node_by_data(head, "name", "Bob");
  Node *result2 = find_node_by_data(head, "email", "alice.smith@example.com");

  TEST_ASSERT_NOT_NULL(result1);
  TEST_ASSERT_NOT_NULL(result2);
  TEST_ASSERT_EQUAL_STRING("Bob", result1->data.name);
  TEST_ASSERT_EQUAL_STRING("alice.smith@example.com", result2->data.email);

  free_linked_list(&head);
  free_linked_list(&result1);
  free_linked_list(&result2);
}
