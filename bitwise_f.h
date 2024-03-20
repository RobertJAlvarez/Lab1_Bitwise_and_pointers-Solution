#ifndef __BITWISE_F_H__
#define __BITWISE_F_H__

typedef enum { NO, x_axis, y_axis, xy_axis } reflection_t;

extern const unsigned char font_12x8[10][12];

/* [10 points] Swap two short numbers without the need of a
 * third variable.
 * Only use: ^
 */
void swap(short *n1, short *n2);

/* [10 points] Return 0 if the variable has an even number of
 * bits set and 1 if it has an odd number of bits set.
 * Only use: ~ and &
 */
int has_odd_number_of_bits_set(int n);

/* [5 points] Turn k bit of n off
 * Only use: &, ~ and <<
 */
int turn_k_bit_off(const int n, const short k);

/* [5 points] Return true if the k bit of n is on. False otherwise.
 * Only use: & and <<
 */
int k_bit_is_on(const int n, const short k);

/* [5 points] Turn on the k bit of n if it is off or turn it off if it
 * is on.
 * Only use: ^ and <<
 */
int toggle_k_bit(const int n, const short k);

/* [15 points] Return 1 if the bit of n are palindrome
 * Only use: <<, |, & and >>
 */
int is_palindrome(const int n);
int is_palindrome2(const int n);

/* [15 points] Return an int that have the same bits of n but in reverse.
 * Only use: &, | and <<
 */
short copy_reverse_bits(short n);

/* [15 points] Return 1 if all the its characters are unique, 0 otherwise.
 * Only use: |, & and <<
 */
int is_unique(const char *s);

/* [20 points] Numbers is a 2D array of
 * Only use:
 */
void print_number(const unsigned char number, const reflection_t refl);

#endif
