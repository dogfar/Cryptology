#pragma GCC optimize("-O3")
#include <bits/stdc++.h>
using namespace std;

static int Box_1C[28] = 
{
	57, 49, 41, 33, 25, 17, 9,
	1, 58, 50, 42, 34, 26, 18,
	10, 2, 59, 51, 43, 35, 27,
	19, 11, 3, 60, 52, 44, 36
};
static int Box_1D[28] = 
{
	63, 55, 47, 39, 31, 23, 15,
	7, 62, 54, 46, 38, 30, 22, 
	14, 6, 61, 53, 45, 37, 29, 
	21, 13,  5, 28, 20, 12, 4
};
static int shiftnumber[16] = {1, 1, 2, 2, 2, 2, 2, 2, 1, 2, 2, 2, 2, 2, 2, 1};
static int Box_2[48] = 
{
	14, 17, 11, 24, 1, 5, 
	3, 28, 15, 6, 21, 10, 
	23, 19, 12, 4, 26, 8, 
	16, 7, 27, 20, 13, 2, 
	41, 52, 31, 37, 47, 55, 
	30, 40, 51, 45, 33, 48, 
	44, 49, 39, 56, 34, 53, 
	46, 42, 50, 36, 29, 32
};
static int IP[64] = 
{
	58, 50, 42, 34, 26, 18, 10, 2, 
	60, 52, 44, 36, 28, 20, 12, 4, 
	62, 54, 46, 38, 30, 22, 14, 6, 
	64, 56, 48, 40, 32, 24, 16, 8, 
	57, 49, 41, 33, 25, 17, 9, 1, 
	59, 51, 43, 35, 27, 19, 11, 3, 
	61, 53, 45, 37, 29, 21, 13, 5, 
	63, 55, 47, 39, 31, 23, 15, 7
};
static int Box_E[48] = 
{
	32, 1, 2, 3, 4, 5, 
	4, 5, 6, 7, 8, 9, 
	8,  9, 10, 11, 12, 13, 
	12, 13, 14, 15, 16, 17, 
	16, 17, 18, 19, 20, 21, 
	20, 21, 22, 23, 24, 25, 
	24, 25, 26, 27, 28, 29, 
	28, 29, 30, 31, 32, 1
};
static int Box_S[8][4][16] = {
{
	{14,  4, 13,  1,  2, 15, 11,  8,  3, 10,  6, 12,  5,  9,  0,  7}, 
	{ 0, 15,  7,  4, 14,  2, 13,  1, 10,  6, 12, 11,  9,  5,  3,  8}, 
	{ 4,  1, 14,  8, 13,  6,  2, 11, 15, 12,  9,  7,  3, 10,  5,  0}, 
	{15, 12,  8,  2,  4,  9,  1,  7,  5, 11,  3, 14, 10,  0,  6, 13}
}, 
{
	{15,  1,  8, 14,  6, 11,  3,  4,  9,  7,  2, 13, 12,  0,  5, 10}, 
    { 3, 13,  4,  7, 15,  2,  8, 14, 12,  0,  1, 10,  6,  9, 11,  5}, 
    { 0, 14,  7, 11, 10,  4, 13,  1,  5,  8, 12,  6,  9,  3,  2, 15}, 
    {13,  8, 10,  1,  3, 15,  4,  2, 11,  6,  7, 12,  0,  5, 14,  9}
}, 
{
	{10,  0,  9, 14,  6,  3, 15,  5,  1, 13, 12,  7, 11,  4,  2,  8}, 
	{13,  7,  0,  9,  3,  4,  6, 10,  2,  8,  5, 14, 12, 11, 15,  1}, 
	{13,  6,  4,  9,  8, 15,  3,  0, 11,  1,  2, 12,  5, 10, 14,  7}, 
	{ 1, 10, 13,  0,  6,  9,  8,  7,  4, 15, 14,  3, 11,  5,  2, 12}
}, 
{
	{ 7, 13, 14,  3,  0,  6,  9, 10,  1,  2,  8,  5, 11, 12,  4, 15}, 
	{13,  8, 11,  5,  6, 15,  0,  3,  4,  7,  2, 12,  1, 10, 14,  9}, 
	{10,  6,  9,  0, 12, 11,  7, 13, 15,  1,  3, 14,  5,  2,  8,  4}, 
	{ 3, 15,  0,  6, 10,  1, 13,  8,  9,  4,  5, 11, 12,  7,  2, 14}
}, 
{
	{ 2, 12,  4,  1,  7, 10, 11,  6,  8,  5,  3, 15, 13,  0, 14,  9}, 
	{14, 11,  2, 12,  4,  7, 13,  1,  5,  0, 15, 10,  3,  9,  8,  6}, 
	{ 4,  2,  1, 11, 10, 13,  7,  8, 15,  9, 12,  5,  6,  3,  0, 14}, 
	{11,  8, 12,  7,  1, 14,  2, 13,  6, 15,  0,  9, 10,  4,  5,  3}
}, 
{
	{12,  1, 10, 15,  9,  2,  6,  8,  0, 13,  3,  4, 14,  7,  5, 11}, 
	{10, 15,  4,  2,  7, 12,  9,  5,  6,  1, 13, 14,  0, 11,  3,  8}, 
	{ 9, 14, 15,  5,  2,  8, 12,  3,  7,  0,  4, 10,  1, 13, 11,  6}, 
	{ 4,  3,  2, 12,  9,  5, 15, 10, 11, 14,  1,  7,  6,  0,  8, 13}
}, 
{
	{ 4, 11,  2, 14, 15,  0,  8, 13,  3, 12,  9,  7,  5, 10,  6,  1}, 
	{13,  0, 11,  7,  4,  9,  1, 10, 14,  3,  5, 12,  2, 15,  8,  6}, 
	{ 1,  4, 11, 13, 12,  3,  7, 14, 10, 15,  6,  8,  0,  5,  9,  2}, 
	{ 6, 11, 13,  8,  1,  4, 10,  7,  9,  5,  0, 15, 14,  2,  3, 12}
}, 
{
	{13,  2,  8,  4,  6, 15, 11,  1, 10,  9,  3, 14,  5,  0, 12,  7}, 
	{ 1, 15, 13,  8, 10,  3,  7,  4, 12,  5,  6, 11,  0, 14,  9,  2}, 
	{ 7, 11,  4,  1,  9, 12, 14,  2,  0,  6, 10, 13, 15,  3,  5,  8}, 
	{ 2,  1, 14,  7,  4, 10,  8, 13, 15, 12,  9,  0,  3,  5,  6, 11}
}};
static int Box_P[32] = {
	16,  7, 20, 21, 
	29, 12, 28, 17, 
	1, 15, 23, 26, 
	5, 18, 31, 10, 
	2,  8, 24, 14, 
	32, 27,  3,  9, 
	19, 13, 30,  6, 
	22, 11,  4, 25
};
static int reverse_IP[64] = {
	40,  8, 48, 16, 56, 24, 64, 32, 
	39,  7, 47, 15, 55, 23, 63, 31, 
	38,  6, 46, 14, 54, 22, 62, 30, 
	37,  5, 45, 13, 53, 21, 61, 29, 
	36,  4, 44, 12, 52, 20, 60, 28, 
	35,  3, 43, 11, 51, 19, 59, 27, 
	34,  2, 42, 10, 50, 18, 58, 26, 
	33,  1, 41,  9, 49, 17, 57, 25
};
unsigned char exp_in[64], exp_out[64], exp_key[64];
unsigned char K[16][48];

