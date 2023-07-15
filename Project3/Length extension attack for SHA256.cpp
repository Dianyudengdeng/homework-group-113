#include <iostream> 
#include <cstdio>
#include <cstdlib>

using namespace std;
unsigned int * StrSHA256(const char* str, long long length, unsigned int* Hash);
unsigned int* StrSHA256_length_extension_Attack(unsigned int* latestHash, unsigned char* append, long long msglen, long long appendlen, unsigned int* Hash);
void padding(const char* input, uint8_t* output, size_t length);
#define SHA256_ROTL(a,b) (((a>>(32-b))&(0x7fffffff>>(31-b)))|(a<<b))
#define SHA256_SR(a,b) ((a>>b)&(0x7fffffff>>(b-1)))
#define SHA256_Ch(x,y,z) ((x&y)^((~x)&z))
#define SHA256_Maj(x,y,z) ((x&y)^(x&z)^(y&z))
#define SHA256_E0(x) (SHA256_ROTL(x,30)^SHA256_ROTL(x,19)^SHA256_ROTL(x,10))
#define SHA256_E1(x) (SHA256_ROTL(x,26)^SHA256_ROTL(x,21)^SHA256_ROTL(x,7))
#define SHA256_O0(x) (SHA256_ROTL(x,25)^SHA256_ROTL(x,14)^SHA256_SR(x,3))
#define SHA256_O1(x) (SHA256_ROTL(x,15)^SHA256_ROTL(x,13)^SHA256_SR(x,10))
unsigned int* StrSHA256(const char* str, long long length, unsigned int* Hash) {
    char* pp, * ppend;
    long l, i, W[64], T1, T2, A, B, C, D, E, F, G, H, H0, H1, H2, H3, H4, H5, H6, H7;
    H0 = 0x6a09e667, H1 = 0xbb67ae85, H2 = 0x3c6ef372, H3 = 0xa54ff53a;
    H4 = 0x510e527f, H5 = 0x9b05688c, H6 = 0x1f83d9ab, H7 = 0x5be0cd19;
    long K[64] = {
        0x428a2f98, 0x71374491, 0xb5c0fbcf, 0xe9b5dba5, 0x3956c25b, 0x59f111f1, 0x923f82a4, 0xab1c5ed5,
        0xd807aa98, 0x12835b01, 0x243185be, 0x550c7dc3, 0x72be5d74, 0x80deb1fe, 0x9bdc06a7, 0xc19bf174,
        0xe49b69c1, 0xefbe4786, 0x0fc19dc6, 0x240ca1cc, 0x2de92c6f, 0x4a7484aa, 0x5cb0a9dc, 0x76f988da,
        0x983e5152, 0xa831c66d, 0xb00327c8, 0xbf597fc7, 0xc6e00bf3, 0xd5a79147, 0x06ca6351, 0x14292967,
        0x27b70a85, 0x2e1b2138, 0x4d2c6dfc, 0x53380d13, 0x650a7354, 0x766a0abb, 0x81c2c92e, 0x92722c85,
        0xa2bfe8a1, 0xa81a664b, 0xc24b8b70, 0xc76c51a3, 0xd192e819, 0xd6990624, 0xf40e3585, 0x106aa070,
        0x19a4c116, 0x1e376c08, 0x2748774c, 0x34b0bcb5, 0x391c0cb3, 0x4ed8aa4a, 0x5b9cca4f, 0x682e6ff3,
        0x748f82ee, 0x78a5636f, 0x84c87814, 0x8cc70208, 0x90befffa, 0xa4506ceb, 0xbef9a3f7, 0xc67178f2,
    };
    l = length + ((length % 64 > 56) ? (128 - length % 64) : (64 - length % 64));
    if (!(pp = (char*)malloc((unsigned long)l)))
        return 0;
    for (i = 0; i < length; pp[i + 3 - 2 * (i % 4)] = str[i], i++);
    for (pp[i + 3 - 2 * (i % 4)] = 128, i++; i < l; pp[i + 3 - 2 * (i % 4)] = 0, i++);
    *((long*)(pp + l - 4)) = length << 3;
    *((long*)(pp + l - 8)) = length >> 29;
    for (ppend = pp + l; pp < ppend; pp += 64) {
        for (i = 0; i < 16; W[i] = ((long*)pp)[i], i++);
        for (i = 16; i < 64; W[i] = (SHA256_O1(W[i - 2]) + W[i - 7] + SHA256_O0(W[i - 15]) + W[i - 16]), i++);
        A = H0, B = H1, C = H2, D = H3, E = H4, F = H5, G = H6, H = H7;
        for (i = 0; i < 64; i++) {
            T1 = H + SHA256_E1(E) + SHA256_Ch(E, F, G) + K[i] + W[i];
            T2 = SHA256_E0(A) + SHA256_Maj(A, B, C);
            H = G, G = F, F = E, E = D + T1, D = C, C = B, B = A, A = T1 + T2;
        }
        H0 += A, H1 += B, H2 += C, H3 += D, H4 += E, H5 += F, H6 += G, H7 += H;
    }
    free(pp - l);
    Hash[0] = H0;
    Hash[1] = H1;
    Hash[2] = H2;
    Hash[3] = H3;
    Hash[4] = H4;
    Hash[5] = H5;
    Hash[6] = H6;
    Hash[7] = H7;
    return Hash;
}
void padding(const char* input, uint8_t* output, size_t length) {
    size_t l = length + ((length % 64 > 56) ? (128 - length % 64) : (64 - length % 64));
    uint8_t* pp = (uint8_t*)malloc(l);
    if (!pp) {
        return;
    }

    std::memcpy(pp, input, length);
    pp[length] = 0x80;

    for (size_t i = length + 1; i < l - 8; i++) {
        pp[i] = 0;
    }

    uint64_t bitLength = (uint64_t)length << 3;
    for (size_t i = 0; i < 8; i++) {
        pp[l - 8 + i] = (bitLength >> (56 - i * 8)) & 0xFF;
    }

    std::memcpy(output, pp, l);
    free(pp);
}

