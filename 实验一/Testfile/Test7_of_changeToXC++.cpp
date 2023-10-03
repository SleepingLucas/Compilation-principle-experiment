#include<iostream>
#include<vector>
using namespace std;

const int maxn = 2e5 + 5;
const double PI = 3.141592653;
const float E = 2.71828;

bool isnp[maxn];
vector<int> primes; 
void init(int n) {
    for (int i=2;i<=n;i++) {
        if (!isnp[i]) primes.push_back(i);
        for (int p:primes) {
            if (p * i > n) break;
            isnp[p * i] = 1;
            if (i % p == 0) break;
        }
    }
}

int main() {
	int n;
	cin >> n;
	init(n);
	for (int i=2;i<=n;i++) {
		if (isnp[i]||i>n-2) continue;
		if (!isnp[i]&&!isnp[i+2])
			cout << i << " " << i+2 << endl;
	}
}