inline void givekeys(){
	unsigned char C[28], D[28];
	for(int i = 0; i < 28; i++){
		C[i] = exp_key[Box_1C[i] - 1];
		D[i] = exp_key[Box_1D[i] - 1];
	}
	int start = 0;
	for(int i = 0; i < 16; i++){
		start += shiftnumber[i];
		for(int j = 0; j < 48; j++){
			if(Box_2[j] <= 28)K[i][j] = C[((start + Box_2[j] - 1) % 28)];
			else K[i][j] = D[((Box_2[j] + start - 29) % 28)];
		}
	}
}

inline void f(unsigned char* R, unsigned char* K, unsigned char* tmp){
	unsigned char ra[48];
	unsigned char r[32];
	int a, t;
	for(int i = 0; i < 48; ++i){
		ra[i] = R[Box_E[i] - 1];
		ra[i] ^= K[i];
	}
	for(int i = 0; i < 48; i += 6){
		a = i / 6;
		t = Box_S[a][(ra[i] << 1) + ra[i+5]][(ra[i+1] << 3) + (ra[i+2] << 2) + (ra[i+3] << 1) + ra[i+4]];
		for(int j = 0; j < 4; j++){
			r[(a << 2) + j] = (t >> (3-j)) & 1;
		}
	}
	for(int i = 0; i < 32; i++){
		tmp[i] = r[Box_P[i] - 1];
	}
}

inline void des_encrypt(unsigned char* in, unsigned char* out){
	unsigned char tmp[64];
	unsigned char L[17][32];
	unsigned char R[17][32];
	unsigned char ft[32];
	for(int i = 0; i < 8; ++i){
		for(int j = 0; j < 8; ++j){
			exp_in[(i << 3) + j] = (in[i] >> (7-j)) & 1;
		}
	}
	for(int i = 0; i < 64; ++i){
		tmp[i] = exp_in[IP[i] - 1];
	}
	memcpy(L[0], tmp, 32);
	memcpy(R[0], tmp+32, 32);
	for(int i = 1; i <= 16; ++i){
		memcpy(L[i], R[i-1], 32);
		f(R[i-1], K[i-1], ft);
		for(int j = 0; j < 32; ++j){
			R[i][j] = L[i-1][j] ^ ft[j];
		}
	}
	memcpy(tmp, R[16], 32);
	memcpy(tmp+32, L[16], 32);
	for(int i = 0; i < 64; ++i){
		exp_out[i] = tmp[reverse_IP[i] - 1];
	}
	for(int i = 0; i < 8; ++i){
		for(int j = 0; j < 8; ++j){
			out[i] |= ((exp_out[(i << 3)+j] & 1) << (7-j));
		}
	}
}

