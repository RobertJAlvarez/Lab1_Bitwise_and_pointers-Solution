#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "my_DoubleLL.h"

// Helper function to return __XOR of `x` and `y`
my_node_t *__XOR(const void *x, const void *y) {
  return (my_node_t *)(((uintptr_t)x) ^ ((uintptr_t)y));
}

void my_free_LL(my_list_t *LL) {
  my_node_t *curr = LL->head;
  my_node_t *prev = NULL;
  my_node_t *next;

  while (curr != NULL) {
    next = __XOR(prev, curr->link);
    prev = curr;
    free(curr);
    curr = next;
  }
}

void my_print_LL(const my_list_t *LL, const my_order_t order) {
  if (LL == NULL) return;

  my_node_t *curr = order == my_ASC ? LL->head : LL->tail;
  my_node_t *prev = NULL;
  my_node_t *next;

  while (curr != NULL) {
    printf("%d —> ", curr->data);

    // `next` node would be xor of the address of the
    //   previous node and current node link
    next = __XOR(prev, curr->link);

    // update `prev` and `curr` pointers for the next
    //  iteration of the loop
    prev = curr;
    curr = next;
  }

  printf("NULL\n");
}

static void __push_node(my_list_t *LL, my_node_t *new_node) {
  if (LL->head != NULL)
    // Update head->link value of the current head
    //  node if the linked list is not empty
    LL->head->link = __XOR(new_node, LL->head->link);
  else
    // If head is null, then newNode, head and tail
    //  are the same
    LL->tail = new_node;

  // update the head pointer
  LL->head = new_node;
}

void my_push(my_list_t *LL, const int data) {
  if (LL == NULL) return;

  my_node_t *head = LL->head;

  // allocate a new list node and set its data
  my_node_t *newNode = (my_node_t *)malloc(sizeof(my_node_t));
  newNode->data = data;

  // The link field of the new node is __XOR of the current
  //  head and 'NULL' since a new node is being inserted at
  //  the beginning
  newNode->link = head;

  __push_node(LL, newNode);
}

void my_insert_node(my_list_t *LL, my_node_t *new_node) {
  if (LL == NULL) return;

  // If new_node is the first node in LL or if new_node
  //  have a lower address that current LL->head
  if (LL->head == NULL || LL->head > new_node) {
    __push_node(LL, new_node);
    return;
  }

  // If new_node is greater than tail, just update
  //  tail and last node
  if (LL->tail < new_node) {
    LL->tail->link = __XOR(LL->tail->link, new_node);
    new_node->link = LL->tail;
    LL->tail = new_node;
    return;
  }

  // Iterate until we find the last node in LL with
  //  lower address than new_node
  my_node_t *curr = LL->head;
  my_node_t *prev = NULL;
  my_node_t *next;

  do {
    next = __XOR(prev, curr->link);
    prev = curr;
    curr = next;
  } while (curr < new_node);

  // Add new_node between prev and next
  prev->link = __XOR(__XOR(prev->link, next), new_node);
  next->link = __XOR(__XOR(next->link, prev), new_node);
  new_node->link = __XOR(prev, next);
}

void my_remove_node(my_list_t *LL, unsigned long remove_node) {
  if (LL == NULL) return;

  my_node_t *free_node = (my_node_t *)remove_node;

  // If the node to free is head or tail, update LL head or
  //  tail pointer
  if (LL->head == free_node || LL->tail == free_node) {
    my_node_t **update = LL->head == free_node ? &(LL->head) : &(LL->tail);

    // Update what head or tail is pointing to
    *update = free_node->link;
    // Update the link of it
    (*update)->link = __XOR((*update)->link, free_node);
  }
  // Node is not in head nor tail, so iterate list and update
  //  node links
  else {
    my_node_t *curr = LL->head;
    my_node_t *prev = NULL;
    my_node_t *next;

    // Find the node pointing to remove_node
    do {
      next = __XOR(prev, curr->link);
      prev = curr;
      curr = next;
    } while (curr != free_node);

    // Update the link of the previous node
    prev->link =
        __XOR(__XOR(prev->link, free_node), __XOR(free_node->link, prev));
  }

  // Free node
  free(free_node);
}
