#include "../lib/helper.h"
#include "../lib/linkedlist.h"
#include "helper.h"
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

int stop_loop = 0;

int main(void) {
  signal(SIGINT, signal_handler);

  Node *head = NULL;

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

  if (read_csv_file(address_file_path, &head)) {
    printf("Failed to read CSV file. Continuing without it.\n");
  }

  print_usage();

  while (!stop_loop) {
    switch (get_user_option()) {
    case 1:
      display_list(head);
      break;
    case 2:
      add_node_at_head(&head, create_person_input());
      break;
    case 3:
      add_node_at_index(&head, create_person_input(), get_user_option());
      break;
    case 4:
      find_by_index(head);
      break;
    case 5:
      find_by_keyword(head);
      break;
    case 6:
      delete_node_at_index(&head, get_user_option());
      break;
    case 7:
      printf("List size - %d\n", get_length(head));
      break;
    case 8:
      free_linked_list(&head);
      break;
    case 9:
      stop_loop = 1;
      break;
    default:
      printf("Your selected option doesn't exist\n");
      break;
    }
  }

  free(address_file_path);
  free_linked_list(&head);
  return 0;
}
