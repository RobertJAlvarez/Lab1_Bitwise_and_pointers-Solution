#include <errno.h>  //errno
#include <stdio.h>
#include <stdlib.h>
#include <string.h>     //strncpy()
#include <sys/mman.h>   //mmap()
#include <sys/types.h>  //fork()  waitpid()
#include <sys/wait.h>   //waitpid()
#include <time.h>
#include <unistd.h>  //fork()

#include "DoubleLL.h"
#include "bitwise_f.h"
#include "my_DoubleLL.h"
#include "my_bitwise_f.h"

#define N_TESTS ((size_t)1000)

static void error_no_memory(void) {
  fprintf(
      stderr,
      "No more memory available, consider decreasing number size of copy.\n");
  return;
}

/* 10 points */
double test_swap(void) {
  size_t passed = 0;
  const double points = 10.;

  short n1, n2, n3, n4;

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

  printf("Function %s() ", __func__);

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
  // const int n_tests = 100;

  char *s1, *s2;
  size_t len;

  printf("Function %s() ", __func__);

  for (size_t i = 0; i < N_TESTS; i++) {
    len = 1 + ((size_t)(rand() % 30));  // 92 possible characters
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
  size_t passed = 0;
  const double points = 20.;

  return points * ((double)passed) / ((double)N_TESTS);
}

static double *func_points;

int main(void) {
  double total_points = 0.0;
  static const int N_FUNC = 8;
  double (*functions[N_FUNC])(void) = {&test_swap,
                                       &test_has_odd_number_of_bits_set,
                                       &test_turn_k_bit_off,
                                       &test_k_bit_is_on,
                                       &test_toggle_k_bit,
                                       &test_is_palindrome,
                                       &test_copy_reverse_bits,
                                       &test_is_unique};

  pid_t pid;

  total_points = 0.0;
  srand((unsigned int)time(NULL));

  func_points = mmap(NULL, sizeof *func_points, PROT_READ | PROT_WRITE,
                     MAP_SHARED | MAP_ANONYMOUS, -1, 0);

  for (int i = 0; i < N_FUNC; i++) {
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
          "fail by student function, grade it manually and give no more than "
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
