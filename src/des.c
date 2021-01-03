#include <stdlib.h>
#include "fk.h"
#include "keygen.h"
#include "des.h"

u_int64_t des_ciphertext(u_int64_t plaintext, u_int64_t key){

	//Generation of the sixteen subkeys
	u_int64_t* subkeys;
    	subkeys = sixteen_key_generation(key);

	u_int64_t ciphertext = permutation(plaintext, 64);
	
	//The DES algorithm proper, applying the 16 subkeys one by one
    	ciphertext = lr_gen(ciphertext, subkeys);
	
    	ciphertext = permutation(ciphertext, -1);

	return(ciphertext);
}

u_int64_t des_plaintext(u_int64_t ciphertext, u_int64_t key){

	//Generation of the sixteen subkeys and then reversing their order, as necessary to decrypt
	u_int64_t* subkeys;
	u_int64_t* subkeys_inverse;
	int i;
    	subkeys = sixteen_key_generation(key);

	for(i=0; i<16; i++)
	{
		subkeys_inverse[i]=subkeys[15-i];
	}

	u_int64_t plaintext = permutation(ciphertext, 64);
	
    	plaintext = lr_gen(plaintext, subkeys_inverse);
	
    	plaintext = permutation(plaintext, -1);

	return(ciphertext);
}
