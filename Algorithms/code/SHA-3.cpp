#pragma GCC optimize("-O2")
#include <bits/stdc++.h>
#define ROTR(x, n) ((x >> n) | (x << (64-n)))
#define ROTL(x, n) ((x << n) | (x >> (64-n)))

typedef unsigned long long ull;

static ull rc[24] = {
	0x0000000000000001, 0x0000000000008082, 0x800000000000808A, 0x8000000080008000, 0x000000000000808B, 0x0000000080000001,
    0x8000000080008081, 0x8000000000008009, 0x000000000000008A, 0x0000000000000088, 0x0000000080008009, 0x000000008000000A,
    0x000000008000808B, 0x800000000000008B, 0x8000000000008089, 0x8000000000008003, 0x8000000000008002, 0x8000000000000080,
    0x000000000000800A, 0x800000008000000A, 0x8000000080008081, 0x8000000000008080, 0x0000000080000001, 0x8000000080008008
};

static int shiftoff[24] = {1,62,28,27,36,44,6,55,20,3,10,43,25,39,41,45,15,21,8,18,2,61,56,14};
static int magicindex[24] = {1,6,9,22,14,20,2,12,13,19,23,15,4,24,21,8,16,5,3,18,17,11,7,10};
using namespace std;

inline void theta(ull A[]){
	ull C[5],D[5];
	for(int i = 0; i < 5; i++){
		C[i] = A[i] ^ A[i+5] ^ A[i+10] ^ A[i+15] ^ A[i+20];
	}
	D[0] = ROTL(C[1], 1) ^ C[4];
	D[1] = ROTL(C[2], 1) ^ C[0];
	D[2] = ROTL(C[3], 1) ^ C[1];
    D[3] = ROTL(C[4], 1) ^ C[2];
    D[4] = ROTL(C[0], 1) ^ C[3];

    for(int i = 0; i < 5; ++i) {
        A[i] ^= D[i];
        A[i+5] ^= D[i];
        A[i+10] ^= D[i];
        A[i+15] ^= D[i];
        A[i+20] ^= D[i];
    }
}
inline void pi(ull A[]) {
    ull tmp = A[1];
    for(int i = 0; i < 23; i++){
    	A[magicindex[i]] = A[magicindex[i+1]];
    }
    A[10] = tmp;
}
inline void rho(ull A[]){
	for(int i = 0; i < 25; i += 5) {
        ull A0 = A[i], A1 = A[i+1];
        A[i] ^= A[i+2] & (~A1);
        A[i+1] ^= A[i+3] & (~A[i+2]);
        A[i+2] ^= (~A[i+3]) & A[i+4];
        A[i+3] ^= (~A[i+4]) & A0;
        A[i+4] ^= (~A0) & A1;
    }
}
inline void permute(ull s[]){
	for(int i = 0; i < 24; i++){
		theta(s);
		for(int j = 0; j < 24; j++){
			s[j+1] = ROTL(s[j+1], shiftoff[j]);
		}
		pi(s);
		rho(s);
		*s ^= rc[i];
	}
}

inline void SHA3_256(const unsigned char* data, ull h[]){
	ull tmp ;
	for(int i = 0; i <= 16; i++){
		tmp = 0;
		for(int j = 0; j < 8; j++){
			tmp |= (ull(data[(i << 3) + j])) << (j << 3);
		}
		h[i] ^= tmp;
	}
	permute(h);
}

inline void entry(const void* data, int len, unsigned char* out){
	unsigned char* d = (unsigned char*)data;
	ull h[25] = {0};
	for(int i = 0; i < len / 136; i++){
		SHA3_256(d + i * 136, h);
	}
	unsigned char buffer[136] = {0};
	int pos = (len / 136) * 136;
	memcpy(buffer, d + pos, len % 136);
	len %= 136;
	buffer[len] |= 0x06;
	buffer[135] |= 0x80;

	SHA3_256(buffer, h);
	memcpy(out, h, 32);
}

int main(){
	/*
	string input = "chengyua17_2017011429";
	unsigned char out[32];
	entry(input.data(), input.length(), out);
	for(int i = 0; i < 32; i++){
		printf("%02x", out[i]);
	}
	printf("\n");
	*/
	FILE *fpout = NULL;
	fpout = fopen("output_SHA3.txt", "w+");
	unsigned char text[3000];
	string input = "";
	for(int i = 0; i < 2048; i++){
		text[i] = rand() % 256;
		input += text[i];
	}
	unsigned char out[32];
//	clock_t starttime, endtime;
//	double totaltime;
//	for(int i = 0; i < 6400; i++){
//		starttime = clock();
		entry(input.data(), input.length(), out);
//		endtime = clock();
//		totaltime += (double)(endtime - starttime);
//	}
//	cout << "The run time is: " << 1000 * totaltime / CLOCKS_PER_SEC << "ms" << endl;
	for(int i = 0 ; i < 32; i++){
		fprintf(fpout, "%02x", out[i]);
	}
	return 0;
}