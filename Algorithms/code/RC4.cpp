#include <bits/stdc++.h>
using namespace std;

unsigned char S[256];
unsigned char T[256];
unsigned char keystream[2048];

void RC4_encrypt(unsigned char* txt, unsigned char* out, unsigned char* k, int len, int keylen){
	int i, t, j = 0, m = 0;
	unsigned char tmp;
	for(i = 0; i < 256; i++){
		S[i] = i;
		T[i] = k[i % keylen];
	} 
	for(i = 0; i < 256; i++){
		j = (j + S[i] + T[i]) % 256;
		tmp = S[j];
		S[j] = S[i];
		S[i] = tmp;
	}
	i = 0, j = 0;
	for(m = 0; m < len; m++){
		i = (i + 1) % 256;
		j = (j + S[i]) % 256;
		tmp = S[i];
		S[i] = S[j];
		S[j] = tmp;
		t = (S[i] + S[j]) % 256;
		keystream[m] = S[t];
		out[m] = S[t] ^ txt[m];
	}
}

int main(){
	/*
	unsigned char text[1000] = {'c','h','e','n','g','y','u','a','1','7','2','0','1','7','0','1','1','4','2','9'};
	unsigned char out[1000];
	unsigned char key[6] = {'c', 'i', 'p', 'h','e','r'};
	RC4_encrypt(text, out, key, 20, 6);
	for(int i = 0 ; i < 20; i++){
		printf("%02x", out[i]);
	}*/
	FILE *fpout = NULL;
	fpout = fopen("output_rc4.txt", "w+");
	unsigned char text[2048];
	unsigned char out[2048];
	unsigned char initkey[128];
	for(int i = 0 ; i < 2048; i++){
		text[i] = rand() % 256;
	}
	for(int i = 0; i < 128; i++){
		initkey[i] = rand() % 256;
		printf("%02x", initkey[i]);
	}
//	clock_t start, end;
//	double total;
//	start = clock();
//	for(int i = 0; i < 6400; i++){
		RC4_encrypt(text, out, initkey, 2048, 128);
//	}
//	end = clock();
//	total = (double)(end - start);
//	cout << "The run time is: " << 1000 * total / CLOCKS_PER_SEC << "ms" << endl;
	for(int i = 0; i < 2048; i++){
		fprintf(fpout, "%02x", out[i]);
	}
	return 0;	
}