unsigned int* StrSHA256_length_extension_Attack(unsigned int* latestHash, unsigned char* append, long long msglen,long long appendlen, unsigned int* Hash) {
    char* pp, * ppend;
    long l_1,l_2, i, W[64], T1, T2, A, B, C, D, E, F, G, H, H0, H1, H2, H3, H4, H5, H6, H7;
    H0 = latestHash[0], H1 = latestHash[1], H2 = latestHash[2], H3 = latestHash[3];
    H4 = latestHash[4], H5 = latestHash[5], H6 = latestHash[6], H7 = latestHash[7];
    long K[64] = {
        0x428a2f98, 0x71374491, 0xb5c0fbcf, 0xe9b5dba5, 0x3956c25b, 0x59f111f1, 0x923f82a4, 0xab1c5ed5,
        0xd807aa98, 0x12835b01, 0x243185be, 0x550c7dc3, 0x72be5d74, 0x80deb1fe, 0x9bdc06a7, 0xc19bf174,
        0xe49b69c1, 0xefbe4786, 0x0fc19dc6, 0x240ca1cc, 0x2de92c6f, 0x4a7484aa, 0x5cb0a9dc, 0x76f988da,
        0x983e5152, 0xa831c66d, 0xb00327c8, 0xbf597fc7, 0xc6e00bf3, 0xd5a79147, 0x06ca6351, 0x14292967,
        0x27b70a85, 0x2e1b2138, 0x4d2c6dfc, 0x53380d13, 0x650a7354, 0x766a0abb, 0x81c2c92e, 0x92722c85,
        0xa2bfe8a1, 0xa81a664b, 0xc24b8b70, 0xc76c51a3, 0xd192e819, 0xd6990624, 0xf40e3585, 0x106aa070,
        0x19a4c116, 0x1e376c08, 0x2748774c, 0x34b0bcb5, 0x391c0cb3, 0x4ed8aa4a, 0x5b9cca4f, 0x682e6ff3,
        0x748f82ee, 0x78a5636f, 0x84c87814, 0x8cc70208, 0x90befffa, 0xa4506ceb, 0xbef9a3f7, 0xc67178f2,
    };
    //l_1 = msglen + ((msglen % 64 > 56) ? (128 - msglen % 64) : (64 - msglen % 64));
    l_2 = appendlen + ((appendlen % 64 > 56) ? (128 - appendlen % 64) : (64 - appendlen % 64));
    if (!(pp = (char*)malloc((unsigned long)l_2))) return 0;
    for (i = 0; i < appendlen; pp[i + 3 - 2 * (i % 4)] = append[i], i++);
    for (pp[i + 3 - 2 * (i % 4)] = 128, i++; i < l_2; pp[i + 3 - 2 * (i % 4)] = 0, i++);
    *((long*)(pp + l_2 - 4)) = msglen << 3;
    *((long*)(pp + l_2 - 8)) = msglen >> 29;
    for (ppend = pp + l_2; pp < ppend; pp += 64) {
        for (i = 0; i < 16; W[i] = ((long*)pp)[i], i++);
        for (i = 16; i < 64; W[i] = (SHA256_O1(W[i - 2]) + W[i - 7] + SHA256_O0(W[i - 15]) + W[i - 16]), i++);
        A = H0, B = H1, C = H2, D = H3, E = H4, F = H5, G = H6, H = H7;
        for (i = 0; i < 64; i++) {
            T1 = H + SHA256_E1(E) + SHA256_Ch(E, F, G) + K[i] + W[i];
            T2 = SHA256_E0(A) + SHA256_Maj(A, B, C);
            H = G, G = F, F = E, E = D + T1, D = C, C = B, B = A, A = T1 + T2;
        }
        H0 += A, H1 += B, H2 += C, H3 += D, H4 += E, H5 += F, H6 += G, H7 += H;
    }
    free(pp - l_2);
    Hash[0] = H0;
    Hash[1] = H1;
    Hash[2] = H2;
    Hash[3] = H3;
    Hash[4] = H4;
    Hash[5] = H5;
    Hash[6] = H6;
    Hash[7] = H7;
    return Hash;
}



