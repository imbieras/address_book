#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#define MAX_FILE_LINE_LENGTH 1024
#define MAX_CSV_FIELDS 4
#define MAX_PERSONS 10
#define BUFFER_SIZE 100

#define GET_INPUT(prompt, field)                                               \
  fprintf(stdout, prompt);                                                     \
  fflush(stdout);                                                              \
  if (fgets(data.field, BUFFER_SIZE, stdin)) {                                 \
    char *p;                                                                   \
    if ((p = strchr(data.field, '\n'))) {                                      \
      *p = '\0';                                                               \
    } else {                                                                   \
      scanf("%*[^\n]");                                                        \
      scanf("%*c");                                                            \
    }                                                                          \
  }

typedef struct {
  char name[BUFFER_SIZE];
  char surname[BUFFER_SIZE];
  char email[BUFFER_SIZE];
  char phone_number[BUFFER_SIZE];
} Person;

typedef struct Node {
  Person data;
  struct Node *next;
} Node;

void err_n_die(const char *fmt, ...);
void clear_input_buffer();
void signal_handler(int signal);
void flush_stdin();
Node *create_node(Person data);
Person create_person_input();
void handle_user_input(Node **head);
void display_nodes(Node *head);
void add_node_at_head(Node **head, Person data);
void add_node_at_index(Node **head, Person data, int index);
void delete_node_at_index(Node **head, int index);
int get_length(Node *head);
void free_linked_list(Node **head);
Node *find_node_at_index(Node *head, int index);
Node *find_node_by_data(Node *head, char *field, char *value);
int read_csv_file(const char *filename, Node **head);

#endif // LINKEDLIST_H
