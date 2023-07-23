#include <stdio.h>
#include <openssl/evp.h>
#include <openssl/rand.h>
#include <chrono>
#include<iostream>

// AES加密函数
int aes_encrypt(const unsigned char* plaintext, int plaintext_len, const unsigned char* key,
    unsigned char* ciphertext, int* ciphertext_len) {
    EVP_CIPHER_CTX* ctx;
    int len, out_len;

    // 创建EVP_CIPHER_CTX上下文
    ctx = EVP_CIPHER_CTX_new();
    if (ctx == NULL) {
        fprintf(stderr, "Error creating EVP_CIPHER_CTX.\n");
        return 0;
    }

    // 初始化加密操作，使用AES-128加密
    if (EVP_EncryptInit_ex(ctx, EVP_aes_128_ecb(), NULL, key, key) != 1) {
        fprintf(stderr, "Error initializing AES encryption.\n");
        EVP_CIPHER_CTX_free(ctx);
        return 0;
    }

    // 执行加密操作
    if (EVP_EncryptUpdate(ctx, ciphertext, &len, plaintext, plaintext_len) != 1) {
        fprintf(stderr, "Error performing AES encryption.\n");
        EVP_CIPHER_CTX_free(ctx);
        return 0;
    }
    out_len = len;

    // 完成加密操作
    if (EVP_EncryptFinal_ex(ctx, ciphertext + len, &len) != 1) {
        fprintf(stderr, "Error finalizing AES encryption.\n");
        EVP_CIPHER_CTX_free(ctx);
        return 0;
    }
    out_len += len;

    // 释放上下文
    EVP_CIPHER_CTX_free(ctx);

    *ciphertext_len = out_len;
    return 1;
}

int main() {
    // 要加密的明文和密钥
    unsigned char plaintext[160] = {
            0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30,
            0x31, 0x31, 0x31, 0x31, 0x31, 0x31, 0x31, 0x31, 0x31, 0x31, 0x31, 0x31, 0x31, 0x31, 0x31, 0x31,
            0x32, 0x32, 0x32, 0x32, 0x32, 0x32, 0x32, 0x32, 0x32, 0x32, 0x32, 0x32, 0x32, 0x32, 0x32, 0x32,
            0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33,
            0x34, 0x34, 0x34, 0x34, 0x34, 0x34, 0x34, 0x34, 0x34, 0x34, 0x34, 0x34, 0x34, 0x34, 0x34, 0x34,
            0x35, 0x35, 0x35, 0x35, 0x35, 0x35, 0x35, 0x35, 0x35, 0x35, 0x35, 0x35, 0x35, 0x35, 0x35, 0x35,
            0x36, 0x36, 0x36, 0x36, 0x36, 0x36, 0x36, 0x36, 0x36, 0x36, 0x36, 0x36, 0x36, 0x36, 0x36, 0x36,
            0x37, 0x37, 0x37, 0x37, 0x37, 0x37, 0x37, 0x37, 0x37, 0x37, 0x37, 0x37, 0x37, 0x37, 0x37, 0x37,
            0x38, 0x38, 0x38, 0x38, 0x38, 0x38, 0x38, 0x38, 0x38, 0x38, 0x38, 0x38, 0x38, 0x38, 0x38, 0x38,
            0x39, 0x39, 0x39, 0x39, 0x39, 0x39, 0x39, 0x39, 0x39, 0x39, 0x39, 0x39, 0x39, 0x39, 0x39, 0x39
    };
    unsigned char key[16] = {
        0x2b, 0x7e, 0x15, 0x16, 0x28, 0xae, 0xd2, 0xa6,
        0xab, 0xf7, 0x15, 0x88, 0x09, 0xcf, 0x4f, 0x3c
    };

    // 计算加密后的密文长度
    int plaintext_len = sizeof(plaintext); // 减去结尾的空字符
    int ciphertext_len = ((plaintext_len + EVP_MAX_BLOCK_LENGTH - 1) / EVP_MAX_BLOCK_LENGTH) * EVP_MAX_BLOCK_LENGTH;
    unsigned char *ciphertext=new unsigned char[ciphertext_len];
    int encrypted_length;
    // 执行加密操作
    auto start = std::chrono::high_resolution_clock::now();

    const int repetitions = 1;

    for (int i = 0; i < repetitions; ++i) {
        if (aes_encrypt(plaintext, plaintext_len, key, ciphertext, &encrypted_length) != 1) {
            fprintf(stderr, "AES encryption failed.\n");
            return 1;
        }
    }
    auto end = std::chrono::high_resolution_clock::now();
    long long elapsed_time = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();

    double average_duration = elapsed_time / repetitions;

    std::cout << "平均执行时间（毫秒）: " << average_duration << std::endl;
    // 打印加密结果
    printf("Ciphertext: ");

    for (int i = 0; i < encrypted_length; ++i) {
        printf("%02x", ciphertext[i]);
    }
    printf("\n");

    return 0;
}
