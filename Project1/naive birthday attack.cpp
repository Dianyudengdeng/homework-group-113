#include"SM3.h"
#include<iostream>
#include <sstream>
#include <iomanip>
#include <string>
#include <unordered_map>
#include<chrono>
using namespace std;
#define InputLength 32
#define CollisionLength 1 //单位：4bytes

string convertHashToString(const unsigned int Hash[8]) {
    ostringstream oss;
    oss << hex << setfill('0');
    for (int i = 0; i < 8; i++) {
        oss << setw(8) << Hash[i];
    }
    return oss.str();
}

string convertInputToString(uint8_t input[InputLength]) {
    std::ostringstream oss;
    oss << std::hex << std::setfill('0');
    for (int i = 0; i < InputLength; i++) {
        oss << std::setw(2) << static_cast<unsigned>(input[i]);
    }
    return oss.str();
}

string reduced_convertHashToString(const unsigned int *Hash) {
    ostringstream oss;
    oss << hex << setfill('0');
    for (int i = 0; i < CollisionLength; i++) {
        oss << setw(8) << Hash[i];
    }
    return oss.str();
}

void convertToUInt8Array(string& hexString, uint8_t result[InputLength]) {
    for (int i = 0; i < InputLength *2; i += 2) {
        string substring = hexString.substr(i, 2);
        result[(i / 2)] = stoi(substring, nullptr, 16);
    }

}


void attack() {
    unordered_map<string, string> hashToInputMap;

    // 添加键值对到映射
    unsigned int Hash[8];
    unsigned int Collision_Hash[8];
    uint8_t* input = new uint8_t[InputLength];
    uint8_t* oldinput = new uint8_t[InputLength];
    for (int i = 0; i < 32; i++) {
        input[i] = 0;
    }
    int count = 0;
    // 使用 SM3 函数计算 Hash
    while(1){
        uint8_t* result = new uint8_t[InputLength];
        SM3(input, InputLength, Hash);
        count++;
        string inputString = convertInputToString(input);
        convertToUInt8Array(inputString, result);

        string hashString = reduced_convertHashToString(Hash);
        auto it = hashToInputMap.find(hashString);
        if (it != hashToInputMap.end()) {
            string retrievedInput = it->second;
            cout << "Reduced_Collision!" << endl;
            convertToUInt8Array(retrievedInput, oldinput);
            SM3(oldinput, InputLength, Collision_Hash);
            cout << retrievedInput<<"\n对应Hash："<< convertHashToString(Collision_Hash) << endl;
            cout << inputString << "\n对应Hash："<< convertHashToString(Hash)<<endl;
            cout << "经过 " << count << " 次哈希运算" << endl;
            cout << "碰撞部分：" << hashString << endl;
            return;
        }
        else {
            hashToInputMap[hashString] = inputString;
        }
        memcpy(input, Hash, InputLength);

    }
    
}
int main() {
    auto start = std::chrono::high_resolution_clock::now();
    attack();
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, milli> duration = end - start;
    std::cout << "Naive Birthday Attack用时: " << duration.count() << " 毫秒" << std::endl;
}