#include <bits/stdc++.h>
using namespace std;
#define FF1(x, y, z) (x ^ y ^ z)
#define FF2(x, y, z) ((x & y) | (x & z) | (y & z))
#define GG1(x, y, z) (x ^ y ^ z)
#define GG2(x, y, z) ((x & y) | (~x & z))
#define P0(x) ((x) ^ ((x << 9) | (x >> 23)) ^ ((x << 17) | (x >> 15)))
#define P1(x) ((x) ^ ((x << 15) | (x >> 17)) ^ ((x << 23) | (x >> 9)))
#define ROL(x, n) ((x << n) | (x >> (32-n)))

unsigned int V[8] = {0x7380166f, 0x4914b2b9, 0x172442d7, 0xda8a0600, 0xa96f30bc, 0x163138aa, 0xe38dee4d, 0xb0fb0e4e};
static unsigned int Vcp[8] = {0x7380166f, 0x4914b2b9, 0x172442d7, 0xda8a0600, 0xa96f30bc, 0x163138aa, 0xe38dee4d, 0xb0fb0e4e};
unsigned int T1 = 0x79cc4519;
unsigned int T2 = 0x7a879d8a;
unsigned int SS1, SS2, TT1, TT2;

unsigned int msg_pad(unsigned char* msg, unsigned int len){ // len : number of bytes
	unsigned int u = len % 64;
	unsigned int l = (len << 3);
	if(u < 56){
		msg[len++] = 0x80;
		u++;
		while(u < 56){
			msg[len++] = 0;
			u++;
		}
	}
	else if(u > 56){
		msg[len++] = 0x80;
		u++;
		while(u < 120){
			msg[len++] = 0;
			u++;
		}
	}
	for(int i = 0; i < 4; i++)msg[len++] = 0;
	for(int i = 0; i < 4; i++){
		msg[len++] = (l >> ((3-i) << 3)) & 0xff;
	}
	return len;
}

void CF(unsigned int* V, unsigned char* B){
	unsigned int W[68];
	unsigned int W_0[64];
	unsigned int cpv[8];
	memcpy(cpv, V, 32);
	for(int i = 0; i < 16; i++){
		memcpy(W+i, B+i*4, 4);
		W[i] = (W[i] << 24) | ((W[i] & 0xff00) << 8) | ((W[i] & 0xff0000) >> 8) | (W[i] >> 24);
	}
	for(int i = 16; i < 68; i++){
		W[i] = P1((W[i-16] ^ W[i-9] ^ ROL(W[i-3], 15))) ^ ROL(W[i-13], 7) ^ W[i-6];
	}
	
	for(int i = 0; i < 64; i++){
		W_0[i] = W[i] ^ W[i+4];
	}

	for(int j = 0; j < 64; j++){
		if(j < 16)SS1 = ROL((ROL(V[0], 12) + V[4] + ROL(T1, j)), 7);
		else SS1 = ROL((ROL(V[0], 12) + V[4] + ROL(T2, j)), 7);

		SS2 = SS1 ^ ROL(V[0], 12);

		if(j < 16)TT1 = FF1(V[0], V[1], V[2]) + V[3] + SS2 + W_0[j];
		else TT1 = FF2(V[0], V[1], V[2]) + V[3] + SS2 + W_0[j];

		if(j < 16)TT2 = GG1(V[4], V[5], V[6]) + V[7] + SS1 + W[j];
		else TT2 = GG2(V[4], V[5], V[6]) + V[7] + SS1 + W[j];

		V[3] = V[2];
		V[2] = ROL(V[1], 9);
		V[1] = V[0];
		V[0] = TT1;
		V[7] = V[6];
		V[6] = ROL(V[5], 19);
		V[5] = V[4];
		V[4] = P0(TT2);
	}
	for(int i = 0; i < 8; i++){
		V[i] ^= cpv[i];
	}
}

void SM3_hash(unsigned char* msg, unsigned int len){ // len : number of bytes
	int N = (len >> 6); // 64bytes per group 
	unsigned char B[N][64];
	for(int i = 0; i < N; i++){
		memcpy(B[i], msg+i*64, 64);
	}
	for(int i = 0; i < N; i++){
		CF(V, B[i]);
	}

}

int main(){
	/*
	unsigned char msg[128];
	for(int i = 0; i < 16; i++){
		for(int j = 0; j < 4; j++){
			msg[i*4+j] = 'a' + j;
		}
	}
	unsigned int length = msg_pad(msg, 64);
	SM3_hash(msg, length);
	*/
	FILE *fpout = NULL;
	fpout = fopen("output_SM3.txt", "w+");
	unsigned char msg[20000];
	for(int i = 0; i < 2048; i++){
		msg[i] = rand() % 256;
	}
	unsigned int length = msg_pad(msg, 2048);
//	clock_t starttime, endtime;
//	double totaltime;
//	for(int i = 0; i < 6400; i++){
//		memcpy(V, Vcp, sizeof(Vcp));
//		starttime = clock();
		SM3_hash(msg, length);
//		endtime = clock();
//		totaltime += (double)(endtime - starttime);
//	}
//	cout << "The run time is: " << 1000 * totaltime / CLOCKS_PER_SEC << "ms" << endl;
	for(int i = 0 ; i < 8; i++){
		fprintf(fpout, "%08x", V[i]);
	}
	return 0;
}
