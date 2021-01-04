#include <stdlib.h>
#include "fk.h"
#include "keygen.h"
#include "des.h"

u_int64_t des_ciphertext(u_int64_t plaintext, u_int64_t key){

	int i;

	//Generation of the sixteen subkeys
	u_int64_t* subkeys;
	subkeys = sixteen_key_generation(key);

	u_int64_t ciphertext = permutation(plaintext, 1);
	//The DES algorithm proper, applying the 16 subkeys one by one
	ciphertext = lr_gen(ciphertext, subkeys);
	print_bits(ciphertext,64);
	ciphertext = permutation(ciphertext, -1);

	return(ciphertext);
}

u_int64_t des_plaintext(u_int64_t ciphertext, u_int64_t key){

	//Generation of the sixteen subkeys and then reversing their order, as necessary to decrypt
	u_int64_t* subkeys;
	u_int64_t* subkeys_inverse = (u_int64_t*)malloc(16*sizeof(u_int64_t));
	int i;

	subkeys = sixteen_key_generation(key);

	for(i=0; i<16; i++){
		subkeys_inverse[i]=subkeys[15-i];
	}

	u_int64_t plaintext = permutation(ciphertext, 1);
	
    	plaintext = lr_gen(plaintext, subkeys_inverse);
	
    	plaintext = permutation(plaintext, -1);

	return(plaintext);
}
