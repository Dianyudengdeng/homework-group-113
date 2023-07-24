#ifndef SM4_H
#define SM4_H
#include <iostream>
#include <vector>

void setKey(unsigned char* key);
void encrypt(unsigned int plain[4], unsigned int cipher[4]);
void encrypt(unsigned char plain[16], unsigned char cipher[16]);
void decrypt(unsigned int cipher[4], unsigned int plain[4]);
void decrypt(unsigned char cipher[16], unsigned char plain[16]);
void encfile(unsigned int* data_in, unsigned int* data_out);

#endif
