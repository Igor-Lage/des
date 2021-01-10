#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "ebc.h"
#include "des.h"
#include "keygen.h"

//transforms a string of 0 and 1 of lenght 64 into the 64-bit int it represents
u_int64_t stringToBinary(char* ch) {
    u_int64_t masque = 1;
    u_int64_t binary = 0;
    for(size_t i = 0; i < 8; ++i) {
        for(int j = 7; j >= 0; --j){
            if(ch[i] & (1 << j)) {
                binary |= (masque << (8*(7-i) + j));
            }
        }
    }
    return binary;
}

//transforms a 64-bit int into a string of 0 and 1s
char* binaryToString (u_int64_t message)
{
    int i;
    u_int64_t masque = 1;
    char* result = (char*)malloc(64*sizeof(char)+1); // each char is one byte (8 bits) and + 1 at the end for null terminator
    result[0] = '\0';
    for(i=63; i >= 0; i--)
    {
	if( message & (masque << i))
	{
	    strcat(result, "1");
	}
	else
	{
	    strcat(result, "0");
	}
    }
    return result;
}

//transforms un string of 0 and 1 of lenght 8 into the corresponding ascii character
char asciiConvert(char* message)
{
	u_int8_t letter=0;
	char result;
	int i;
	for(i=0; i<8; i++)
	{
		if(message[i] == '1')
		{
			letter |= 1<<7-i;
		}
	}
	result = letter;
	return result;
}

//transforms a string of 0 and 1s into the 64 bits integer it represents
u_int64_t stringTranslate(char* string)
{
	u_int64_t result = 0;
	u_int64_t masque = 1;
	int i;
	for (i=0; i<64; i++)
	{
		if (string[i]=='1')
		{
			result |= (masque << 63-i);
		}
	}
	return result;
}

char* ebc_crypt(char* message, u_int64_t key)
{
    size_t i;
    int j;
    size_t len = strlen(message);
    char* copy = malloc(len + 8*sizeof(char) +1);
    strcpy(copy, message);
	
    for(i=0; i<(8-(len%8)); i++)
    {
	strcat(copy, "X"); //pads the message so we can split it into 64-bits blocks (meaning there is 8*i characters in the message
    }
	
    size_t len2 = strlen(copy)/8;
    char* result = (char*)malloc(64*len2*sizeof(char) + 1);
    result[0]='\0';
	
    char buffer[9];
    u_int64_t* binary = (u_int64_t*)malloc(len2 * sizeof(u_int64_t));
    for(i=0; i<len2; i++)
    {
        memcpy( buffer, &copy[i*8], 8);
	buffer[8] = '\0';
	binary[i] = stringToBinary(buffer);
    }
	
    u_int64_t plaintext;
    for(i=0; i<len2; i++)
    {
	plaintext = (u_int64_t)binary[(int)i];
        binary[(int)i] = des_ciphertext(plaintext, key); //applies DES on each 64-bit block of the message
        strcat(result,binaryToString(binary[(int)i])); //concatenates the 64-bit blocks (transformed into strings of length 64)
    }
    return result;
}

char* ebc_decrypt(char* message, u_int64_t key)
{
	size_t i,cur_len;
	int j;
	size_t len = strlen(message)/64;
	
	char* result = (char*)malloc(len*8*sizeof(char)+1);
	result[0]='\0';
	
	char** ascii = (char**)malloc(len*sizeof(char*));
	char buffer[65];
	char buffer2[9];
	buffer[64] = '\0';
	buffer2[8] = '\0';
	char character;
	
	for(i=0; i<len; i++)
	{
		memcpy(buffer, &message[i*64], 64);
		ascii[(int)i] = (char*)malloc(64*sizeof(char)+1);
		ascii[(int)i] = binaryToString(des_plaintext(stringTranslate(buffer),key)); //applies the DES decryption algorithm to each 64-bit block of the ciphertext
		for(j=0; j<8; j++)
		{
			memcpy(buffer2, &ascii[(int)i][8*j], 64);
			character = asciiConvert(buffer2); 
			
			cur_len = strlen(result);
			result[cur_len] = character; 
			result[cur_len+1] = '\0'; //concatenates the decrypted letter to the result
		}
	}
	return result;
}
