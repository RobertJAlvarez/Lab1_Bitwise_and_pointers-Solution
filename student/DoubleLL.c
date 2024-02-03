#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "DoubleLL.h"

// Helper function to return __XOR of `x` and `y`
static node_t *__XOR(const void *x, const void *y) {
  return (node_t *)(((uintptr_t)x) ^ ((uintptr_t)y));
}

void print_LL(const list_t *LL, const order_t order) {
  if (LL == NULL) return;

  node_t *curr = order == ASC ? LL->head : LL->tail;
  node_t *prev = NULL;
  node_t *next;

  while (curr != NULL) {
    printf("%d —> ", curr->data);

    // `next` node would be xor of the address of the
    //  previous node and current node link
    next = __XOR(prev, curr->link);

    // update `prev` and `curr` pointers for the next
    //  iteration of the loop
    prev = curr;
    curr = next;
  }

  printf("NULL\n");
}

int push(list_t *LL, const int data) {
  if (LL == NULL) return 1;

  node_t *head = LL->head;

  // allocate a new list node and set its data
  node_t *newNode = (node_t *)malloc(sizeof(node_t));
  newNode->data = data;

  // The link field of the new node is __XOR of the current
  //  head and `NULL` since a new node is being inserted at
  //  the beginning
  newNode->link = head;

  // Update LL
  if (head != NULL)
    // Update head->link value of the current head node if
    //  the linked list is not empty
    head->link = __XOR(newNode, head->link);
  else
    // If head is null, then newNode, head and tail are the
    //  same
    LL->tail = newNode;

  // update the head pointer
  LL->head = newNode;

  return 0;
}

int insert_node(list_t *LL, node_t *new_node) {
  printf("IMPLEMENT THIS FUNCTION");
  printf("LL = %p\n", LL);
  printf("new_node = %p\n", new_node);

  return 1;
}

int remove_node(list_t *LL, unsigned long remove_node) {
  printf("IMPLEMENT THIS FUNCTION");
  printf("LL = %p\n", LL);
  printf("remove_node = %ld\n", remove_node);

  return 1;
}
