#ifndef LINKEDLIST_H
#define LINKEDLIST_H

typedef struct node {
	int val;
	struct node *next;
} node_t;

void print_list(node_t *head);

void append(node_t **head, int val);

void push(node_t **head, int val);
int pop(node_t **head);

int pop_first(node_t **head);

int remove_at_index(node_t **head, int index);

int remove_by_value(node_t **head, int val);

void insert_at_index(node_t **head, int val, int index);

int get_length(node_t * head);

void reverse(node_t ** head);

void print_list(node_t *head);

void destroy_list(node_t ** head);

int contains(node_t * head, int val);

void remove_duplicates(node_t * head);

void sort_list(node_t ** head);

#endif