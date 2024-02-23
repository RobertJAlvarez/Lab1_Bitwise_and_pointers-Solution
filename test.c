#include <errno.h>     //errno
#include <stdio.h>     //printf() fprintf()
#include <stdlib.h>    //rand()
#include <string.h>    //strcpy()
#include <sys/mman.h>  //mmap() munmap()
#include <sys/wait.h>  //wait()
#include <time.h>      //time()
#include <unistd.h>    //fork()

#include "DoubleLL.h"
#include "bitwise_f.h"
#include "my_DoubleLL.h"
#include "my_bitwise_f.h"

#define N_TESTS ((size_t)1000)
#define MAX_DATA (256)

static void error_no_memory(void) {
  fprintf(stderr, "No more memory available.\n");
  return;
}

/* 10 points */
double test_swap(void) {
  size_t passed = 0;
  const double points = 10.;

  short n1, n2, n3, n4;

  printf("-------------------------\n");
  printf("Function %s() ", __func__);

  for (size_t i = 0; i < N_TESTS; i++) {
    n1 = n3 = (short)rand();
    n2 = n4 = (short)rand();

    swap(&n1, &n2);
    my_swap(&n3, &n4);

    passed += ((n1 == n3) && (n2 == n4));
  }

  return points * ((double)passed) / ((double)N_TESTS);
}

/* 10 points */
double test_has_odd_number_of_bits_set(void) {
  size_t passed = 0;
  const double points = 10.;

  int n1, n2;

  printf("-------------------------\n");
  printf("Function %s() ", __func__);

  for (size_t i = 0; i < N_TESTS; i++) {
    n1 = n2 = rand();

    passed +=
        (my_has_odd_number_of_bits_set(n1) == has_odd_number_of_bits_set(n2));
  }

  return points * ((double)passed) / ((double)N_TESTS);
}

/* 5 points */
double test_turn_k_bit_off(void) {
  size_t passed = 0;
  const double points = 5.;

  int n1, n2;
  short k;

  printf("-------------------------\n");
  printf("Function %s() ", __func__);

  for (size_t i = 0; i < N_TESTS; i++) {
    n1 = n2 = rand();
    k = ((short)(((unsigned long)rand()) % (sizeof(int) * 8)));

    passed += (my_turn_k_bit_off(n1, k) == turn_k_bit_off(n2, k));
  }

  return points * ((double)passed) / ((double)N_TESTS);
}

/* 5 points */
double test_k_bit_is_on(void) {
  size_t passed = 0;
  const double points = 5.;

  int n1, n2;
  short k;

  printf("-------------------------\n");
  printf("Function %s() ", __func__);

  for (size_t i = 0; i < N_TESTS; i++) {
    n1 = n2 = rand();
    k = ((short)(((unsigned long)rand()) % (sizeof(int) * 8)));

    passed += (my_k_bit_is_on(n1, k) == k_bit_is_on(n2, k));
  }

  return points * ((double)passed) / ((double)N_TESTS);
}

/* 5 points */
double test_toggle_k_bit(void) {
  size_t passed = 0;
  const double points = 5.;

  int n1, n2;
  short k;

  printf("-------------------------\n");
  printf("Function %s() ", __func__);

  for (size_t i = 0; i < N_TESTS; i++) {
    n1 = n2 = rand();
    k = ((short)(((unsigned long)rand()) % (sizeof(int) * 8)));

    passed += (my_toggle_k_bit(n1, k) == toggle_k_bit(n2, k));
  }

  return points * ((double)passed) / ((double)N_TESTS);
}

/* 15 points */
double test_is_palindrome(void) {
  size_t passed = 0;
  const double points = 15.;

  int n1, n2;

  printf("-------------------------\n");
  printf("Function %s() ", __func__);

  for (size_t i = 0; i < N_TESTS; i++) {
    n1 = n2 = rand();

    if ((my_is_palindrome(n1) == is_palindrome(n2)) ||
        (my_is_palindrome2(n1) == is_palindrome(n2)))
      passed++;
  }

  return points * ((double)passed) / ((double)N_TESTS);
}

