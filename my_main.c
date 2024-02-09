#include <stdio.h>
#include <stdlib.h>

#include "my_DoubleLL.h"
#include "my_bitwise_f.h"

int main(void) {
  // Double linked list
  int keys[] = {1, 2, 3, 4, 5};
  int n = sizeof(keys) / sizeof(keys[0]);

  my_list_t *LL = (my_list_t *)malloc(sizeof(my_list_t));

  for (int i = n - 1; i >= 0; i--) my_push(LL, keys[i]);

  printf("Ascending...\n");
  my_print_LL(LL, my_ASC);

  printf("Descending...\n");
  my_print_LL(LL, my_DESC);

  my_free_LL(LL);
  free(LL);

  // Print numbers
  for (unsigned char number = 0; number <= 9; ++number) {
    printf("Drawing number %d\n", number);
    my_print_number(number, my_NO);
  }

  printf("Reflection = NO\n");
  my_print_number(7, my_NO);
  printf("Reflection = x_axis\n");
  my_print_number(7, my_x_axis);
  printf("Reflection = y_axis\n");
  my_print_number(7, my_y_axis);
  printf("Reflection = xy_axis\n");
  my_print_number(7, my_xy_axis);

  return 0;
}