int main(void) {
    unsigned int Hash[8] = { 0 };
    unsigned int Result_Hash[8] = { 0 };
    unsigned int Attack_Hash[8] = { 0 };
    char* secret = (char*)"secret";
    //进行长度扩展攻击 secret内容未知，secret长度、H(secret)已知 
    StrSHA256(secret, strlen(secret), Hash);//得到服务器返回的Hash值 
    cout << "H(secret||data||padding): " << endl;
    for (int j = 0; j < 8; j++) {
        cout << hex << Hash[j] << " ";
    }
    cout << endl;
    //希望计算Hash(secret||padding||append)
    //服务器端计算结果
    int length = strlen(secret);
    size_t l = length + ((length % 64 > 56) ? (128 - length % 64) : (64 - length % 64));
    uint8_t* message_padding = (uint8_t*)malloc(l);
    padding(secret, message_padding, strlen(secret));
    char* append = (char*)"append";
    int len_append = strlen(append);
    unsigned char* message_append = new unsigned char[64 + len_append + 1];
    message_append[64 + len_append] = '\0';
    memcpy(message_append, message_padding, 64);
    memcpy(&message_append[64], append, len_append);
    cout << "已知secret内容,由服务器计算出,H(secret||padding||append):" << endl;
    StrSHA256((char*)message_append, 70, Result_Hash);
    for (int j = 0; j < 8; j++) {
        cout << hex << Result_Hash[j] << " ";
    }
    cout << endl << endl;
    //进行长度扩展攻击
    cout << "未知secret内容，已知secret长度与H(secret)，进行长度扩展攻击,H(secret||padding||append): " << endl;
    StrSHA256_length_extension_Attack(Hash, (unsigned char*)append, 70, len_append, Attack_Hash);
    for (int j = 0; j < 8; j++) {
        cout << hex << Attack_Hash[j] << " ";
    }
    cout << endl;
    return 0;
}
