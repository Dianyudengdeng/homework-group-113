#include "SM4.h"
#include<chrono>

int main()
{
    unsigned char key[16] = { 0x01,0x23,0x45,0x67,0x89,0xab,0xcd,0xef,0xfe,0xdc,0xba,0x98,0x76,0x54,0x32,0x10 };
    setKey(key);

    unsigned char plain[16] = { 0x01,0x23,0x45,0x67,0x89,0xab,0xcd,0xef,0xfe,0xdc,0xba,0x98,0x76,0x54,0x32,0x10 };
    unsigned char cipher[16];
    unsigned char decipher[16];
    unsigned int plain32[4];
    unsigned int cipher32[4];
    unsigned int decipher32[4];

    auto start = std::chrono::high_resolution_clock::now();
    /*for (int i = 0; i < 4; i++) {
        plain32[i] = plain[i * 4] << 24 | plain[i * 4 + 1] << 16 | plain[i * 4 + 2] << 8 | plain[i * 4 + 3];
    }
    encrypt(plain32, cipher32);
    for (int i = 0; i < 4; i++) {
        cipher[4 * i] = (cipher32[i] >> 24) & 0xff;
        cipher[4 * i + 1] = (cipher32[i] >> 16) & 0xff;
        cipher[4 * i + 2] = (cipher32[i] >> 8) & 0xff;
        cipher[4 * i + 3] = (cipher32[i]) & 0xff;
    }*/
    for (int i = 0; i < 10000; i++) {
        encrypt(plain, cipher);
    }

    auto end = std::chrono::high_resolution_clock::now();

    auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start);
    std::cout << "软件实现加密执行时间: " << duration.count() << " 纳秒" << std::endl;
    decrypt(cipher, decipher);
    /*for (int i = 0; i < 4; i++) {
        decipher[4 * i] = (decipher32[i] >> 24) & 0xff;
        decipher[4 * i + 1] = (decipher32[i] >> 16) & 0xff;
        decipher[4 * i + 2] = (decipher32[i] >> 8) & 0xff;
        decipher[4 * i + 3] = (decipher32[i]) & 0xff;
    }*/

    for (int i = 0; i < 16; i++) {
        printf("%x ", cipher[i]);
    }
    printf("\n");
    for (int i = 0; i < 16; i++) {
        printf("%x ", decipher[i]);
    }
    return 0;


}