/* 15 points */
double test_copy_reverse_bits(void) {
  size_t passed = 0;
  const double points = 15.;

  short n1, n2;

  printf("-------------------------\n");
  printf("Function %s() ", __func__);

  for (size_t i = 0; i < N_TESTS; i++) {
    n1 = n2 = ((short)rand());

    passed += (my_copy_reverse_bits(n1) == copy_reverse_bits(n2));
  }

  return points * ((double)passed) / ((double)N_TESTS);
}

static char *randstring(size_t length) {
  static char charset[] =
      "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789`~!@#$%^&*"
      "()_+-=[]{}\\|;:,<.>/?";
  char *randomString = NULL;

  if (!length) return NULL;
  if ((randomString = malloc(sizeof(char) * (length + 1))) == NULL) return NULL;

  for (size_t i = 0; i < length; i++) {
    int key = rand() % (int)(sizeof(charset) - 1);
    randomString[i] = charset[key];
  }

  randomString[length] = '\0';

  return randomString;
}

/* 15 points */
double test_is_unique(void) {
  size_t passed = 0;
  const double points = 15.;

  char *s1, *s2;
  size_t len;

  printf("-------------------------\n");
  printf("Function %s() ", __func__);

  for (size_t i = 0; i < N_TESTS; i++) {
    len = 1 + ((size_t)(rand() % 30));
    if ((s1 = randstring(len)) == NULL) {
      error_no_memory();
      continue;
    }
    if ((s2 = malloc(sizeof(char) * (len + 1))) == NULL) {
      error_no_memory();
      free(s1);
      continue;
    }

    strcpy(s2, s1);

    passed += (my_is_unique(s1) == is_unique(s2));

    free(s1);
    free(s2);
  }

  return points * ((double)passed) / ((double)N_TESTS);
}

/* 20 points */
double test_print_number(void) {
  unsigned char possible_nums[] = {1, 2, 4, 5, 6, 7, 9};
  unsigned char num;
  int n_nums;

  printf("-------------------------\n");
  printf(
      "The following output is a random number from 0-9 printed in all 4 "
      "different reflections. First my implementation and then the student "
      "implementation. Grade is given if they are visually identical.\n");

  n_nums = sizeof(possible_nums) / sizeof(possible_nums[0]);
  printf("n_nums = %d\n", n_nums);

  for (size_t i = 0; i < 3; i++) rand();

  num = ((unsigned char)possible_nums[rand() % n_nums]);

  printf("My number %d with NO reflection:\n", num);
  my_print_number(num, my_NO);
  printf("Student number %d with NO reflection:\n", num);
  print_number(num, NO);

  printf("My number %d with x_axis reflection:\n", num);
  my_print_number(num, my_x_axis);
  printf("Student number %d with x_axis reflection:\n", num);
  print_number(num, x_axis);

  printf("My number %d with y_axis reflection:\n", num);
  my_print_number(num, my_y_axis);
  printf("Student number %d with y_axis reflection:\n", num);
  print_number(num, y_axis);

  printf("My number %d with xy_axis reflection:\n", num);
  my_print_number(num, my_xy_axis);
  printf("Student number %d with xy_axis reflection:\n", num);
  print_number(num, xy_axis);

  return 0.0;
}

static node_t *create_node(void) {
  node_t *newNode = (node_t *)malloc(sizeof(node_t));

  if (newNode == NULL) return NULL;

  newNode->data = rand() % MAX_DATA;
  newNode->link = NULL;

  return newNode;
}

static int _init_s_LL(list_t **s_LL) {
  if ((*s_LL = (list_t *)malloc(sizeof(list_t))) == NULL) {
    error_no_memory();
    return 1;
  }

  (*s_LL)->head = NULL;
  (*s_LL)->tail = NULL;

  return 0;
}

