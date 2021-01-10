#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "fk.h"
#include "keygen.h"
#include "des.h"
#include "ecb.h"



/* The main is here to perform simple tests to make sure everything works fine.
 * As you can see, it generates an integer between 0 and (2^64)-1, as we were asked
 * to work with 64-bit plaintexts. You can change it to whichever value you can, 
 * provided it fills the requirements cited above.*/

int main(){

	srand(time(NULL));

	u_int64_t plaintext, ciphertext;

	//64-bit key
	u_int64_t key = 0x133457799BBCDFF1;
	plaintext = rand() % 0xFFFFFFFFFFFFFFFF; //(2^64 -1)
	printf("The randomly generated plaintext is ");
	print_bits(plaintext,64);


	// encryption of the plaintext
	ciphertext = des_ciphertext(plaintext, key);
	printf("\nThe ciphertext generated from the plaintext is ");
	print_bits(ciphertext, 64);

	//decryption of the ciphertext
	plaintext = des_plaintext(ciphertext, key);
	printf("\nThe original plaintext is ");
	print_bits(plaintext, 64);


	char* message ="SamyIgorEBC";
	printf("\nThe message is %s\n",message);

	char* chiffre = ecb_crypt(message, key);
	printf("\nThe ciphertext generated from the plaintext is %s",chiffre);

	char* dechiffre = ecb_decrypt(chiffre,key);
	printf("\n\nThe plaintext generated from the ciphertext is %s",dechiffre);
	printf("\n");
	return(0);
}
