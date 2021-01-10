#ifndef __EBC_H__
#define __EBC_H__

#include <stddef.h>

u_int64_t stringToBinary(char* s);

char* binaryToString (u_int64_t message);

char asciiConvert(char* message);

u_int64_t stringTranslate(char* string);

char* ebc_crypt(char* message, u_int64_t key);

char* ebc_decrypt(char* message, u_int64_t key);

#endif