double test_insert_node(void) {
  const size_t ADD_N = 5;
  node_t *t_node;

  my_list_t *my_LL = NULL;
  list_t *s_LL = NULL;

  printf("-------------------------\n");
  printf("Function %s()\n", __func__);

  if (_init_s_LL(&s_LL)) return 0.0;
  if ((my_LL = (my_list_t *)malloc(sizeof(my_list_t))) == NULL) {
    error_no_memory();
    free(s_LL);
    return 0.0;
  }

  // Test with ADD_N nodes
  for (size_t i = ((size_t)0); i < ADD_N; i++) {
    if ((t_node = create_node()) == NULL) {
      error_no_memory();

      my_free_LL(my_LL);
      free(my_LL);
      free(s_LL);

      return 0.0;
    }

    // Get data for node
    insert_node(s_LL, t_node);
    my_insert_node(my_LL, (my_node_t *)t_node);
  }

  printf("\nAfter adding %zu nodes, the LL suppose to look like:\n", ADD_N);
  my_print_LL(my_LL, my_ASC);

  printf("\nThe student LL is:\n");
  print_LL(s_LL, ASC);
  printf("\n");

  my_free_LL(my_LL);
  free(s_LL);
  free(my_LL);

  return 0.0;
}

static void _free_s_LL(list_t *LL) {
  node_t *curr = LL->head;
  node_t *prev = NULL;
  node_t *next;

  while (curr != NULL) {
    next = (node_t *)__XOR(prev, curr->link);
    prev = curr;
    free(curr);
    curr = next;
  }
}

double test_remove_node(void) {
  const size_t ADD_N = 5;
  list_t *s_LL = NULL;

  printf("-------------------------\n");
  printf("Function %s()\n", __func__);

  if (_init_s_LL(&s_LL)) return 0.0;

  for (size_t i = ((size_t)0); i < ADD_N; i++) {
    if (push(s_LL, rand() % MAX_DATA)) {
      printf("PUSH FAIL. Grade remove_node by hand.\n");
      return 0.0;
    }
  }

  printf("\nThe following list was created:\n");
  print_LL(s_LL, ASC);

  printf("\nCalling remove_node for half the nodes in LL...\n");
  for (size_t i = ((size_t)0); i < ADD_N / 2; i++) {
    remove_node(s_LL, ((unsigned long)(i % 2 ? s_LL->head : s_LL->tail)));
  }

  printf("\nLL after deleting half the list:\n");
  print_LL(s_LL, ASC);
  printf("\n");

  for (size_t i = ((size_t)ADD_N / 2); i < ADD_N; i++) {
    remove_node(s_LL, (unsigned long)s_LL->head);
  }

  printf("\nFinal LL after removing all nodes:\n");
  print_LL(s_LL, ASC);
  printf("\n");

  // Free all nodes just in case that the student didn't implement remove_node
  _free_s_LL(s_LL);
  free(s_LL);

  return 0.0;
}

static double *func_points;

int main(void) {
  double total_points;
  int n_funcs;
  double (*functions[])(void) = {&test_swap,
                                 &test_has_odd_number_of_bits_set,
                                 &test_turn_k_bit_off,
                                 &test_k_bit_is_on,
                                 &test_toggle_k_bit,
                                 &test_is_palindrome,
                                 &test_copy_reverse_bits,
                                 &test_is_unique,
                                 &test_print_number,
                                 &test_insert_node,
                                 &test_remove_node};

  pid_t pid;

  n_funcs = sizeof(functions) / sizeof(functions[0]);
  total_points = 0.0;
  srand((unsigned int)time(NULL));

  func_points = mmap(NULL, sizeof *func_points, PROT_READ | PROT_WRITE,
                     MAP_SHARED | MAP_ANONYMOUS, -1, 0);

  for (int i = 0; i < n_funcs; i++) {
    pid = fork();

    if (pid < ((pid_t)0)) {
      fprintf(stderr, "fork() did not work: %s.\n Try running it again.\n",
              strerror(errno));
      return 1;
    }

    if (pid == ((pid_t)0)) {
      // We are the child.
      *func_points = -1.0;
      *func_points = functions[i]();

      return 0;
    }

    // Wait for children
    wait(NULL);

    if (*func_points < 0.0) {
      printf(
          "FAIL by student function, grade it manually and give no more than "
          "half of the full credit.\n");
    } else {
      printf("got %f points.\n", *func_points);
      total_points += *func_points;
    }
  }

  printf("%f\n", total_points);

  munmap(func_points, sizeof *func_points);

  return 0;
}
