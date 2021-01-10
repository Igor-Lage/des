#ifndef __ECB_H__
#define __ECB_H__

#include <stddef.h>

u_int64_t stringToBinary(char* s);

char* binaryToString (u_int64_t message);

char asciiConvert(char* message);

u_int64_t stringTranslate(char* string);

char* ecb_crypt(char* message, u_int64_t key);

char* ecb_decrypt(char* message, u_int64_t key);

#endif
