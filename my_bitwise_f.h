#ifndef __MY_BITWISE_F_H__
#define __MY_BITWISE_F_H__

typedef enum { my_NO, my_x_axis, my_y_axis, my_xy_axis } reflection_t;

extern const unsigned char my_font_12x8[10][12];

/* [10 points] Swap two short numbers without the need of a
 * third variable.
 * Only use: ^
 */
void my_swap(short *n1, short *n2);

/* [10 points] Return 0 if the variable has an even number of
 * bits set and 1 if it has an odd number of bits set.
 * Only use: ~ and &
 */
int my_has_odd_number_of_bits_set(int n);

/* [5 points] Turn k bit of n off
 * Only use: &, ~ and <<
 */
int my_turn_k_bit_off(const int n, const short k);

/* [5 points] Return true if the k bit of n is on. False otherwise.
 * Only use: & and <<
 */
int my_k_bit_is_on(const int n, const short k);

/* [5 points] Turn on the k bit of n if it is off or turn it off if it
 * is on.
 * Only use: ^ and <<
 */
int my_toggle_k_bit(const int n, const short k);

/* [15 points] Return 1 if the bit of n are palindrome
 * Only use: <<, |, & and >>
 */
int my_is_palindrome(const int n);
int my_is_palindrome2(const int n);

/* [15 points] Return an int that have the same bits of n but in reverse.
 * Only use: &, | and <<
 */
short my_copy_reverse_bits(short n);

/* [15 points] Return 1 if all the its characters are unique, 0 otherwise.
 * Only use: |, & and <<
 */
int my_is_unique(const char *s);

/* [20 points] Numbers is a 2D array of
 * Only use:
 */
void my_print_number(const unsigned char number, const reflection_t refl);

#endif
