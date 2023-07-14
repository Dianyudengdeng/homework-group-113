#include <iostream>
#include <iomanip>
#include <sstream>
#include <openssl/evp.h>
#include <openssl/err.h>
#include<chrono>

// 计算 SM3 哈希值的十六进制字符串
std::string calculateSM3HashHex(const std::string& input) {
    // 初始化 OpenSSL 库
    OpenSSL_add_all_algorithms();
    ERR_load_crypto_strings();

    // 创建 SM3 上下文对象
    EVP_MD_CTX* mdctx = EVP_MD_CTX_new();
    const EVP_MD* md = EVP_sm3();


    // 初始化 SM3 哈希上下文
    EVP_DigestInit_ex(mdctx, md, NULL);


    // 更新输入数据
    EVP_DigestUpdate(mdctx, input.c_str(), input.length());
    auto start = std::chrono::high_resolution_clock::now();
    // 计算哈希值
    unsigned char hash[EVP_MAX_MD_SIZE];
    unsigned int hashLen = 0;
    EVP_DigestFinal_ex(mdctx, hash, &hashLen);
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> duration = end - start;
    std::cout << "Hash用时: " << duration.count() << " 毫秒" << std::endl;


    // 释放 SM3 上下文对象
    EVP_MD_CTX_free(mdctx);

    // 将哈希值转换为十六进制字符串
    std::ostringstream oss;
    oss << std::hex << std::setfill('0');
    for (unsigned int i = 0; i < hashLen; i++) {
        oss << std::setw(2) << static_cast<unsigned int>(hash[i]);
    }

    // 清理 OpenSSL 资源
    EVP_cleanup();
    ERR_free_strings();

    return oss.str();
}

int main() {
    // 输入数据
    std::string input = "abc";

    // 计算 SM3 哈希值的十六进制字符串

    std::string hashHex = calculateSM3HashHex(input);

    // 输出结果
    std::cout << "SM3 哈希值（十六进制）: " << hashHex << std::endl;

    return 0;
}
