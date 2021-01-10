#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "ecb.h"
#include "des.h"

char* stringToBinary(char* s) {
    if(s == NULL) return 0; /* no input string */
    size_t len = strlen(s);
    char *binary = malloc(len*8 + 1); // each char is one byte (8 bits) and + 1 at the end for null terminator
    binary[0] = '\0';
    for(size_t i = 0; i < len; ++i) {
        char ch = s[i];
        for(int j = 7; j >= 0; --j){
            if(ch & (1 << j)) {
                strcat(binary,"1");
            } else {
                strcat(binary,"0");
            }
        }
    }
    return binary;
}

char* ecb_crypt(char* message, u_int64_t key)
{
    size_t i;
    int j;
    char* result = malloc(64*sizeof(char) + 1);
    size_t len = strlen(message);
    size_t difference = 8 - len % 8;
    if (difference != 8)
    for(i=0; i<len; i++)
    {
        strcat(message, "X");
    }
    len2 = strlen(message)/8;
    u_int64_t* binary = malloc(64*len2);
    char** temp = malloc(len2*sizeof(char*))
    for(i=0; i<len2; i++)
    {
        temp[(int)i]=malloc(8*sizeof(char)+1);
    }
    for(i=0; i<len2; i++)
    {
        for(j=0;j<8;j++)
        {
            temp[(int)i][j]=message[((int)i)*8+j];
        }
    }
    for(i=0; i<len2; i++)
    {
        binary[(int)i] = des_ciphertext(temp[(int)i], key);
        for(j=0; j<8; j++)
        {
            strcat(result,binary[(int)i][j]);
        }
    }
    return result;
}