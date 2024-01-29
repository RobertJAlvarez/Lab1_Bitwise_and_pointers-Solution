#include <math.h>
#include <stdio.h>

#include "bitwise_f.h"

#define K_BIT_ON(N, K) (N | (1 << (K - 1)))
#define K_BIT_OFF(N, K) (N & ~(1 << (K - 1)))
#define CHECK_K_BIT_ON(N, K) (N & (1 << (K - 1)))
#define TOGGLE_K_BIT(N, K) (N ^ (1 << (K - 1)))

/* Swap two short numbers without the need of a\
 * third variable.
 * Only use: ^
 */
void swap(short *n1, short *n2) {
  *n1 ^= *n2;
  *n2 ^= *n1;
  *n1 ^= *n2;
}

// Parity: Brian Kernighan's approach
int has_odd_number_of_bits_set(int n) {
  int parity = 0;

  while (n) {
    parity = ~parity;
    n &= (n - 1);
  }

  return parity & 1;
}

/* Turn k bit of n off
 * Only use: &, ~ and <<
 */
int turn_k_bit_off(const int n, const short k) { return n & ~(1 << (k - 1)); }

/* Return true if the k bit of n is on. False otherwise.
 * Only use: & and <<
 */
int k_bit_is_on(const int n, const short k) { return n & (1 << (k - 1)); }

/* Turn on the k bit of n if it is off or turn it off if it
 * is on.
 * Only use: ^ and <<
 */
int toggle_k_bit(const int n, const short k) { return n ^ (1 << (k - 1)); }

/* Return 1 if the bit of n are palindrome
 * Only use: <<, |, & and >>
 */
int is_palindrome(const int n) {
  int rev = 0;
  int k = n;

  while (k) {
    rev = (rev << 1) | (k & 1);
    k >>= 1;
  }

  return n == rev;
}

/* Return a short that have the same bits of n but in reverse.
 * Only use: &, | and <<
 */
short copy_reverse_bits(short n) {
  short reverse = 0;

  while (n) {
    short pos = log2(n & -n) + 1;
    reverse |= (1 << (sizeof(n) * 8 - pos));
    n &= (n - 1);
  }

  return reverse;
}

static unsigned char __get_i_row(const enum reflection refl,
                                 const unsigned char NROWS,
                                 const unsigned char row) {
  return refl == x_axis || refl == xy_axis ? NROWS - 1 - row : row;
}

static unsigned char __calculate_shifts(const enum reflection refl,
                                        const unsigned char NCOLS,
                                        const unsigned char col) {
  return refl == y_axis || refl == xy_axis ? NCOLS - 1 - col : col;
}

/* Numbers is a 2D array of
 * Only use: << and &
 */
void print_number(const unsigned char number, const enum reflection refl) {
  const unsigned char NROWS = 12;
  const unsigned char NCOLS = 8;

  unsigned char rowBits;
  unsigned char colMask;

  for (unsigned char row = 0; row < NROWS; ++row) {
    rowBits = font_12x8[number][__get_i_row(refl, NROWS, row)];
    for (char col = 0; col < NCOLS; ++col) {
      colMask = 1 << __calculate_shifts(refl, NCOLS, col);
      putchar((rowBits & colMask) ? '*' : ' ');
    }
    putchar('\n');
  }
}

int is_unique(const char *s) {
  int32_t checker[] = {0, 0, 0, 0, 0, 0, 0, 0};
  int i, val;

  for (const char *c = s; *c; ++c) {
    i = *c / 32;
    val = *c - 32 * i;
    if ((checker[i] & (1 << val)) > 0) return 0;
    checker[i] |= (1 << val);
  }

  return 1;
}
