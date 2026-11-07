#include <stdio.h>
#include <stdlib.h>
#include "linked-list.h"

void append(node_t **head, int val) {
	if (*head == NULL) {
		node_t *new_node = malloc(sizeof *new_node);

		if (new_node == NULL) return;

		new_node->val = val;
		new_node->next = NULL;
		*head = new_node;
		return;
	}

	node_t *current = *head;

	while (current->next != NULL) {
		current = current->next;
	}

	node_t *new_node = malloc(sizeof *new_node);

	if (new_node == NULL) return;

	new_node->val = val;
	new_node->next = NULL;
	current->next = new_node;
}

void push(node_t **head, int val) {
	node_t *new_node = malloc(sizeof(*new_node));

	if (new_node == NULL) return;

	new_node->val = val;
	new_node->next = *head;
	*head = new_node;
}

int pop(node_t **head) {
	int retval = -1;

	if (*head == NULL) {
		return -1;
	}

	node_t *current = *head;

	if (current->next == NULL) {
		retval = current->val;
		free(*head);
		*head = NULL;
		return retval;
	}

	while (current->next->next != NULL) {
		current = current->next;
	}

	retval = current->next->val;
	free(current->next);
	current->next = NULL;
	return retval;
}

int pop_first(node_t **head) {
	int retval = -1;

	if (*head == NULL) {
		return -1;
	}

	node_t *temp_node = (*head)->next;
	retval = (*head)->val;
	free(*head);
	*head = temp_node;
	return retval;
}

int remove_at_index(node_t **head, int index) {
	if (index < 0) return -1;

	int retval = -1;

	if (*head == NULL) {
		return -1;
	}

	if (index == 0) {
		return pop_first(head);
	}

	node_t *current = *head;
	node_t *temp_node = NULL;

	for (int i = 0; i < index - 1; i++) {
		if (current->next == NULL)
			return -1;

		current = current->next;
	}

	if (current->next == NULL) {
		return -1;
	}

	temp_node = current->next;
	retval = temp_node->val;
	current->next = temp_node->next;
	free(temp_node);
	return retval;
}

int remove_by_value(node_t **head, int val) {
	int retval = -1;
	node_t *current = *head;
	node_t *temp_node = NULL;

	if (*head == NULL) {
		return -1;
	}else if (current->val == val) {
		return pop_first(head);
	}

	while (current->next != NULL) {
		if (current->next->val == val) {
			temp_node = current->next;
			retval = temp_node->val;
			current->next = temp_node->next;
			free(temp_node);
			return retval;
		}

		current = current->next;
	}

	return retval;
}

void insert_at_index(node_t **head, int val, int index) {
	if (index < 0) return;

	if(index == 0) {
		push(head, val);
		return;
	}

	if(*head == NULL) {
		return;
	}

	node_t * current = *head;

	for(int i = 0; i<index-1; i++) {
		if(current->next == NULL) {
			return;
		}

		current = current->next;
	}

	if(current->next == NULL) {
		append(head, val);
		return;
	}

	node_t *new_node = malloc(sizeof *new_node);

	if (new_node == NULL) return;

	new_node->val = val;
	new_node->next = current->next;
	current->next = new_node;
}

int get_length(node_t * head) {
	node_t * current = head;
	int retval = 0;

	while(current != NULL) {
		retval++;
		current = current->next;
	}

	return retval;
}

void reverse(node_t ** head) {
	if(*head == NULL) {
		return;
	}

	node_t * current = *head;
	node_t * temp = NULL;

	while(current->next != NULL) {
		temp = current->next;
		current->next = temp->next;
		temp->next = *head;
		*head = temp;
	}
}

void print_list(node_t *head) {
	node_t * current = head;

	while(current!=NULL) {
		printf("%d\n", current->val);
		current = current->next;
	}
}

void destroy_list(node_t ** head) {
	if(*head == NULL) {
		return;
	}

	node_t * current = *head;
	node_t * next_node = NULL;

	while(current != NULL) {
		next_node = current->next;
		free(current);
		current = next_node;
	}

	*head = NULL;
}

int contains(node_t * head, int val) {
	node_t * current = head;

	while(current != NULL) {
		if(current->val == val) {
			return 1;
		}

		current = current->next;
	}

	return 0;
}

void remove_duplicates(node_t * head) {
	node_t * current = head;
	node_t * temp = NULL;
	node_t * runner = NULL;

	while(current != NULL) {
		runner = current;

		while(runner->next != NULL) {
			if(runner->next->val == current->val) {
				temp = runner->next;
				runner->next = temp->next;
				free(temp);
			}else {
				runner = runner->next;
			}
		}

		current = current->next;
	}
}

void sort_list(node_t ** head) {
	node_t * sorted = NULL;
	node_t * current = *head;
	node_t * next = NULL;

	while(current!=NULL) {
		next = current->next;

		if(sorted == NULL || current->val < sorted->val) {
			current->next = sorted;
			sorted = current;
		}else {
			node_t * s = sorted;

			while(s->next != NULL && s->next->val < current->val) {
				s = s->next;
			}

			current->next = s->next;
			s->next = current;
		}

		current = next;
	}

	*head = sorted;
}