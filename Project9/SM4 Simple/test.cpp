#include "SM4.h"
#include<chrono>
#include <iostream>
#include <vector>

int main()
{
    unsigned char key[16] = { 0x01,0x23,0x45,0x67,0x89,0xab,0xcd,0xef,0xfe,0xdc,0xba,0x98,0x76,0x54,0x32,0x10 };
    setKey(key);

   // unsigned char plain[16] = { 0x01,0x23,0x45,0x67,0x89,0xab,0xcd,0xef,0xfe,0xdc,0xba,0x98,0x76,0x54,0x32,0x10 };
    unsigned char cipher[16];
    unsigned char decipher[16];
    unsigned int plain32[4];
    unsigned int cipher32[4];
    unsigned int decipher32[4];

    FILE* inputfile;
    if (fopen_s(&inputfile, "C:/Users/dianyudengdeng/Desktop/input.txt", "rb") != 0) {
        printf("OK\n");
        return -1;
    }
    unsigned char plain[1600];

    size_t bytes_read = fread(plain, 1, 1600, inputfile);
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
    for (int i = 0; i < bytes_read; i+=16) {
        encrypt(plain + i, cipher);

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

//int main()
//{
//    unsigned char key[16] = "0123456789abcde";
//
//    FILE* inputfile;
//    if (fopen_s(&inputfile, "C:/Users/dianyudengdeng/Desktop/video.mp4", "rb") != 0) {
//        printf("无法打开输入文件。\n");
//        return -1;
//    }
//    FILE* outputfile;
//    if (fopen_s(&outputfile, "C:/Users/dianyudengdeng/Desktop/test", "wb") != 0) {
//        printf("无法创建输出文件。\n");
//        fclose(inputfile);
//        return -1;
//    }
//
//    std::vector<unsigned int> data_in(175812);
//    std::vector<unsigned int> data_out(175812);
//
//    size_t bytes_read = fread(data_in.data(), 4, 175812, inputfile);
//
//    //std::cout << bytes_read << std::endl;
//    auto start = std::chrono::high_resolution_clock::now();
//    data_in[175811] = 0;
//    //unsigned char iv[16] = { 0 }; 
//
//    encfile(data_in.data(), data_out.data());
//    auto end = std::chrono::high_resolution_clock::now();
//
//    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
//    std::cout << "软件实现加密执行时间: " << duration.count() << " 毫秒" << std::endl;
//
//    fwrite(data_out.data(), 4, 175812, outputfile);
//
//    fclose(inputfile);
//    fclose(outputfile);
//}