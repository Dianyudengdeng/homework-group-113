#include"SM3.h"
#include <iostream>
#include <sstream>
#include <iomanip>
#include <string>
#include <chrono>
#include <thread>
#include <random>
using namespace std;
#define InputLength 4
#define CollisionLength 4//单位：byte
#define IVNumber 80
#define ThreadNumber 8

string convertHashToString(const unsigned int Hash[8]) {
    ostringstream oss;
    oss << hex << setfill('0');
    for (int i = 0; i < 8; i++) {
        oss << setw(8) << Hash[i];
    }
    return oss.str();
}

string convertInputToString(uint8_t input[32]) {
    std::ostringstream oss;
    oss << std::hex << std::setfill('0');
    for (int i = 0; i < 32; i++) {
        oss << std::setw(2) << static_cast<unsigned>(input[i]);
    }
    return oss.str();
}



//void attack() {
//    auto start = std::chrono::high_resolution_clock::now();
//    uint8_t IV[IVNumber][32];
//    for (int i = 0; i < IVNumber; i++) {
//        for (int j = 0; j < 32; j++) {
//            IV[i][j] = i + j;
//        }
//    }
//    unsigned int H_1[IVNumber][8], H_2[IVNumber][8];
//    uint8_t input_1[IVNumber][32], input_2[IVNumber][32];
//    int count[IVNumber] = { 0 };
//    for (int i = 0; i < IVNumber; i++) {
//        SM3(IV[i], 32, H_1[i]);
//        memcpy(H_2[i], H_1[i], 32);
//    }
//    while (1) {
//        for (int i = 0; i < IVNumber; i++) {
//            for (int j = 0; j < 8; j++) {
//                input_1[i][j * 4] = (H_1[i][j] >> 24) & 0xff;
//                input_1[i][j * 4 + 1] = (H_1[i][j] >> 16) & 0xff;
//                input_1[i][j * 4 + 2] = (H_1[i][j] >> 8) & 0xff;
//                input_1[i][j * 4 + 3] = H_1[i][j] & 0xff;
//            }
//            SM3(input_1[i], 32, H_1[i]);
//            for (int j = 0; j < 8; j++) {
//                input_2[i][j * 4] = (H_2[i][j] >> 24) & 0xff;
//                input_2[i][j * 4 + 1] = (H_2[i][j] >> 16) & 0xff;
//                input_2[i][j * 4 + 2] = (H_2[i][j] >> 8) & 0xff;
//                input_2[i][j * 4 + 3] = H_2[i][j] & 0xff;
//            }
//            SM3(input_2[i], 32, H_2[i]);
//            for (int j = 0; j < 8; j++) {
//                input_2[i][j * 4] = (H_2[i][j] >> 24) & 0xff;
//                input_2[i][j * 4 + 1] = (H_2[i][j] >> 16) & 0xff;
//                input_2[i][j * 4 + 2] = (H_2[i][j] >> 8) & 0xff;
//                input_2[i][j * 4 + 3] = H_2[i][j] & 0xff;
//            }
//            SM3(input_2[i], 32, H_2[i]);
//            count[i] += 3;
//            if (memcmp(H_1[i], H_2[i], CollisionLength) == 0) {
//                cout << "Reduced_Collision!" << endl;
//                cout << convertInputToString(input_1[i]) << "\n对应Hash：" << convertHashToString(H_1[i]) << endl;
//                cout << convertInputToString(input_2[i]) << "\n对应Hash：" << convertHashToString(H_2[i]) << endl;
//                cout << "经过 " << count[i] << " 次哈希运算" << endl;
//                //cout << "碰撞部分：" << hashString << endl;
//                auto end = std::chrono::high_resolution_clock::now();
//                chrono::duration<double> duration = end - start;
//                cout << "Rho Method Attack用时: " << duration.count() << " 秒" << endl;
//                return;
//            }
//        }
//    }
//}

