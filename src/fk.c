#include <stdio.h>
#include <stdlib.h>
#include "fk.h"
#include "keygen.h"

int **sbox_creation(int type){

	int **sbox;
	if ((sbox = (int **)malloc(4 * sizeof(int*))) == NULL){
		perror("Memory allocation failed. Exit.\n");
		exit(-1);
	}
	int i, j, d, u;
	for (i = 0; i < 4; i++){
		if ((sbox[i] = (int *)malloc(16 * sizeof(int))) == NULL){
			perror("Memory allocation failed. Exit.\n");
			exit(-1);
		}
	}

	//We'll be using eight text files that contain the values of each slot of each sbox, 
	//in order to fill them.
	FILE *f;
	char *filename;

	if (type == 0)
		filename = "../sbox1.txt";
	else if (type == 1)
		filename = "../sbox2.txt";
	else if (type == 2)
		filename = "../sbox3.txt";
	else if (type == 3)
		filename = "../sbox4.txt";
	else if (type == 4)
		filename = "../sbox5.txt";
	else if (type == 5)
		filename = "../sbox6.txt";
	else if (type == 6)
		filename = "../sbox7.txt";
	else if (type == 7)
		filename = "../sbox8.txt";
	
	if ((f = fopen(filename, "r")) == NULL){
		perror("Something went wrong. Abort.\n");
		exit(-1);
	}

	for (i = 0; i < 4; i++){
		for (j = 0; j < 16; j++){
          		d = fgetc(f) - '0'; //To retrieve the actual integer and not an ASCII code
            		u = fgetc(f) - '0';
			sbox[i][j] = d*10+u; //All numbers are written with 2 digits in the sboxes (for example 14 is 14 and 4 is 04)
		}
	}
	fclose(f);
	return(sbox);

}

u_int64_t sbox_mapping(u_int64_t block, int box){
	int **sbox = sbox_creation(box);
	
	u_int64_t copy = block;
    u_int8_t result_line = 0;
    u_int8_t result_column = 0;
    if(copy & (1 << 5)) {
        result_line |= 2; //00000010
    }
    copy = block;
    if(copy & 1){
        result_line |= 1; //00000001
    }
    copy = block;
    if((copy &(15 << 1)) >> 1){ //15=00001111, we use it to get 4 digits, the 2nd, 3rd, 4th, and 5th
        result_column |= ((copy &(15 << 1)) >> 1);
    }

	return sbox[result_line][result_column];
}

u_int64_t f (u_int32_t R, u_int64_t K)
{
  u_int64_t result;
  u_int64_t perm = permutation (R, 5);
	u_int64_t KplusE = perm ^ K;
	u_int64_t SBone = sbox_mapping(six_bit_select(KplusE, 0), 0) << 28;
	u_int64_t SBtwo = sbox_mapping(six_bit_select(KplusE, 1), 1) << 24;
	u_int64_t SBthree = sbox_mapping(six_bit_select(KplusE, 2), 2) << 20;
	u_int64_t SBfour = sbox_mapping(six_bit_select(KplusE, 3), 3) << 16;
	u_int64_t SBfive = sbox_mapping(six_bit_select(KplusE, 4), 4) << 12;
	u_int64_t SBsix = sbox_mapping(six_bit_select(KplusE, 5), 5) << 8;
	u_int64_t SBseven = sbox_mapping(six_bit_select(KplusE, 6), 6) << 4;
	u_int64_t SBeight = sbox_mapping(six_bit_select(KplusE, 7), 7);
	
	result = SBone | SBtwo | SBthree | SBfour | SBfive | SBsix | SBseven | SBeight;
	result = permutation(result, 32);
	return result;
}

u_int64_t six_bit_select (u_int64_t key, int part)
{
	u_int64_t masque = 63; // 63 = 00...0111111
	u_int64_t result = 0;
	result|= ((key & (masque << 6*(7-part))) >> 6*(7-part)); 
	return result;
}

u_int64_t lr_gen(u_int64_t IP, u_int64_t* K_list)
{
	int i;
	u_int32_t L[17];
	L[0]=leftmost_thirty_two_bits(IP);
	u_int32_t R[17];
	R[0]=rightmost_thirty_two_bits(IP);

	for(i=0; i<16; i++)
	{
		L[i+1]=R[i];
		R[i+1]=L[i] ^ rightmost_thirty_two_bits(f(R[i], K_list[i]));
	}
	u_int64_t result = 0;
	result = ((result | R[16]) << 32 ) | L[16]; //to return R16L16
	return result;
}
