#ifndef __XOR_DOUBLE_LL_H__
#define __XOR_DOUBLE_LL_H__

typedef enum { DESC, ASC } order_t;

/* Data structure to store a XOR linked list node */
typedef struct __node_t {
  int data;
  struct __node_t *link;
} node_t;

typedef struct {
  node_t *head;
  node_t *tail;
} list_t;

/* Helper function to print every value in list nodes on a
 * forward traversal.
 */
void print_LL(const list_t *LL, const order_t order);

/* Helper function to create a node with data and added at
 * the beginning of the list.
 */
void push(list_t *LL, const int data);

/* Helper function to insert new_node in LL such that the
 * node before it have a lower address and the node after
 * have a higher address than new_node.
 */
void insert_node(list_t *LL, node_t *new_node);

/* Helper function to remove a node from LL given its
 * address.
 */
void remove_node(list_t *LL, unsigned long remove_node);

#endif
