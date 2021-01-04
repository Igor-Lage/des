#ifndef __DES_H__
#define __DES_H__

u_int64_t des_ciphertext(u_int64_t plaintext, u_int64_t key);

u_int64_t des_plaintext(u_int64_t ciphertext, u_int64_t key);
#endif