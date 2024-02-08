#include <math.h>
#include <stdio.h>

#include "my_bitwise_f.h"

#define K_BIT_ON(N, K) (N | (1 << (K - 1)))
#define K_BIT_OFF(N, K) (N & ~(1 << (K - 1)))
#define CHECK_K_BIT_ON(N, K) (N & (1 << (K - 1)))
#define TOGGLE_K_BIT(N, K) (N ^ (1 << (K - 1)))

/* Swap two short numbers without the need of a\
 * third variable.
 * Only use: ^
 */
void my_swap(short *n1, short *n2) {
  *n1 ^= *n2;
  *n2 ^= *n1;
  *n1 ^= *n2;
}

// Parity: Brian Kernighan's approach
int my_has_odd_number_of_bits_set(int n) {
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
int my_turn_k_bit_off(const int n, const short k) {
  return n & ~(1 << (k - 1));
}

/* Return true if the k bit of n is on. False otherwise.
 * Only use: & and <<
 */
int my_k_bit_is_on(const int n, const short k) { return n & (1 << (k - 1)); }

/* Turn on the k bit of n if it is off or turn it off if it
 * is on.
 * Only use: ^ and <<
 */
int my_toggle_k_bit(const int n, const short k) { return n ^ (1 << (k - 1)); }

/* Return 1 if the bit of n are palindrome
 * Only use: <<, |, & and >>
 */
int my_is_palindrome(const int n) {
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
short my_copy_reverse_bits(short n) {
  short reverse = 0;

  while (n) {
    short pos = ((short)log2(n & -n)) + 1;
    reverse |= (1 << (sizeof(n) * 8 - ((unsigned long)pos)));
    n &= (n - 1);
  }

  return reverse;
}

static unsigned char __get_i_row(const reflection_t refl,
                                 const unsigned char NROWS,
                                 const unsigned char row) {
  return refl == my_x_axis || refl == my_xy_axis ? NROWS - 1 - row : row;
}

static unsigned char __calculate_shifts(const reflection_t refl,
                                        const unsigned char NCOLS,
                                        const unsigned char col) {
  return refl == my_y_axis || refl == my_xy_axis ? NCOLS - 1 - col : col;
}

/* Numbers is a 2D array of
 * Only use: << and &
 */
void my_print_number(const unsigned char number, const reflection_t refl) {
  const unsigned char NROWS = 12;
  const unsigned char NCOLS = 8;

  unsigned char rowBits;
  unsigned char colMask;

  for (unsigned char row = 0; row < NROWS; ++row) {
    rowBits = my_font_12x8[number][__get_i_row(refl, NROWS, row)];
    for (unsigned char col = 0; col < NCOLS; ++col) {
      colMask = ((unsigned char)(1 << __calculate_shifts(refl, NCOLS, col)));
      putchar((rowBits & colMask) ? '*' : ' ');
    }
    putchar('\n');
  }
}

int my_is_unique(const char *s) {
  int32_t checker[] = {0, 0, 0, 0, 0, 0, 0, 0};
  int i, val;
  int32_t mask;

  if (s == NULL) return 1;

  for (const char *c = s; *c != '\0'; ++c) {
    i = *c / 32;
    val = *c - 32 * i;
    mask = (1 << val);
    if ((checker[i] & mask) > 0) return 0;
    checker[i] |= mask;
  }

  return 1;
}
