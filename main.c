#include <stdio.h>
#include "linked-list.h"
#include <assert.h>

static int is_sorted(node_t *head) {
	while (head != NULL && head->next != NULL) {
		if (head->val > head->next->val) return 0;

		head = head->next;
	}

	return 1;
}

int main() {
	node_t *head = NULL;
	push(&head, 1);
	push(&head, 2);
	assert(get_length(head) == 2);
	assert(pop_first(&head) == 2);
	assert(pop(&head) == 1);
	assert(head == NULL);
	assert(remove_at_index(&head, -1) == -1);
	destroy_list(&head);

	node_t *head2 = NULL;
	push(&head2, 5);
	push(&head2, 1);
	push(&head2, 2);
	push(&head2, 4);
	push(&head2, 3);
	push(&head2, 5);
	printf("Lista przed posortowaniem: \n");
	print_list(head2);
	printf("Lista po posortowaniu: \n");
	sort_list(&head2);
	print_list(head2);
	assert(is_sorted(head2) == 1);
	destroy_list(&head2);

	node_t *e = NULL;
	sort_list(&e);
	assert(e == NULL);
	node_t *one = NULL;
	push(&one, 7);
	sort_list(&one);
	assert(get_length(one) == 1 && one->val == 7);
	destroy_list(&one);
	printf("Wszystkie testy przeszly\n");

	return 0;
}
