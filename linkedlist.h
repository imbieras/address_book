#ifndef LINKEDLIST

#define MAX_FILE_LINE_LENGTH 1024
#define MAX_CSV_FIELDS 4
#define MAX_PERSONS 10

typedef struct {
  char name[100];
  char surname[100];
  char email[100];
  char phone_number[100];
} Person;

typedef struct Node {
  Person data;
  struct Node *next;
} Node;

void err_n_die(const char *fmt, ...);
Node *create_node(Person data);
void display_nodes(Node *head);
void add_node_at_head(Node **head, Person data);
void add_node_at_index(Node **head, Person data, int index);
void delete_node_at_index(Node **head, int index);
void free_linked_list(Node **head);
Node *find_node_at_index(Node *head, int index);
Node *find_node_by_data(Node *head, char *field, char *value);
int read_csv_file(const char *filename, Node **head);

#endif // !LINKEDLIST
