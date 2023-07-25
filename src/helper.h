#ifndef HELPER_H
#define HELPER_H

#include "./lib/linkedlist.h"

#define SEPARATOR_LINE "--------------------------------------------------"
#define PRINT_SEPARATOR() printf("%s\n", SEPARATOR_LINE)

#define GET_INPUT(prompt, field)                                               \
  fprintf(stdout, prompt);                                                     \
  fflush(stdout);                                                              \
  if (fgets(field, BUFFER_SIZE, stdin)) {                                      \
    char *p;                                                                   \
    if ((p = strchr(field, '\n'))) {                                           \
      *p = '\0';                                                               \
    } else {                                                                   \
      scanf("%*[^\n]");                                                        \
      scanf("%*c");                                                            \
    }                                                                          \
  }

void err_n_die(const char *fmt, ...);
void clear_input_buffer();
void signal_handler(int signal);
void print_usage();
int get_user_option();
int find_by_index(Node *head);
int find_by_keyword(Node *head);
int read_csv_file(const char *filename, Node **head);

#endif // HELPER_H
