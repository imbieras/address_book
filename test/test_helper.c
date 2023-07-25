#include "helper.h"
#include "lib/linkedlist.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unity.h>

int stop_loop = 0;

void setUp(void) {}

void tearDown(void) {}

void test_GET_INPUT_valid_input(void) {
  char input[BUFFER_SIZE];
  FILE *fake_stdin = fopen("fake_stdin.txt", "w");
  if (!fake_stdin) {
    TEST_FAIL_MESSAGE("Failed to open fake_stdin.txt for writing.");
    return;
  }

  fprintf(fake_stdin, "Test Input\n");
  fclose(fake_stdin);

  freopen("fake_stdin.txt", "r", stdin);

  GET_INPUT("Enter test input: ", input);

  freopen("/dev/tty", "r", stdin);

  TEST_ASSERT_EQUAL_STRING("Test Input", input);
}

void test_GET_INPUT_long_input(void) {
  char input[BUFFER_SIZE];
  FILE *fake_stdin = fopen("fake_stdin.txt", "w");
  if (!fake_stdin) {
    TEST_FAIL_MESSAGE("Failed to open fake_stdin.txt for writing.");
    return;
  }

  fprintf(fake_stdin,
          "Lorem ipsum dolor sit amet, consectetur adipiscing elit. Morbi "
          "ultrices neque fermentum, volutpat purus fusce.");
  fclose(fake_stdin);

  freopen("fake_stdin.txt", "r", stdin);

  GET_INPUT("Enter test input: ", input);

  freopen("/dev/tty", "r", stdin);

  TEST_ASSERT_EQUAL_STRING_LEN(
      "Lorem ipsum dolor sit amet, consectetur adipiscing "
      "elit. Morbi ultrices neque fermentum, volutpat p",
      input, BUFFER_SIZE - 1);
}

void test_get_user_option_valid_input(void) {
  char input[BUFFER_SIZE];
  FILE *fake_stdin = fopen("fake_stdin.txt", "w");
  if (!fake_stdin) {
    TEST_FAIL_MESSAGE("Failed to open fake_stdin.txt for writing.");
    return;
  }

  fprintf(fake_stdin, "42\n");
  fclose(fake_stdin);

  freopen("fake_stdin.txt", "r", stdin);

  int option = get_user_option();

  freopen("/dev/tty", "r", stdin);

  TEST_ASSERT_EQUAL_INT(42, option);
}

void test_get_user_option_invalid_input(void) {
  char input[BUFFER_SIZE];
  FILE *fake_stdin = fopen("fake_stdin.txt", "w");
  if (!fake_stdin) {
    TEST_FAIL_MESSAGE("Failed to open fake_stdin.txt for writing.");
    return;
  }

  fprintf(fake_stdin, "invalid\n-15\n");
  fclose(fake_stdin);

  freopen("fake_stdin.txt", "r", stdin);

  int option = get_user_option();

  freopen("/dev/tty", "r", stdin);

  TEST_ASSERT_EQUAL_INT(-15, option);
}

void test_read_csv_file_valid_entries(void) {
  Node *head = NULL;

  FILE *csv_file = fopen("test.csv", "w");
  fprintf(csv_file, "Alice,Smith,alice.smith@example.com,987-654-3210\n");
  fprintf(csv_file, "Bob,Johnson,bob.johnson@example.com,555-123-4567\n");
  fclose(csv_file);

  int result = read_csv_file("test.csv", &head);

  TEST_ASSERT_EQUAL_INT(0, result);

  TEST_ASSERT_EQUAL_INT(2, get_length(head));

  free_linked_list(&head);
  remove("test.csv");
}

void test_read_csv_file_invalid_entries(void) {
  Node *head = NULL;

  FILE *csv_file = fopen("test.csv", "w");
  fprintf(csv_file, "Alice,Smith,alice.smith@example.com\n");
  fprintf(csv_file, ",Johnson,bob.johnson@example.com,555-123-4567\n");
  fclose(csv_file);

  int result = read_csv_file("test.csv", &head);

  TEST_ASSERT_EQUAL_INT(0, result);

  TEST_ASSERT_EQUAL_INT(0, get_length(head));

  free_linked_list(&head);
  remove("test.csv");
}

void test_read_csv_file_file_not_found(void) {
  Node *head = NULL;

  int result = read_csv_file("nonexistent.csv", &head);

  TEST_ASSERT_EQUAL_INT(2, result);
}
