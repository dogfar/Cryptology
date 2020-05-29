#include <bits/stdc++.h>
using namespace std;

int a[200],c[200][200],l[200],d[200];

void dobm(int N){
	c[0][0] = 1;
	l[0] = 0;
	for(int i = 0; i < N; i++){
		d[i] = 0;
		for(int j = 0; j <= l[i]; j++){
			d[i] ^= c[i][j] & a[i-j];
		}
		if(d[i] == 0){
			l[i+1] = l[i];
			for(int j = 0; j < N; j++){
				c[i+1][j] = c[i][j];
			}
		}
		else{
			int id = -1;
			for(int j = i-1; j >= 0; j--){
				if(l[j] < l[j+1]){
					id = j;
					break;
				}
			}
			if(id == -1){
				c[i+1][0] = 1;
				c[i+1][i+1] = 1;
				l[i+1] = i+1;
			}
			else{
				for(int j = 0; j < N; j++){
					c[i+1][j] = c[i][j];
				}
				for(int j = 0; j < N; j++){
					c[i+1][(i-id)+j] = (c[id][j] + c[i+1][i-id+j]) % 2;
				}
				l[i+1] = max(l[i], i+1 - l[i]);
			}
		}
	}
}

string itoa(int t){
	string ans = "";
	if(t == 0)return "0";
	while(t > 0){
		ans += (t % 10) + '0';
		t /= 10;
	}
	reverse(ans.begin(), ans.end());
	return ans;
}

int main(){
	
	int N;
	cin >> N;
	for(int i = 0; i < N; i++)cin >> a[i];
	memset(c, 0 ,sizeof(c));
	memset(l ,0 , sizeof(l));
	memset(d, 0 , sizeof(d));
	dobm(N);
	string ans;
	if(c[N][0] != 0)ans += "1+";
	for(int i = 1; i < N; i++){
		if(c[N][i] != 0){
			ans +=  "x^";
			ans += itoa(i);
			ans += "+";
		}
	}
	if(ans[ans.length()-1] == '+'){
		ans[ans.length()-1] = '\n';
	}
	cout << ans << endl;
	cout << l[N] << endl;
/*
	int N = 10;
	for(int i = 0; i < 10; i++){
		a[i] = rand() % 2;
	}
	clock_t start, end;
	double total;
	for(int i = 0; i < 100000; i++){
		memset(c, 0 ,sizeof(c));
		memset(l ,0 , sizeof(l));
		memset(d, 0 , sizeof(d));
		start = clock();
		dobm(N);
		end = clock();
		total += (double)(end - start);
	}
	cout << "The run time is: " << 1000 * total / CLOCKS_PER_SEC << "ms" << endl;*/
	return 0;
}