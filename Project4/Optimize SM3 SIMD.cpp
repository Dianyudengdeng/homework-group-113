#include<iostream>
#include <string>
#include <iomanip>
#include <chrono>
#include <immintrin.h> 
#include<cstring>
using namespace std;

static unsigned char message_buffer[16][64] = { 0 };
unsigned V[8] = { 0 };
__m512i V_1[8] = { 0 };
__m512i T0;
__m512i T1;


void SM3_init();
void SM3(unsigned char* msg[16], unsigned int msglen[16], unsigned int Hash[8][16]);
void CF(unsigned char msg[16][64]);
unsigned int rotate_left(unsigned int a, unsigned int k);
//unsigned int FF(unsigned int X, unsigned int  Y, unsigned int  Z, int j);
//unsigned int GG(unsigned int X, unsigned int  Y, unsigned int  Z, int j);

__m512i FF_1(__m512i X, __m512i  Y, __m512i  Z);
__m512i FF_2(__m512i X, __m512i  Y, __m512i  Z);
__m512i GG_1(__m512i X, __m512i  Y, __m512i  Z);
__m512i GG_2(__m512i X, __m512i  Y, __m512i  Z);


void SM3_init() {
	T0 = _mm512_set1_epi32(0x79cc4519);
	T1 = _mm512_set1_epi32(0x7a879d8a);
	V_1[0] = _mm512_set1_epi32(0x7380166f);
	V_1[1] = _mm512_set1_epi32(0x4914b2b9);
	V_1[2] = _mm512_set1_epi32(0x172442d7);
	V_1[3] = _mm512_set1_epi32(0xda8a0600);
	V_1[4] = _mm512_set1_epi32(0xa96f30bc);
	V_1[5] = _mm512_set1_epi32(0x163138aa);
	V_1[6] = _mm512_set1_epi32(0xe38dee4d);
	V_1[7] = _mm512_set1_epi32(0xb0fb0e4e);

}
//Padding + Output

void SM3(unsigned char* msg[16], unsigned int msglen[16], unsigned int Hash[8][16]) {
	int left;
	unsigned long long total = 0;
	SM3_init();
	for (int i = 0; i < 16; i++) {
		total = long long(msglen[i]) * 8;//总bit数
		left = msglen[i] % 64;//需要padding的分组长度
		memset(&message_buffer[i][left], 0, 64 - left);
		memcpy(message_buffer[i], msg[i], left);
		message_buffer[i][left] = 0x80;//完成0的填充
		if (left <= 55) {//检测剩余长度以填入64位的数据长度
			for (int j = 0; j < 8; j++)
				message_buffer[i][56 + j] = (total >> ((8 - 1 - j) * 8)) & 0xFF;
		}

	}

	CF(message_buffer);


	for (int i = 0; i < 8; i++) {
		_mm512_storeu_si512(Hash[i], V_1[i]);

	}
}



__m512i P_0(__m512i x) {
	return  _mm512_xor_si512(x, _mm512_xor_si512(_mm512_rol_epi32(x, 9), _mm512_rol_epi32(x, 17)));
}


__m512i P_1(__m512i x) {
	return _mm512_xor_si512(x, _mm512_xor_si512(_mm512_rol_epi32(x, 15), _mm512_rol_epi32(x, 23)));
}


__m512i FF_1(__m512i X, __m512i  Y, __m512i  Z) {
	return  _mm512_xor_si512(X , _mm512_xor_si512(Y , Z));
}
__m512i FF_2(__m512i X, __m512i  Y, __m512i  Z) {
	__m512i temp1 = _mm512_and_epi32(X, Y);
	__m512i temp2 = _mm512_and_epi32(X, Z);
	__m512i temp3 = _mm512_and_epi32(Y, Z);
	return _mm512_or_epi32(_mm512_or_epi32(temp1, temp2), temp3);
}

__m512i GG_1(__m512i X, __m512i  Y, __m512i  Z) {
	return  _mm512_xor_si512(X, _mm512_xor_si512(Y, Z));
}

__m512i GG_2(__m512i X, __m512i  Y, __m512i  Z) {
	__m512i temp1 = _mm512_and_epi32(X, Y);
	__m512i temp2 = _mm512_andnot_epi32(X, Z);
	return _mm512_or_epi32(temp1, temp2);
}



