#include "../helper.h"
#include "lhelper.h"
#include "linkedlist.h"
#include <stdio.h>
#include <string.h>
#include <unity.h>

int stop_loop = 0;

void setUp(void) {}

void tearDown(void) {}

void test_create_person_input(void) {
  Person data;

  FILE *fake_stdin = fopen("fake_stdin.txt", "w");
  if (!fake_stdin) {
    TEST_FAIL_MESSAGE("Failed to open fake_stdin.txt for writing.");
    return;
  }
  fprintf(fake_stdin, "John\nDoe\njohn.doe@example.com\n123-456-7890\n");
  fclose(fake_stdin);

  freopen("fake_stdin.txt", "r", stdin);

  data = create_person_input();

  freopen("/dev/tty", "r", stdin);

  TEST_ASSERT_EQUAL_STRING("John", data.name);
  TEST_ASSERT_EQUAL_STRING("Doe", data.surname);
  TEST_ASSERT_EQUAL_STRING("john.doe@example.com", data.email);
  TEST_ASSERT_EQUAL_STRING("123-456-7890", data.phone_number);
}
