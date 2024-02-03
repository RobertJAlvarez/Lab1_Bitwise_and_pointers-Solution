#include <errno.h>      //errno
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>  //fork()  waitpid()
#include <sys/wait.h>   //waitpid()
#include <time.h>
#include <unistd.h>     //fork()
#include <string.h>     //strncpy()

#include "DoubleLL.h"
#include "bitwise_f.h"
#include "my_DoubleLL.h"
#include "my_bitwise_f.h"

#define N_TESTS ((size_t)1000)

static void error_no_memory(void) {
  return;
}

/* 10 points */
double test_swap(void) {
  short n1, n2, n3, n4;
  size_t passed = 0;
  const double points = 10.;

  for (size_t i = 0; i < N_TESTS; i++) {
    n1 = n3 = (short)rand();
    n2 = n4 = (short)rand();

    my_swap(&n1, &n2);

    passed += ((n1 == n4) && (n2 == n3));
  }

  return points * ((double)passed) / ((double)N_TESTS);
}

static void print_binary(int n) {
  const int N_BITS = (sizeof(n) * 8);

  for (int i = 0; i < N_BITS; i++) {
    if (n & 1)
      printf("1");
    else
      printf("0");

    n >>= 1;
  }
  printf("\n");
}

/* 10 points */
double test_has_odd_number_of_bits_set(void) {
  int n1, n2;
  size_t passed = 0;
  const double points = 10.;

  for (size_t i = 0; i < N_TESTS; i++) {
    n1 = n2 = rand();

    passed +=
        (my_has_odd_number_of_bits_set(n1) == has_odd_number_of_bits_set(n2));
  }

  return points * ((double)passed) / ((double)N_TESTS);
}

/* 5 points */
double test_turn_k_bit_off(void) {
  int n1, n2;
  short k;
  size_t passed = 0;
  const double points = 5.;

  for (size_t i = 0; i < N_TESTS; i++) {
    n1 = n2 = rand();
    k = ((short)(((unsigned long)rand()) % (sizeof(int) * 8)));

    passed += (my_turn_k_bit_off(n1, k) == turn_k_bit_off(n2, k));
  }

  return points * ((double)passed) / ((double)N_TESTS);
}

/* 5 points */
double test_k_bit_is_on(void) {
  int n1, n2;
  short k;
  size_t passed = 0;
  const double points = 5.;

  for (size_t i = 0; i < N_TESTS; i++) {
    n1 = n2 = rand();
    k = ((short)(((unsigned long)rand()) % (sizeof(int) * 8)));

    passed += (my_k_bit_is_on(n1, k) == k_bit_is_on(n2, k));
  }

  return points * ((double)passed) / ((double)N_TESTS);
}

/* 5 points */
double test_toggle_k_bit(void) {
  int n1, n2;
  short k;
  size_t passed = 0;
  const double points = 5.;

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

  for (size_t i = 0; i < N_TESTS; i++) {
    n1 = n2 = rand();

    passed += (my_is_palindrome(n1) == is_palindrome(n2));
  }

  return points * ((double)passed) / ((double)N_TESTS);
}

/* 15 points */
double test_copy_reverse_bits(void) {
  size_t passed = 0;
  const double points = 15.;

  short n1, n2;

  for (size_t i = 0; i < N_TESTS; i++) {
    n1 = n2 = ((short)rand());

    passed += (my_copy_reverse_bits(n1) == copy_reverse_bits(n2));
  }

  return points * ((double)passed) / ((double)N_TESTS);
}

char *randstring(size_t length) {
  static char charset[] =
      "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789`~!@#$%^&*"
      "()_+-=[]{}\\|;:,<.>/?";
  char *randomString = NULL;

  if (length) {
    if ((randomString = malloc(sizeof(char) * (length + 1))) == NULL) return NULL;

    if (randomString) {
      for (size_t n = 0; n < length; n++) {
        int key = rand() % (int)(sizeof(charset) - 1);
        randomString[n] = charset[key];
      }

      randomString[length] = '\0';
    }
  }

  return randomString;
}

/* 15 points */
double test_is_unique(void) {
  size_t passed = 0;
  const double points = 15.;

  char *s1, *s2;
  size_t len;

  for (size_t i = 0; i < N_TESTS; i++) {
    len = ((size_t) (rand() % 30)); // 92 possible characters
    if ((s1 = randstring(len)) == NULL) error_no_memory();
    if ((s2 = malloc(sizeof(char) * (len + 1))) == NULL) error_no_memory();

    strncpy(s2, s1, len);

    passed += (my_is_unique(s1) == is_unique(s2));

    free(s1);
    free(s2);
  }

  return points * ((double)passed) / ((double)N_TESTS);
}

/* 20 points */
double test_print_number(void) {
  size_t passed = 0;
  const double points = 20.;

  return points * ((double)passed) / ((double)N_TESTS);
}

int main(void) {
  double total_points = 0.0;

  srand((unsigned int)time(NULL));

  total_points += test_swap();
  total_points += test_has_odd_number_of_bits_set();
  total_points += test_turn_k_bit_off();
  total_points += test_k_bit_is_on();
  total_points += test_toggle_k_bit();
  total_points += test_is_palindrome();
  total_points += test_copy_reverse_bits();
  total_points += test_print_number();
  total_points += test_is_unique();

  printf("%f\n", total_points);

  return 0;
}