inline void des_decrypt(unsigned char* in, unsigned char* out){
	unsigned char tmp[64];
	unsigned char L[17][32];
	unsigned char R[17][32];
	unsigned char ft[32];
	for(int i = 0; i < 8; ++i){
		for(int j = 0; j < 8; ++j){
			exp_in[(i << 3) + j] = (in[i] >> (7-j)) & 1;
		}
	}
	for(int i = 0; i < 64; ++i){
		tmp[i] = exp_in[IP[i] - 1];
	}
	memcpy(R[16], tmp, 32);
	memcpy(L[16], tmp+32, 32);
	for(int i = 16; i >= 1; i--){
		f(L[i], K[i-1], ft);
		for(int j = 0; j < 32; ++j){
			L[i-1][j] = R[i][j] ^ ft[j];
		}
		memcpy(R[i-1], L[i], 32);
	}
	memcpy(tmp, L[0], 32);
	memcpy(tmp+32, R[0], 32);
	for(int i = 0; i < 64; ++i){
		exp_out[i] = tmp[reverse_IP[i] - 1];
	}
	for(int i = 0; i < 8; ++i){
		for(int j = 0; j < 8; ++j){
			out[i] |= ((exp_out[(i << 3)+j] & 1) << (7-j));
		}
	}
}
int main(){
	/*
	unsigned char in[16] = {'c','h', 'e', 'n', 'g', 'y', 'u', 'a', '1','7', '2', '0','1','7','0','1'};
	unsigned char IV[8] = {'a','a','a','a','a','a','a','a'};
	unsigned char out[16];
	unsigned char dec[16];
	unsigned char key[8] = {'a','b','c','d','e','f','g','h'};

	memset(out, 0, 16);
	memset(dec, 0, 16);

	for(int i = 0; i < 8; i++){
		for(int j = 0; j < 8; j++){
			exp_key[(i << 3) + j] = (key[i] >> (7-j)) & 1;
		}
	}
	givekeys();
	
	for(int i = 0; i < 8; i++){
		in[i] ^= IV[i];
	}
	des_encrypt(in, out);
	printf("des_encrypt\n");
	for(int i = 0; i < 8; i++){
		printf("%02x", out[i]);
		in[i+8] ^= out[i];
	}
	des_encrypt(in+8, out+8);
	for(int i = 0; i < 8; i++){
		printf("%02x", out[i+8]);
	}
	printf("\n");
	des_decrypt(out, dec);
	printf("des_decrypt\n");
	for(int i = 0; i < 8; i++){
		printf("%c", dec[i] ^ IV[i]);
	}
	des_decrypt(out+8, dec+8);
	for(int i = 0; i < 8; i++){
		printf("%c", dec[i+8] ^ out[i]);
	}
	printf("\n");
	*/
	FILE *fpout = NULL;
	FILE *fpout2 = NULL;
	fpout = fopen("output_DES.txt", "w+");
	fpout2 = fopen("decrypt_DES.txt", "w+");
	unsigned char in[2048];
	unsigned char IV[8];
	unsigned char out[2048] = {0};
	unsigned char dec[2048] = {0};
	unsigned char key[8];
	for(int i = 0; i < 2048; i++){
		in[i] = rand() % 256;
	}
	for(int i = 0; i < 8; i++){
		key[i] = rand() % 256;
		IV[i] = rand() % 256;
	}
	for(int i = 0; i < 8; i++){
		for(int j = 0; j < 8; j++){
			exp_key[(i << 3) + j] = (key[i] >> (7-j)) & 1;
		}
	}
	givekeys();
//	clock_t start, end;
//	double total;
//	start = clock();
//	for(int k = 0 ; k < 6400; k++){
	for(int i = 0; i < 256; i++){
		if(i == 0){
			for(int j = 0; j < 8; j++){
				in[j] ^= IV[j];
			}
			des_encrypt(in, out);
		}
		else{
			for(int j = 0; j < 8; j++){
				in[(i << 3)+j] ^= out[((i-1) << 3)+j];
			}
			des_encrypt(in+(i << 3), out+(i << 3));
		}
	}
//}
//	end = clock();
//	total = (double)(end - start);
//	cout << "The run time is: " << 1000 * total / CLOCKS_PER_SEC << "ms" << endl;
	for(int i = 0; i < 2048; i++){
		fprintf(fpout, "%02x", out[i]);
	}
	for(int i = 0; i < 256; i++){
		if(i == 0){
			des_decrypt(out, dec);
			for(int j = 0; j < 8; j++){
				dec[j] ^= IV[j];
			}
		}
		else{
			des_decrypt(out+8*i, dec+8*i);
			for(int j = 0; j < 8; j++){
				dec[i*8+j] ^= out[(i-1)*8+j];
			}
		}
	}
	for(int i = 0; i < 2048; i++){
		fprintf(fpout2, "%02x", dec[i]);
	}
	return 0;
}