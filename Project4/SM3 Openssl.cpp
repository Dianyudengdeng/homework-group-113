#include <iostream>
#include <iomanip>
#include <sstream>
#include <openssl/evp.h>
#include <openssl/err.h>
#include<chrono>

// ���� SM3 ��ϣֵ��ʮ�������ַ���
std::string calculateSM3HashHex(const std::string& input) {
    // ��ʼ�� OpenSSL ��
    OpenSSL_add_all_algorithms();
    ERR_load_crypto_strings();

    // ���� SM3 �����Ķ���
    EVP_MD_CTX* mdctx = EVP_MD_CTX_new();
    const EVP_MD* md = EVP_sm3();


    // ��ʼ�� SM3 ��ϣ������
    EVP_DigestInit_ex(mdctx, md, NULL);


    // ������������
    EVP_DigestUpdate(mdctx, input.c_str(), input.length());
    auto start = std::chrono::high_resolution_clock::now();
    // �����ϣֵ
    unsigned char hash[EVP_MAX_MD_SIZE];
    unsigned int hashLen = 0;
    EVP_DigestFinal_ex(mdctx, hash, &hashLen);
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> duration = end - start;
    std::cout << "Hash��ʱ: " << duration.count() << " ����" << std::endl;


    // �ͷ� SM3 �����Ķ���
    EVP_MD_CTX_free(mdctx);

    // ����ϣֵת��Ϊʮ�������ַ���
    std::ostringstream oss;
    oss << std::hex << std::setfill('0');
    for (unsigned int i = 0; i < hashLen; i++) {
        oss << std::setw(2) << static_cast<unsigned int>(hash[i]);
    }

    // ���� OpenSSL ��Դ
    EVP_cleanup();
    ERR_free_strings();

    return oss.str();
}

int main() {
    // ��������
    std::string input = "abc";

    // ���� SM3 ��ϣֵ��ʮ�������ַ���

    std::string hashHex = calculateSM3HashHex(input);

    // ������
    std::cout << "SM3 ��ϣֵ��ʮ�����ƣ�: " << hashHex << std::endl;

    return 0;
}