void CF(unsigned char msg[16][64]) {
	__m512i W[68];
	//unsigned int W_1[64];
	__m512i A, B, C, D, E, F, G, H;
	__m512i SS1, SS2, TT1, TT2;
	for (int j = 0; j < 16; j++) {
		unsigned int temp[16];
		for (int k = 0; k < 16; k++) {
			temp[k] = msg[k][j * 4 + 0] << 24 | msg[k][j * 4 + 1] << 16 | msg[k][j * 4 + 2] << 8 | msg[k][j * 4 + 3];
			/*temp[k+1] = msg[k + 1][j * 4 + 0] << 24 | msg[k + 1][j * 4 + 1] << 16 | msg[k + 1][j * 4 + 2] << 8 | msg[k + 1][j * 4 + 3];
			temp[k+2] = msg[k + 2][j * 4 + 0] << 24 | msg[k + 2][j * 4 + 1] << 16 | msg[k + 2][j * 4 + 2] << 8 | msg[k + 2][j * 4 + 3];
			temp[k+3] = msg[k + 3][j * 4 + 0] << 24 | msg[k + 3][j * 4 + 1] << 16 | msg[k + 3][j * 4 + 2] << 8 | msg[k + 3][j * 4 + 3];*/
		}
		W[j] = _mm512_set_epi32(temp[15], temp[14], temp[13], temp[12], temp[11], temp[10], temp[9], temp[8], temp[7], temp[6], temp[5], temp[4], temp[3], temp[2], temp[1], temp[0]);
	}
	for (int j = 16; j < 68; j++) {
		__m512i temp1 = _mm512_xor_si512(W[j - 16], W[j - 9]);
		__m512i temp2=_mm512_rol_epi32(W[j - 3], 15);
		__m512i temp3 = P_1(_mm512_xor_si512(temp1,temp2));
		__m512i temp4 = _mm512_xor_si512(_mm512_rol_epi32(W[j - 13], 7), W[j - 6]);
		W[j] = _mm512_xor_si512(temp3, temp4);
	}
	A = V_1[0];
	B = V_1[1];
	C = V_1[2];
	D = V_1[3];
	E = V_1[4];
	F = V_1[5];
	G = V_1[6];
	H = V_1[7];
	for (int j = 0; j < 16; j++) {
		__m512i temp = _mm512_rol_epi32(A, 12);
		__m512i shiftAmount = _mm512_set1_epi32(j);
		SS1 = _mm512_rol_epi32(_mm512_add_epi32(_mm512_add_epi32(temp,E),_mm512_rolv_epi32(T0, shiftAmount)), 7);
		SS2 = _mm512_xor_si512(SS1,temp);
		TT1 = _mm512_add_epi32(_mm512_add_epi32(FF_1(A, B, C), D), _mm512_add_epi32(SS2, _mm512_xor_si512(W[j], W[j + 4])));
		TT2 = _mm512_add_epi32(_mm512_add_epi32(GG_1(E, F, G), H), _mm512_add_epi32(SS1, W[j]));
		D = C;
		C = _mm512_rol_epi32(B, 9);
		B = A;
		A = TT1;
		H = G;
		G = _mm512_rol_epi32(F, 19);
		F = E;
		E = P_0(TT2);
	}
	for (int j = 16; j < 64; j++) {
		__m512i temp = _mm512_rol_epi32(A, 12);
		__m512i shiftAmount = _mm512_set1_epi32(j);
		SS1 = _mm512_rol_epi32(_mm512_add_epi32(_mm512_add_epi32(temp, E), _mm512_rolv_epi32(T1, shiftAmount)), 7);
		SS2 = _mm512_xor_si512(SS1, temp);
		TT1 = _mm512_add_epi32(_mm512_add_epi32(FF_2(A, B, C), D), _mm512_add_epi32(SS2, _mm512_xor_si512(W[j], W[j + 4])));
		TT2 = _mm512_add_epi32(_mm512_add_epi32(GG_2(E, F, G), H), _mm512_add_epi32(SS1, W[j]));
		D = C;
		C = _mm512_rol_epi32(B, 9);
		B = A;
		A = TT1;
		H = G;
		G = _mm512_rol_epi32(F, 19);
		F = E;
		E = P_0(TT2);
	}
	V_1[0] = _mm512_xor_si512(A , V_1[0]);
	V_1[1] = _mm512_xor_si512(B , V_1[1]);
	V_1[2] = _mm512_xor_si512(C , V_1[2]);
	V_1[3] = _mm512_xor_si512(D , V_1[3]);
	V_1[4] = _mm512_xor_si512(E , V_1[4]);
	V_1[5] = _mm512_xor_si512(F , V_1[5]);
	V_1[6] = _mm512_xor_si512(G , V_1[6]);
	V_1[7] = _mm512_xor_si512(H , V_1[7]);
	return;
}


int main() {

	unsigned int Hash[8][16] = { 0 };
	char* input[16];
	for (int i = 0; i < 16; i++) {
		std::string value = std::to_string(i);
		input[i] = new char[value.length() + 1];
		strcpy_s(input[i], value.length() + 1, value.c_str());
	}
	//input[1] = (char*)"abcd";
	////66c7f0f4 62eeedd9 d1f2d46b dc10e4e2 4167c487 5cf2f7a2 297da02b 8f4ba8e0
	unsigned int len[16];
	for (int i = 0; i < 16; i++) {
		len[i] = strlen(input[i]);
		cout << len[i];
	}
	
	auto start = std::chrono::high_resolution_clock::now();
	SM3((unsigned char**)input, len, Hash);
	auto end = std::chrono::high_resolution_clock::now();
	std::chrono::duration<double, std::milli> duration = end - start;
	std::cout << "Hash用时: " << duration.count() << " 毫秒" << std::endl;
	cout << "Hash: " << endl;;
	for (int i = 0; i < 16; i++) {
		for (int j = 0; j < 8; j++) {
			cout << hex << Hash[j][i] << " ";
		}
		cout << endl;
	}

}