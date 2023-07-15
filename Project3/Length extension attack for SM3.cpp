#include<iostream>
#include <cstring>
#include <iomanip>
#include <chrono>
#define _CRT_SECURE_NO_WARNINGS
using namespace std;

static unsigned char message_buffer[64] = { 0 };
static unsigned int V[8] = { 0 };
static unsigned int T[64] = { 0 };

void SM3_init();
void SM3(unsigned char* msg, unsigned int msglen, unsigned int* Hash);
unsigned char* Padding(unsigned char* msg);
void CF(unsigned char* msg);
unsigned int rotate_left(unsigned int a, unsigned int k);
unsigned int FF_1(unsigned int X, unsigned int  Y, unsigned int  Z);
unsigned int FF_2(unsigned int X, unsigned int  Y, unsigned int  Z);
unsigned int GG_1(unsigned int X, unsigned int  Y, unsigned int  Z);
unsigned int GG_2(unsigned int X, unsigned int  Y, unsigned int  Z);
void SM3_length_extension_Attack(unsigned int* latestHash, unsigned char* append, unsigned int msglen, unsigned int appendlen, unsigned int* Hash);

void SM3_init() {
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
void SM3(unsigned char* msg, unsigned int msglen, unsigned int* Hash) {
	unsigned int i;
	int left = 0;
	unsigned long long total = 0;
	SM3_init();
	for (i = 0; i < msglen / 64; i++) {
		memcpy(message_buffer, msg + i * 64, 64);
		CF(message_buffer);
	}
	total = long long(msglen) * 8;//总bit数
	left = msglen % 64;//需要padding的分组长度
	memset(&message_buffer[left], 0, 64 - left);
	memcpy(message_buffer, msg + i * 64, left);
	message_buffer[left] = 0x80;//完成0的填充

	if (left <= 55) {//检测剩余长度以填入64位的数据长度
		for (i = 0; i < 8; i++)
			message_buffer[56 + i] = (total >> ((8 - 1 - i) * 8)) & 0xFF;
		CF(message_buffer);
	}
	else {
		CF(message_buffer);
		memset(message_buffer, 0, 64);
		for (i = 0; i < 8; i++)
			message_buffer[56 + i] = (total >> ((8 - 1 - i) * 8)) & 0xFF;
		CF(message_buffer);
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

void CF(unsigned char* msg) {
	unsigned int W[68];
	//unsigned int W_1[64];
	unsigned int A, B, C, D, E, F, G, H;
	unsigned int SS1, SS2, TT1, TT2;
	for (int j = 0; j < 16; j++)
		W[j] = msg[j * 4 + 0] << 24 | msg[j * 4 + 1] << 16 | msg[j * 4 + 2] << 8 | msg[j * 4 + 3];
	for (int j = 16; j < 68; j++)
		W[j] = P_1(W[j - 16] ^ W[j - 9] ^ (rotate_left(W[j - 3], 15))) ^ (rotate_left(W[j - 13], 7)) ^ W[j - 6];
	//for (int j = 0; j < 64; j++)
	//	W_1[j] = W[j] ^ W[j + 4];

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

unsigned char* Padding(unsigned char* msg) {
	unsigned int msglen = strlen((char*)msg);
	int i = msglen / 64;
	int left = msglen % 64;
	unsigned long long total = long long(msglen) * 8;
	unsigned char* Padding_message;
	if (left <= 55) {//检测剩余长度以填入64位的数据长度
		Padding_message = new unsigned char[(i + 1) * 64 + 1];
		Padding_message[(i + 1) * 64] = '\0';
	}
	else {
		Padding_message = new unsigned char[(i + 2) * 64 + 1];
		Padding_message[(i + 2) * 64] = '\0';
	}
	memcpy(Padding_message, msg, msglen);
	if (left <= 55) {
		memset(&Padding_message[i * 64 + left], 0, 64 - left);
		for (int j = 0; j < 8; j++)
			Padding_message[(i * 64) + 56 + j] = (total >> ((8 - 1 - j) * 8)) & 0xFF;
	}
	else {
		memset(&Padding_message[i * 64 + left], 0, 128 - left);
		for (int j = 0; j < 8; j++)
			Padding_message[(i + 1) * 64 + 56 + j] = (total >> ((8 - 1 - j) * 8)) & 0xFF;
	}
	Padding_message[i * 64 + left] = 0x80;
	return Padding_message;
}

void SM3_length_extension_Attack(unsigned int* latestHash, unsigned char* append, unsigned int msglen,unsigned int appendlen, unsigned int* Hash) {
	unsigned int i;
	int left = 0;
	unsigned long long total = 0;
	for (i = 0; i < 8; i++) {
		V[i] = latestHash[i];
	}
	for (i = 0; i < appendlen / 64; i++) {
		memcpy(message_buffer, append + i * 64, 64);
		CF(message_buffer);
	}
	total = long long(msglen) * 8;//总bit数
	left = msglen % 64;//需要padding的分组长度
	memset(&message_buffer[left], 0, 64 - left);
	memcpy(message_buffer, append + i * 64, left);
	message_buffer[left] = 0x80;//完成0的填充

	if (left <= 55) {//检测剩余长度以填入64位的数据长度
		for (i = 0; i < 8; i++)
			message_buffer[56 + i] = (total >> ((8 - 1 - i) * 8)) & 0xFF;
		CF(message_buffer);
	}
	else {
		CF(message_buffer);
		memset(message_buffer, 0, 64);
		for (i = 0; i < 8; i++)
			message_buffer[56 + i] = (total >> ((8 - 1 - i) * 8)) & 0xFF;
		CF(message_buffer);
	}
	memcpy(Hash, V, 32);
}

int main() {
	unsigned int Hash[8] = { 0 };
	unsigned int Result_Hash[8] = { 0 };
	unsigned int Attack_Hash[8] = { 0 };
	
	char* secret = (char*)"secret";
	char* data = (char*)"data";
	int len_secret = strlen(secret);
	int len_data = strlen(data);
	int totalLen = len_secret + len_data;
	//进行长度扩展攻击 secret内容未知，secret长度已知
	unsigned char* mergedStr = new unsigned char[totalLen + 1];
	mergedStr[totalLen] = '\0';
	memcpy(mergedStr, secret, len_secret);
	memcpy(&mergedStr[len_secret], data, len_data);
	cout << "H(secret||data||padding): " << endl;
	SM3(mergedStr, totalLen, Hash);//得到服务器返回的Hash值 
	for (int j = 0; j < 8; j++) {
		cout << hex << Hash[j] << " ";
	}
	cout << endl << endl;
	//希望计算Hash(secret||data||padding||append)
	//服务器端计算结果
	unsigned char* msg_padding = Padding((unsigned char*)mergedStr);
	char* append = (char*)"append";
	int len_append = strlen(append);
	unsigned char* message_append = new unsigned char[64 + len_append + 1];
	message_append[64 + len_append] = '\0';
	memcpy(message_append, msg_padding, 64);
	memcpy(&message_append[64], append, len_append);
	cout << "已知secret内容,由服务器计算出,H(secret||data||padding||append):" << endl;
	SM3(message_append, 70, Result_Hash);
	for (int j = 0; j < 8; j++) {
		cout << hex << Result_Hash[j] << " ";
	}
	cout << endl << endl;
	//进行长度扩展攻击
	cout << "未知secret内容，已知secret长度与H(secret||data||padding)，进行长度扩展攻击,H(secret||data||padding||append): " << endl;
	SM3_length_extension_Attack(Hash, (unsigned char*)append, 70, len_append, Attack_Hash);
	for (int j = 0; j < 8; j++) {
		cout << hex << Attack_Hash[j] << " ";
	}
	cout << endl;
}