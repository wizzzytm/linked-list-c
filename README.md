# Linked List in C

A small singly linked list library for `int` values, written in C while learning pointers and dynamic memory allocation. Nodes are allocated with `malloc`, and the library owns and frees them (`destroy_list`).

## Files

- `linked-list.h`: the node type and function declarations
- `linked-list.c`: the implementation
- `main.c`: `assert`-based tests

## Node type

```c
typedef struct node {
	int val;
	struct node *next;
} node_t;
```

An empty list is a `NULL` head pointer.

## API

Functions that can change which node is first take `node_t **head`. Functions that only read the list, or change nodes after the first, take the head directly.

| Function                             | Description                                                                                                          |
| ------------------------------------ | -------------------------------------------------------------------------------------------------------------------- |
| `push(&head, val)`                   | Insert at the beginning                                                                                              |
| `append(&head, val)`                 | Insert at the end                                                                                                    |
| `insert_at_index(&head, val, index)` | Insert at `index`. Index 0 pushes, index equal to the length appends, an out-of-range or negative index does nothing |
| `pop(&head)`                         | Remove and return the last value                                                                                     |
| `pop_first(&head)`                   | Remove and return the first value                                                                                    |
| `remove_at_index(&head, index)`      | Remove and return the value at `index`                                                                               |
| `remove_by_value(&head, val)`        | Remove the first node with `val` and return it                                                                       |
| `get_length(head)`                   | Number of nodes                                                                                                      |
| `contains(head, val)`                | Returns 1 if `val` is in the list, otherwise 0                                                                       |
| `print_list(head)`                   | Print every value on its own line                                                                                    |
| `reverse(&head)`                     | Reverse the list in place                                                                                            |
| `remove_duplicates(head)`            | Remove repeated values, keeping the first occurrence                                                                 |
| `sort_list(&head)`                   | Sort ascending, in place                                                                                             |
| `destroy_list(&head)`                | Free every node and set the head to `NULL`                                                                           |

`pop`, `pop_first`, `remove_at_index` and `remove_by_value` return `-1` when nothing was removed.

## Example

```c
#include <stdio.h>
#include "linked-list.h"

int main(void) {
	node_t *head = NULL;

	push(&head, 3);
	push(&head, 1);
	append(&head, 2);      // 1 -> 3 -> 2

	sort_list(&head);      // 1 -> 2 -> 3
	print_list(head);

	destroy_list(&head);
	return 0;
}
```

## Build and test

```
gcc -Wall -Wextra -g -fsanitize=address,undefined main.c linked-list.c -o test
./test
```

The tests use `assert`, and AddressSanitizer and UBSan report memory errors and leaks.

## Implementation notes

- `sort_list` is an insertion sort that relinks the existing nodes. It allocates no memory (O(1) extra space), but it takes O(n²) time, so it is meant for short lists.
- `reverse` also works in place by moving nodes to the front.
- `remove_duplicates` compares every node with the rest, so it takes O(n²) time and O(1) extra space.
- `append` and `pop` walk the whole list, so they take O(n) time. Keeping a tail pointer would make `append` O(1).

## Known limitations and TODO

- Removal functions return `-1` on error, which cannot be told apart from a stored `-1`. Returning a status code and passing the value through a pointer would fix this.
- `push`, `append` and `insert_at_index` silently do nothing when `malloc` fails. They should return a status code.
- Only `int` values are supported.
- Possible next steps: a faster sort (merge sort on lists), a tail pointer, and a doubly linked variant.
