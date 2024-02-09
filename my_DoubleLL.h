#ifndef __MY_DOUBLE_LL_H__
#define __MY_DOUBLE_LL_H__

typedef enum { my_DESC, my_ASC } my_order_t;

/* Data structure to store a XOR linked list node */
typedef struct __my_node_t {
  int data;
  struct __my_node_t *link;
} my_node_t;

typedef struct {
  my_node_t *head;
  my_node_t *tail;
} my_list_t;

my_node_t *__XOR(const void *x, const void *y);

void my_free_LL(my_list_t *LL);

/* Helper function to print every value in list nodes on a
 * forward traversal.
 */
void my_print_LL(const my_list_t *LL, const my_order_t order);

/* Helper function to create a node with data and added at
 * the beginning of the list.
 */
void my_push(my_list_t *LL, const int data);

/* Helper function to insert new_node in LL such that the
 * node before it have a lower address and the node after
 * have a higher address than new_node.
 */
void my_insert_node(my_list_t *LL, my_node_t *new_node);

/* Helper function to remove a node from LL given its
 * address.
 */
void my_remove_node(my_list_t *LL, unsigned long remove_node);

#endif