void attack_reduced() {
    unsigned seed = chrono::system_clock::now().time_since_epoch().count();
    default_random_engine generator(seed);
    uniform_int_distribution<int> distribution(1, 127);

    auto start = std::chrono::high_resolution_clock::now();
    unsigned int H_1[IVNumber][8], H_2[IVNumber][8];
    uint8_t input_1[IVNumber][32], input_2[IVNumber][32];
    for (int i = 0; i < IVNumber; i++) {
        for (int j = 0; j < 32; j++) {
            input_1[i][j] = distribution(generator);
        }
        memcpy(input_2[i], input_1[i], 32);
    }
    for (int i = 0; i < IVNumber; i++) {
        SM3(input_1[i], 32, H_1[i]);
        memcpy(H_2[i], H_1[i], 32);
    }
    int count[IVNumber] = {0};
    while (1) {
        for (int i = 0; i < IVNumber; i++) {
            memcpy(input_2[i], H_2[i], InputLength);
            SM3(input_2[i], 32, H_2[i]);
            memcpy(input_2[i], H_2[i], InputLength);
            SM3(input_2[i], 32, H_2[i]);
            memcpy(input_1[i], H_1[i], InputLength);
            SM3(input_1[i], 32, H_1[i]);
            count[i] += 3;
            if ((memcmp(H_1[i], H_2[i], CollisionLength) == 0)&& (memcmp(input_1[i], input_2[i], InputLength) != 0)){
                cout << "Reduced_Collision!" << endl;
                cout << convertInputToString(input_1[i]) << "\n对应Hash：" << convertHashToString(H_1[i]) << endl;
                cout << convertInputToString(input_2[i]) << "\n对应Hash：" << convertHashToString(H_2[i]) << endl;
                cout << "经过 " << count[i] << " 次哈希运算" << endl;
                auto end = std::chrono::high_resolution_clock::now();
                chrono::duration<double> duration = end - start;
                cout << "Rho Method Attack用时: " << duration.count() << " 秒" << endl;
                return;
                /*else {
                    cout << "Reduced_Collision!" << endl;
                    SM3(input_1_temp[i][0], 32, H_1[i]);
                    cout << convertInputToString(input_1_temp[i][0]) << "\n对应Hash：" << convertHashToString(H_1[i]) << endl;
                    SM3(input_1_temp[i][1], 32, H_1[i]);
                    cout << convertInputToString(input_1_temp[i][1]) << "\n对应Hash：" << convertHashToString(H_1[i]) << endl;
                    SM3(input_2_temp1[i], 32, H_2[i]);
                    cout << convertInputToString(input_2_temp1[i]) << "\n对应Hash：" << convertHashToString(H_2[i]) << endl;
                    SM3(input_2_temp2[i], 32, H_2[i]);
                    cout << convertInputToString(input_2_temp2[i]) << "\n对应Hash：" << convertHashToString(H_2[i]) << endl;
                    cout << "经过 " << count[i] << " 次哈希运算" << endl;
                    auto end = std::chrono::high_resolution_clock::now();
                    chrono::duration<double> duration = end - start;
                    cout << "Rho Method Attack用时: " << duration.count() << " 秒" << endl;
                    return;
                }*/
            }
        }
    }
}

void attack_single() {
    unsigned seed = chrono::system_clock::now().time_since_epoch().count();
    default_random_engine generator(seed);
    uniform_int_distribution<int> distribution(1, 127);

    auto start = std::chrono::high_resolution_clock::now();
    uint8_t IV[32];

    for (int j = 0; j < 32; j++) {
        IV[j] = distribution(generator);
    }
    unsigned int H_1[8], H_2[8];
    uint8_t input_1[32], input_2[32];
    int count = { 0 };
    for (int i = 0; i < IVNumber; i++) {
        SM3(IV, 32, H_1);
        memcpy(H_2, H_1, 32);
    }
    while (1) {
        for (int i = 0; i < IVNumber; i++) {
            memcpy(input_1, H_1, 32);
            SM3(input_1, 32, H_1);
            memcpy(input_2, H_2, 32);
            SM3(input_2, 32, H_2);
            memcpy(input_2, H_2, 32);
            SM3(input_2, 32, H_2);
            count += 3;
            if (memcmp(H_1, H_2, CollisionLength) == 0) {
                cout << "Reduced_Collision!" << endl;
                cout << convertInputToString(input_1) << "\n对应Hash：" << convertHashToString(H_1) << endl;
                cout << convertInputToString(input_2) << "\n对应Hash：" << convertHashToString(H_2) << endl;
                cout << "经过 " << count << " 次哈希运算" << endl;
                //cout << "碰撞部分：" << hashString << endl;

                auto end = std::chrono::high_resolution_clock::now();
                chrono::duration<double> duration = end - start;
                cout << "Rho Method Attack用时: " << duration.count() << " 秒" << endl;
                return;
            }
        }
    }
    return;

}

int main() {
    attack_reduced();
    /*thread threads[ThreadNumber];


    for (int i = 0; i < ThreadNumber; i++) {
        threads[i] = thread(attack_reduced);
    }


    for (int i = 0; i < ThreadNumber; i++) {
        threads[i].join();
    }*/
    return 0;
}