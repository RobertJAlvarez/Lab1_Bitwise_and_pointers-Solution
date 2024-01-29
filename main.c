#include <stdio.h>
#include <stdlib.h>

#include "DoubleLL.h"
#include "bitwise_f.h"

int main(void) {
  // Double linked list
  int keys[] = {1, 2, 3, 4, 5};
  int n = sizeof(keys) / sizeof(keys[0]);
  list_t *LL = (list_t *)malloc(sizeof(list_t));

  for (int i = n - 1; i >= 0; i--) push(LL, keys[i]);

  printf("Ascending...\n");
  print_LL(LL, ASC);

  printf("Descending...\n");
  print_LL(LL, DESC);

  // Print numbers
  for (unsigned char number = 0; number <= 9; ++number) {
    printf("Drawing number %d\n", number);
    print_number(number, NO);
  }

  printf("Reflection = NO\n");
  print_number(7, NO);
  printf("Reflection = x_axis\n");
  print_number(7, x_axis);
  printf("Reflection = y_axis\n");
  print_number(7, y_axis);
  printf("Reflection = xy_axis\n");
  print_number(7, xy_axis);

  return 0;
}
