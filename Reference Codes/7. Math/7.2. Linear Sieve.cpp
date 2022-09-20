// BOJ 16563 AC Code
// https://www.acmicpc.net/problem/16563
#include <bits/stdc++.h>
using namespace std;
#define ll long long

const int MAXN = 5000000;

vector<int> sp(MAXN + 1);
vector<ll> prime;

// Determine prime numbers between 1 and MAXN in O(MAXN) 
void linearSieve() {
	for (int i = 2;i <= MAXN; i++) {
		if (!sp[i]) {
			prime.push_back(i);
			sp[i] = i;
		}
		for (auto j : prime) {
			if (i * j > MAXN) break;
			sp[i * j] = j;
			if (i % j == 0) break;
		}
	}
}

// factorization in O(log x)
void factorization(int x) {
	while (x > 1) {
		cout << sp[x] << ' ';
		x /= sp[x];
	}
	cout << '\n';
}

int main() {
	cin.tie(NULL); cout.tie(NULL);
	ios_base::sync_with_stdio(false);

	linearSieve();

	int n; cin >> n;
	while (n--) {
		int x; cin >> x;
		factorization(x);
	}

	return 0;
}