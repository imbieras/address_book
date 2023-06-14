#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#define MAX_FILE_LINE_LENGTH 1024
#define MAX_CSV_FIELDS 4
#define MAX_PERSONS 10
#define BUFFER_SIZE 100

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

Node *create_node(Person data);
void display_person(Node *node);
void display_list(Node *head);
void add_node_at_head(Node **head, Person data);
void add_node_at_index(Node **head, Person data, int index);
void delete_node_at_index(Node **head, int index);
int get_length(Node *head);
void free_linked_list(Node **head);
Node *find_node_at_index(Node *head, int index);
Node *find_node_by_data(Node *head, char *field, char *value);

#endif // LINKEDLIST_H
