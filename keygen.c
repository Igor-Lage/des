#include <stdio.h>
#include <stdlib.h>
#include "keygen.h"

u_int64_t permutation(u_int64_t key, int perm){

	int i;
	u_int64_t result = 0;
	u_int64_t masque = 1;

	//PC-1
	if (perm == 56){
		int perm_table[56] = {57, 49, 41, 33, 25, 17, 9, 
                                1, 58, 50, 42, 34, 26, 18, 
                                10, 2, 59, 51, 43, 35, 27, 
                                19, 11, 3, 60, 52, 44, 36, 
                                63, 55, 47, 39, 31, 23, 15, 
                                7, 62, 54, 46, 38, 30, 22, 
                                14, 6, 61, 53, 45, 37, 29, 
                                21, 13, 5, 28, 20, 12, 4};
		for (i = 0; i < 56; i++){
			result <<= 1;
			if (key & (masque << 64 - perm_table[i]))
			result |= 1;
		}
    }

    //PC-2
    else if (perm == 48){
        int perm_table[48] = {14, 17, 11, 24, 1, 5, 
                        3, 28, 15, 6, 21, 10, 
                        23, 19, 12, 4, 26, 8, 
                        16, 7, 27, 20, 13, 2, 
                        41, 52, 31, 37, 47, 55, 
                        30, 40, 51, 45, 33, 48, 
                        44, 49, 39, 56, 34, 53, 
                        46, 42, 50, 36, 29, 32};
        for (i = 0; i < 48; i++){
			result <<= 1;
			if (key & (masque << 56 - perm_table[i]))
			result |= 1;
		}
    }

    //IP
    else if (perm == 1){
        int perm_table[64] = {58, 50, 42, 34, 26, 18, 10, 2, 
                            60, 52, 44, 36, 28, 20, 12, 4, 
                            62, 54, 46, 38, 30, 22, 14, 6, 
                            64, 56, 48, 40, 32, 24, 16, 8, 
                            57, 49, 41, 33, 25, 17, 9, 1, 
                            59, 51, 43, 35, 27, 19, 11, 3, 
                            61, 53, 45, 37, 29, 21, 13, 5, 
                            63, 55, 47, 39, 31, 23, 15, 7};
        for (i = 0; i < 64; i++){
            result <<=1;
            if (key & (masque << 64 - perm_table[i]))
			result |= 1;
        }
    }    

    //IP -1
    else if (perm == -1){
        int perm_table[64] = {40, 8, 48, 16, 56, 24, 64, 32, 
                        39, 7, 47, 15, 55, 23, 63, 31, 
                        38, 6, 46, 14, 54, 22, 62, 30, 
                        37, 5, 45, 13, 53, 21, 61, 29, 
                        36, 4, 44, 12, 52, 20, 60, 28, 
                        35, 3, 43, 11, 51, 19, 59, 27, 
                        34, 2, 42, 10, 50, 18, 58, 26, 
                        33, 1, 41, 9, 49, 17, 57, 25};
        for (i = 0; i < 64; i++){
            result <<=1;
            if (key & (masque << 64 - perm_table[i]))
            result |= 1;
        }
    }

    //E
    else if (perm == 5){
        int perm_table[48] = {32, 1, 2, 3, 4, 5, 
                        4, 5, 6, 7, 8, 9, 
                        8, 9, 10, 11, 12, 13, 
                        12, 13, 14, 15, 16, 17, 
                        16, 17, 18, 19, 20, 21, 
                        20, 21, 22, 23, 24, 25, 
                        24, 25, 26, 27, 28, 29, 
                        28, 29, 30, 31, 32, 1};
        for (i = 0; i < 48; i++){
            result <<=1;
            if (key & (masque << 32 - perm_table[i]))
            result |= 1;
        }
    }

    //P
    else if (perm == 32){
        int perm_table[32] = {16, 7, 20, 21, 
                        29, 12, 28, 17, 
                        1, 15, 23, 26, 
                        5, 18, 31, 10, 
                        2, 8, 24, 14, 
                        32, 27, 3, 9, 
                        19, 13, 30, 6, 
                        22, 11, 4, 25};
        for (i = 0; i < 32; i++){
            result <<=1;
            if (key & (masque << 32 - perm_table[i]))
            result |= 1;
        }
    }

	else{
		perror("Error, the permutation you're asking for doesn't exist.\n");
		exit(-1);
	}

	return (result);

}

