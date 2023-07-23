#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <immintrin.h>
#include <chrono>
#include<iostream>

#define AES_128_key_exp(k, rcon) aes_128_key_expansion(k, _mm_aeskeygenassist_si128(k, rcon))


static __m128i aes_128_key_expansion(__m128i key, __m128i keygened) {
    keygened = _mm_shuffle_epi32(keygened, _MM_SHUFFLE(3, 3, 3, 3));
    key = _mm_xor_si128(key, _mm_slli_si128(key, 4));
    key = _mm_xor_si128(key, _mm_slli_si128(key, 4));
    key = _mm_xor_si128(key, _mm_slli_si128(key, 4));
    return _mm_xor_si128(key, keygened);
}


void aes_key_expansion(const uint8_t* key, __m128i* aes_key) {
    aes_key[0] = _mm_loadu_si128((const __m128i*) key);
   aes_key[1]= AES_128_key_exp(aes_key[0], 0x01);
   aes_key[2]= AES_128_key_exp(aes_key[1], 0x02);
   aes_key[3]= AES_128_key_exp(aes_key[2], 0x04);
   aes_key[4]= AES_128_key_exp(aes_key[3], 0x08);
   aes_key[5]= AES_128_key_exp(aes_key[4], 0x10);
   aes_key[6]= AES_128_key_exp(aes_key[5], 0x20);
   aes_key[7]= AES_128_key_exp(aes_key[6], 0x40);
   aes_key[8]= AES_128_key_exp(aes_key[7], 0x80);
   aes_key[9]= AES_128_key_exp(aes_key[8], 0x1B);
   aes_key[10]= AES_128_key_exp(aes_key[9], 0x36);

    aes_key[11] = _mm_aesimc_si128(aes_key[9]);
    aes_key[12] = _mm_aesimc_si128(aes_key[8]);
    aes_key[13] = _mm_aesimc_si128(aes_key[7]);
    aes_key[14] = _mm_aesimc_si128(aes_key[6]);
    aes_key[15] = _mm_aesimc_si128(aes_key[5]);
    aes_key[16] = _mm_aesimc_si128(aes_key[4]);
    aes_key[17] = _mm_aesimc_si128(aes_key[3]);
    aes_key[18] = _mm_aesimc_si128(aes_key[2]);
    aes_key[19] = _mm_aesimc_si128(aes_key[1]);
}

void aes_encrypt(const uint8_t* plaintext, __m128i* aes_key, uint8_t* ciphertext, size_t plaintext_length) {
    size_t remaining_bytes = plaintext_length;

    // 使用 AES-NI 指令执行 AES 加密操作
    while (remaining_bytes >= 16) {
        __m128i data = _mm_loadu_si128((__m128i*) plaintext);

        __m128i encrypted_data = _mm_xor_si128(data, aes_key[0]); // 第一轮直接与轮密钥异或

        for (int i = 1; i < 10; ++i) {
            encrypted_data = _mm_aesenc_si128(encrypted_data, aes_key[i]);
        }

        encrypted_data = _mm_aesenclast_si128(encrypted_data, aes_key[10]);
        _mm_storeu_si128((__m128i*)ciphertext, encrypted_data);

        plaintext += 16;
        ciphertext += 16;
        remaining_bytes -= 16;
    }

    if (remaining_bytes > 0) {
        alignas(16) uint8_t remaining_data[16] = { 0 };

        for (size_t i = 0; i < remaining_bytes; ++i) {
            remaining_data[i] = plaintext[i];
        }

        __m128i data = _mm_loadu_si128(( __m128i*)remaining_data);

        __m128i encrypted_data = _mm_xor_si128(data, aes_key[0]); 

        for (int i = 1; i < 10; ++i) {
            encrypted_data = _mm_aesenc_si128(encrypted_data, aes_key[i]);
        }

        encrypted_data = _mm_aesenclast_si128(encrypted_data, aes_key[10]);

        _mm_storeu_si128((__m128i*)ciphertext, encrypted_data);
    }
}

void aes_decrypt(const uint8_t* ciphertext, __m128i* aes_key, uint8_t* plaintext, size_t ciphertext_length) {
    size_t remaining_bytes = ciphertext_length;

    while (remaining_bytes >= 16) {
        __m128i data = _mm_loadu_si128(( __m128i*)ciphertext);

        __m128i decrypted_data = _mm_xor_si128(data, aes_key[10]); 

        for (int i = 11; i <20; i++) {
            decrypted_data = _mm_aesdec_si128(decrypted_data, aes_key[i]);
        }

        decrypted_data = _mm_aesdeclast_si128(decrypted_data, aes_key[0]);


        _mm_storeu_si128((__m128i*)plaintext, decrypted_data);

        ciphertext += 16;
        plaintext += 16;
        remaining_bytes -= 16;
    }

    if (remaining_bytes > 0) {
        alignas(16) uint8_t remaining_data[16] = { 0 };

        for (size_t i = 0; i < remaining_bytes; ++i) {
            remaining_data[i] = ciphertext[i];
        }

        __m128i data = _mm_loadu_si128(( __m128i*)remaining_data);

        __m128i decrypted_data = _mm_xor_si128(data, aes_key[10]); 

        for (int i = 9; i > 0; --i) {
            decrypted_data = _mm_aesdec_si128(decrypted_data, aes_key[i]);
        }

        decrypted_data = _mm_aesdeclast_si128(decrypted_data, aes_key[0]);

        _mm_storeu_si128((__m128i*)plaintext, decrypted_data);
    }
}

//测试程序
int main() {
    const int repetitions = 1000;
    // 128位的AES密钥
    uint8_t key[16] = {
        0x2b, 0x7e, 0x15, 0x16, 0x28, 0xae, 0xd2, 0xa6,
        0xab, 0xf7, 0x15, 0x88, 0x09, 0xcf, 0x4f, 0x3c
    };

    // 10个16字节的明文分组
    uint8_t plaintext[160] = {
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

    // 加密后的结果
    uint8_t ciphertext[160];
    // 解密后的结果
    uint8_t decrypted_text[160];

    printf("明文：\n");
    for (int i = 0; i < 10; ++i) {
        for (int j = 0; j < 16; ++j) {
            printf("%02x ", plaintext[i * 16 + j]);
        }
        printf("\n");
    }


    // 加密
    __m128i expanded_key[20];

    auto start = std::chrono::high_resolution_clock::now();

    for (int i = 0; i < repetitions; ++i) {
        aes_key_expansion(key, expanded_key);
        aes_encrypt(plaintext, expanded_key, ciphertext, 160);
    }

    auto end = std::chrono::high_resolution_clock::now();
    long long elapsed_time = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();

    double average_duration = elapsed_time / repetitions;

    std::cout << "平均执行时间（纳秒）: " << average_duration << std::endl;

    printf("\n加密后的结果：\n");
    for (int i = 0; i < 10; ++i) {
        for (int j = 0; j < 16; ++j) {
            printf("%02x ", ciphertext[i*16+j]);
        }
        printf("\n");
    }


    // 解密
    aes_decrypt(ciphertext, expanded_key, decrypted_text, 160);

    printf("\n解密后的结果：\n");
    for (int i = 0; i < 10; ++i) {
        for (int j = 0; j < 16; ++j) {
            printf("%02x ", decrypted_text[i*16+j]);
        }
        printf("\n");
    }

    return 0;
}