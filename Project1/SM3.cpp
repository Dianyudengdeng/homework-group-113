#include <iostream>
#include <string>
#include <iomanip>
#include <chrono>

using namespace std;



void SM3_init(unsigned int* V);
void SM3(uint8_t* msg, unsigned int msglen, unsigned int* Hash);
void CF(uint8_t* msg, unsigned int* V);
unsigned int rotate_left(unsigned int a, unsigned int k);
unsigned int FF_1(unsigned int X, unsigned int  Y, unsigned int  Z);
unsigned int FF_2(unsigned int X, unsigned int  Y, unsigned int  Z);
unsigned int GG_1(unsigned int X, unsigned int  Y, unsigned int  Z);
unsigned int GG_2(unsigned int X, unsigned int  Y, unsigned int  Z);

void SM3_init(unsigned int *V) {
	V[0] = 0x7380166f;
	V[1] = 0x4914b2b9;
	V[2] = 0x172442d7;
	V[3] = 0xda8a0600;
	V[4] = 0xa96f30bc;
	V[5] = 0x163138aa;
	V[6] = 0xe38dee4d;
	V[7] = 0xb0fb0e4e;

}
//Padding + Output
void SM3(uint8_t* msg, unsigned int msglen, unsigned int* Hash) {
	uint8_t message_buffer[64] = { 0 };
	unsigned int V[8] = { 0 };
	int i;
	int left = 0;
	unsigned long long total = 0;
	SM3_init(V);
	for (i = 0; i < msglen / 64; i++) {
		memcpy(message_buffer, msg + i * 64, 64);
		CF(message_buffer, V);
	}
	total = long long(msglen) * 8;//总bit数
	left = msglen % 64;//需要padding的分组长度
	memset(&message_buffer[left], 0, 64 - left);
	memcpy(message_buffer, msg + i * 64, left);
	message_buffer[left] = 0x80;//完成0的填充

	if (left <= 55) {//检测剩余长度以填入64位的数据长度
		for (i = 0; i < 8; i++)
			message_buffer[56 + i] = (total >> ((8 - 1 - i) * 8)) & 0xFF;
		CF(message_buffer, V);
	}
	else {
		CF(message_buffer, V);
		memset(message_buffer, 0, 64);
		for (i = 0; i < 8; i++)
			message_buffer[56 + i] = (total >> ((8 - 1 - i) * 8)) & 0xFF;
		CF(message_buffer, V);
	}
	memcpy(Hash, V, 32);
}
//Expansion + Compression
unsigned int rotate_left(unsigned int a, unsigned int k) {
	k = k % 32;
	return ((a << k) & 0xFFFFFFFF) | ((a & 0xFFFFFFFF) >> (32 - k));
}

unsigned int P_0(unsigned int x) {
	return x ^ (rotate_left(x, 9)) ^ (rotate_left(x, 17));
}

unsigned int P_1(unsigned int x) {
	return x ^ (rotate_left(x, 15)) ^ (rotate_left(x, 23));
}

unsigned int FF_1(unsigned int X, unsigned int  Y, unsigned int  Z) {
	return  (X ^ Y ^ Z);

}

unsigned int FF_2(unsigned int X, unsigned int  Y, unsigned int  Z) {
	return ((X & Y) | (X & Z) | (Y & Z));

}

unsigned int GG_1(unsigned int X, unsigned int  Y, unsigned int  Z) {
	return (X ^ Y ^ Z);

}

unsigned int GG_2(unsigned int X, unsigned int  Y, unsigned int  Z) {
	return ((X & Y) | ((~X) & Z));

}

void CF(uint8_t* msg, unsigned int* V) {
	unsigned int W[68];
	//unsigned int W_1[64];
	unsigned int A, B, C, D, E, F, G, H;
	unsigned int SS1, SS2, TT1, TT2;
	for (int j = 0; j < 16; j++)
		W[j] = msg[j * 4 + 0] << 24 | msg[j * 4 + 1] << 16 | msg[j * 4 + 2] << 8 | msg[j * 4 + 3];
	for (int j = 16; j < 68; j++)
		W[j] = P_1(W[j - 16] ^ W[j - 9] ^ (rotate_left(W[j - 3], 15))) ^ (rotate_left(W[j - 13], 7)) ^ W[j - 6];

	A = V[0];
	B = V[1];
	C = V[2];
	D = V[3];
	E = V[4];
	F = V[5];
	G = V[6];
	H = V[7];
	for (int j = 0; j < 16; j++) {
		SS1 = rotate_left(((rotate_left(A, 12)) + E + (rotate_left(0x79cc4519, j))) & 0xFFFFFFFF, 7);
		SS2 = SS1 ^ (rotate_left(A, 12));
		TT1 = (FF_1(A, B, C) + D + SS2 + (W[j] ^ W[j + 4])) & 0xFFFFFFFF;
		TT2 = (GG_1(E, F, G) + H + SS1 + W[j]) & 0xFFFFFFFF;
		D = C;
		C = rotate_left(B, 9);
		B = A;
		A = TT1;
		H = G;
		G = rotate_left(F, 19);
		F = E;
		E = P_0(TT2);
	}
	for (int j = 16; j < 64; j++) {
		SS1 = rotate_left(((rotate_left(A, 12)) + E + (rotate_left(0x7a879d8a, j))) & 0xFFFFFFFF, 7);
		SS2 = SS1 ^ (rotate_left(A, 12));
		TT1 = (FF_2(A, B, C) + D + SS2 + (W[j] ^ W[j + 4])) & 0xFFFFFFFF;
		TT2 = (GG_2(E, F, G) + H + SS1 + W[j]) & 0xFFFFFFFF;
		D = C;
		C = rotate_left(B, 9);
		B = A;
		A = TT1;
		H = G;
		G = rotate_left(F, 19);
		F = E;
		E = P_0(TT2);
	}

	V[0] = (A ^ V[0]);
	V[1] = (B ^ V[1]);
	V[2] = (C ^ V[2]);
	V[3] = (D ^ V[3]);
	V[4] = (E ^ V[4]);
	V[5] = (F ^ V[5]);
	V[6] = (G ^ V[6]);
	V[7] = (H ^ V[7]);
	return;
}
//int main() {
//	unsigned int Hash[8];
//	uint8_t* input = (uint8_t*)"abc";
//	auto start = std::chrono::high_resolution_clock::now();
//
//	SM3(input, strlen((char*)input), Hash);
//
//	auto end = std::chrono::high_resolution_clock::now();
//	std::chrono::duration<double, std::micro> duration = end - start;
//	std::cout << "Hash用时: " << duration.count() << " 微秒" << std::endl;
//
//	for (int i = 0; i < 8; i++) {
//		cout << hex << Hash[i] << " ";
//	}
//	cout << endl;
//
//}