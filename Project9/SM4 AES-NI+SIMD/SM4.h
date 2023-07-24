#ifndef SM4_H
#define SM4_H

#include <stdint.h>

typedef struct _SM4_Key {
    uint32_t rk[32];//32¬÷√‹‘ø
} SM4_Key;


void SM4_KeyInit(uint8_t* key, SM4_Key* sm4_key);
void SM4_NI_Encrypt_4(uint8_t* plaintext, uint8_t* ciphertext, SM4_Key* sm4_key);

void SM4_NI_Decrypt_4(uint8_t* ciphertext, uint8_t* plaintext, SM4_Key* sm4_key);


#endif // !SM4_H