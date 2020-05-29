#include <bits/stdc++.h>
#define SHL(x, n) ((x << n) | (x >> (32-n)))
#define SHR(x, n) ((x >> n) | (x << (32-n)))
using namespace std;

unsigned int ans_256[8];
static unsigned int H_256[8] = {0x6a09e667, 0xbb67ae85, 0x3c6ef372, 0xa54ff53a, 0x510e527f, 0x9b05688c, 0x1f83d9ab, 0x5be0cd19};

static unsigned int K[64] = {
	0x428a2f98, 0x71374491, 0xb5c0fbcf, 0xe9b5dba5, 0x3956c25b, 0x59f111f1, 0x923f82a4, 0xab1c5ed5,
	0xd807aa98, 0x12835b01, 0x243185be, 0x550c7dc3, 0x72be5d74, 0x80deb1fe, 0x9bdc06a7, 0xc19bf174,
	0xe49b69c1, 0xefbe4786, 0x0fc19dc6, 0x240ca1cc, 0x2de92c6f, 0x4a7484aa, 0x5cb0a9dc, 0x76f988da,
	0x983e5152, 0xa831c66d, 0xb00327c8, 0xbf597fc7, 0xc6e00bf3, 0xd5a79147, 0x06ca6351, 0x14292967,
	0x27b70a85, 0x2e1b2138, 0x4d2c6dfc, 0x53380d13, 0x650a7354, 0x766a0abb, 0x81c2c92e, 0x92722c85,
	0xa2bfe8a1, 0xa81a664b, 0xc24b8b70, 0xc76c51a3, 0xd192e819, 0xd6990624, 0xf40e3585, 0x106aa070,
	0x19a4c116, 0x1e376c08, 0x2748774c, 0x34b0bcb5, 0x391c0cb3, 0x4ed8aa4a, 0x5b9cca4f, 0x682e6ff3,
	0x748f82ee, 0x78a5636f, 0x84c87814, 0x8cc70208, 0x90befffa, 0xa4506ceb, 0xbef9a3f7, 0xc67178f2
};

int padding_32(unsigned char* t, int len){
	int u = (len << 3);
	int left = u % 512;
	if(left < 448){
		t[len++] = 0x80;
		left += 8;
		while(left < 448){
			t[len++] = 0;
			left += 8;
		}
	}
	else{
		t[len++] = 0x80;
		left += 8;
		while(left < 448 + 512){
			t[len++] = 0;
			left += 8;
		}
	}
	for(int i = 0; i < 4; i++)t[len++] = 0;
	for(int i = 0; i < 4; i++){
		t[len++] = (u >> ((3-i) << 3)) & 0xff;
	}
	return len;
}

void SHA_256(unsigned int word[][64], int chunknum){
	unsigned int s0, s1, ch, t1, maj, t2;
	unsigned int tmph[8], cpyh[8];
	memcpy(tmph, H_256, sizeof(H_256));
	for(int chunk = 0; chunk < chunknum; chunk++){
		for(int i = 16; i < 64; i++){
			s0 = SHR(word[chunk][i-15], 7) ^ SHR(word[chunk][i-15], 18) ^ (word[chunk][i-15] >> 3);
			s1 = SHR(word[chunk][i-2], 17) ^ SHR(word[chunk][i-2], 19) ^ (word[chunk][i-2] >> 10);
			word[chunk][i] = word[chunk][i-16] + s0 + s1 + word[chunk][i-7];
		}
		memcpy(cpyh, tmph, sizeof(tmph));
		for(int i = 0 ; i < 64; i++){
			s0 = SHR(tmph[0], 2) ^ SHR(tmph[0], 13) ^ SHR(tmph[0], 22);
			s1 = SHR(tmph[4], 6) ^ SHR(tmph[4], 11) ^ SHR(tmph[4], 25);
			maj = (tmph[0] & tmph[1]) ^ (tmph[0] & tmph[2]) ^ (tmph[1] & tmph[2]);
			ch = (tmph[4] & tmph[5]) ^ ((~tmph[4]) & tmph[6]);
			t1 = tmph[7] + s1 + ch + K[i] + word[chunk][i];
			t2 = s0 + maj;
			tmph[7] = tmph[6];
			tmph[6] = tmph[5];
			tmph[5] = tmph[4];
			tmph[4] = tmph[3] + t1;
			tmph[3] = tmph[2];
			tmph[2] = tmph[1];
			tmph[1] = tmph[0];
			tmph[0] = t1 + t2;
		}
		for(int i = 0; i < 8; i++){
			tmph[i] += cpyh[i];
		}
	}
	memcpy(ans_256, tmph, sizeof(tmph));
	/*
	for(int i = 0; i < 8; i++){
		printf("%02x ", ans_256[i]);
	}
	printf("\n");*/
}

int main(){
	/*
	string s = "chengyua17_2017011429";
	unsigned char t[20000];
	for(int i = 0; i < s.length(); i++){
		t[i] = s[i];
	}
	int l = padding_32(t, s.length());
	int chunknum = (l >> 6);
	unsigned int word[chunknum][64];
	memcpy(word, t, l);
	for(int i = 0; i < chunknum; i++){
		for(int j = 0; j < 16; j++){
			word[i][j] = (word[i][j] << 24) | ((word[i][j] & 0xff00) << 8) | ((word[i][j] & 0xff0000) >> 8) | (word[i][j] >> 24);
		}
	}
	SHA_256(word, chunknum);*/
	FILE *fpout = NULL;
	fpout = fopen("output_SHA2.txt", "w+");
	unsigned char t[20000];
	for(int i = 0; i < 2048; i++){
		t[i] = rand() % 256;
	}
	int l = padding_32(t, 2048);
	int chunknum = (l >> 6);
	unsigned int word[chunknum][64];
	memcpy(word, t, l);
	for(int i = 0; i < chunknum; i++){
		for(int j = 0; j < 16; j++){
			word[i][j] = (word[i][j] << 24) | ((word[i][j] & 0xff00) << 8) | ((word[i][j] & 0xff0000) >> 8) | (word[i][j] >> 24);
		}
	}
//	clock_t startTime, endTime;
//	double totalTime;
//	for(int i = 0; i < 6400; i++){
//		startTime = clock();
		SHA_256(word, chunknum);
//		endTime = clock();
//		totalTime += (double)(endTime - startTime);
//	}
//	cout << "The run time is: " << 1000 * totalTime / CLOCKS_PER_SEC << "ms" << endl;
	for(int i = 0; i < 8; i++){
		fprintf(fpout, "%08x", ans_256[i]);
	}

	return 0;
}