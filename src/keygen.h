#ifndef __KEYGEN_H__
#define __KEYGEN_H__

#include <stddef.h>

u_int64_t permutation(u_int64_t key, int perm);

void print_bits(u_int64_t word, int range);

u_int64_t rightmost_twenty_eight_bits(u_int64_t word);

u_int64_t leftmost_twenty_eight_bits(u_int64_t word);

u_int64_t rightmost_thirty_two_bits(u_int64_t word);

u_int64_t lefttmost_thirty_two_bits(u_int64_t word);

u_int64_t* sixteen_key_generation(u_int64_t key);

u_int32_t* sixteen_shift(u_int32_t key);

u_int32_t shift(u_int32_t key);

#endif