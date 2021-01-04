#ifndef __FK_H__
#define __FK_H__

#include <stddef.h>

int **sbox_creation(int type);

u_int64_t sbox_mapping(u_int64_t block, int box);

u_int64_t f (u_int32_t R, u_int64_t K);

u_int64_t six_bit_select (u_int64_t key, int part);

u_int64_t lr_gen(u_int64_t IP, u_int64_t* K_list);

#endif
