#include<iostream>
#include<chrono>
#include "SM4.h"

int main() {
    // 01 23 45 67 89 ab cd ef fe dc ba 98 76 54 32 10
    unsigned char key[16] = { 0x01, 0x23, 0x45, 0x67, 0x89, 0xab,
                                 0xcd, 0xef, 0xfe, 0xdc, 0xba, 0x98,
                                 0x76, 0x54, 0x32, 0x10 };

    unsigned char plain[16 * 4] = { 0x01, 0x23, 0x45, 0x67, 0x89, 0xab, 0xcd, 0xef,
                                0xfe, 0xdc, 0xba, 0x98, 0x76, 0x54, 0x32, 0x10,
                                0x01, 0x23, 0x45, 0x67, 0x89, 0xab, 0xcd, 0xef,
                                0xfe, 0xdc, 0xba, 0x98, 0x76, 0x54, 0x32, 0x10 ,
                                0x01, 0x23, 0x45, 0x67, 0x89, 0xab, 0xcd, 0xef,
                                0xfe, 0xdc, 0xba, 0x98, 0x76, 0x54, 0x32, 0x10 ,
                                0x01, 0x23, 0x45, 0x67, 0x89, 0xab, 0xcd, 0xef,
                                0xfe, 0xdc, 0xba, 0x98, 0x76, 0x54, 0x32, 0x10 };
    unsigned char cipher[16 * 4];
    SM4_Key sm4_key;

    SM4_KeyInit(key, &sm4_key);

    auto start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < 2500; i++) {
        SM4_NI_Encrypt_4(plain, cipher, &sm4_key);
    }
    auto end = std::chrono::high_resolution_clock::now();

    auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start);
    std::cout << "软件实现加密执行时间: " << duration.count() << " 纳秒" << std::endl;

    printf("Cipher:\n");
    for (int j = 0; j < 4; j++) {
        printf("\t");
        for (int i = 0; i < 16; i++) {
            printf("%02x ", cipher[i + 16 * j]);
        }
        printf("\n");
    }

    printf("Plaintext:\n");
    SM4_NI_Decrypt_4(cipher, plain, &sm4_key);

    for (int j = 0; j < 4; j++) {
        printf("\t");
        for (int i = 0; i < 16; i++) {
            printf("%02x ", plain[i + 16 * j]);
        }
        printf("\n");
    }
    system("pause");
    return 0;
}