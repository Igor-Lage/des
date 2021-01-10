#ifndef __ECB_H__
#define __ECB_H__

#include <stddef.h>

char* stringToBinary(char* s);

char* ecb_crypt(char* message, u_int64_t key);

#endif