void print_bits(u_int64_t word, int range){

	int i;
	u_int64_t masque = 1;
	for (i = range - 1 ; i >= 0; i--){
		putchar(word & (masque << i) ? '1' : '0');
	}
	printf("\n");

}

u_int32_t rightmost_twenty_eight_bits(u_int64_t word){

	int i;
	u_int32_t rightmost_bits = 0;

	for (i = 0; i < 28; i++)
		if (word & (1 << i))
			rightmost_bits |= (1 << i);

	return (rightmost_bits);
}

u_int32_t leftmost_twenty_eight_bits(u_int64_t word){

	int i;
	u_int64_t masque = 1;
	u_int32_t leftmost_bits = 0;

	for (i = 0; i < 28; i++)
		if (word & (masque << 28 + i))
			leftmost_bits |= (1 << i);

	return (leftmost_bits);
}

u_int32_t rightmost_thirty_two_bits(u_int64_t word){

	int i;
	u_int32_t rightmost_bits = 0;

	for (i = 0; i < 32; i++)
		if (word & (1 << i))
			rightmost_bits |= (1 << i);

	return (rightmost_bits);
}



u_int32_t leftmost_thirty_two_bits(u_int64_t word){

	int i;
	u_int64_t masque = 1;
	u_int32_t leftmost_bits = 0;

	for (i = 0; i < 32; i++)
		if (word & (masque << 32 + i))
			leftmost_bits |= (1 << i);

	return (leftmost_bits);
}

u_int64_t* sixteen_key_generation(u_int64_t key){
    key = permutation(key,56);
    int i;
    u_int32_t C_zero = leftmost_twenty_eight_bits(key);
    u_int32_t D_zero = rightmost_twenty_eight_bits(key);
    u_int32_t* C_list = sixteen_shift(C_zero);
    u_int32_t* D_list = sixteen_shift(D_zero);
    u_int64_t *K_list = (u_int64_t*)malloc(16*sizeof(u_int64_t));
	u_int64_t *intermediate = (u_int64_t*)malloc(16*sizeof(u_int64_t));

    for(i=0; i< 16; i++){
      K_list[i] = C_list[i+1];
      K_list[i] = K_list[i] << 28;
	intermediate[i] = D_list[i+1];
      K_list[i] |= intermediate[i];    //K0 = C1D1 for example
        K_list[i]= permutation(K_list[i], 48);
    }

    return K_list;
}

u_int32_t* sixteen_shift(u_int32_t key){

    u_int32_t *result = (u_int32_t*)malloc(17*sizeof(u_int32_t));
    result[0] = key;
    result[1] = shift(result[0]);
    result[2] = shift(result[1]);
    result[3] = shift(shift(result[2]));
    result[4] = shift(shift(result[3]));
    result[5] = shift(shift(result[4]));
    result[6] = shift(shift(result[5]));
    result[7] = shift(shift(result[6]));
    result[8] = shift(shift(result[7]));
    result[9] = shift(result[8]);
    result[10] = shift(shift(result[9]));
    result[11] = shift(shift(result[10]));
    result[12] = shift(shift(result[11]));
    result[13] = shift(shift(result[12]));
    result[14] = shift(shift(result[13]));
    result[15] = shift(shift(result[14]));
    result[16] = shift(result[15]);

    return result;
}

u_int32_t shift(u_int32_t key){

    u_int32_t copy = key;
    u_int32_t leftmost = 0;
    if((copy & (1<<27)) >> 27){
        leftmost=1; //save the 28th bit(the leftmost one), the one that cycle to the end(since we're working on 28bit keys)
    }
    copy = ((copy << 1)| leftmost) & 4026531839; //11101111111111111111111111111111, we set the 29th bit to 0 since we use shift on 28bit sub keys only
    return copy;
}
