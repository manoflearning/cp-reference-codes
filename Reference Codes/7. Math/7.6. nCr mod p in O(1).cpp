// BOJ 13977 AC Code
// https://www.acmicpc.net/problem/13977
#include <bits/stdc++.h>
using namespace std;
#define ll long long

const int MOD = 1e9 + 7;
const int MAXN = 4040404;

ll fac[MAXN], inv[MAXN], facInv[MAXN];

ll binom(int n, int r) {
	return fac[n] * facInv[r] % MOD * facInv[n - r] % MOD;
}

int main() {
	cin.tie(NULL); cout.tie(NULL);
	ios_base::sync_with_stdio(false);

	// Preprocessing in O(N)
	fac[0] = fac[1] = inv[1] = 1;
	facInv[0] = facInv[1] = 1;
	for (int i = 2; i < MAXN; i++) {
		fac[i] = i * fac[i - 1] % MOD;

		inv[i] = -(MOD / i) * inv[MOD % i] % MOD;
		if (inv[i] < 0) inv[i] += MOD;
		facInv[i] = facInv[i - 1] * inv[i] % MOD;
	}

	// Answer each query in O(1)
	int q; cin >> q;
	while (q--) { 
		int n, r;
		cin >> n >> r;

		cout << binom(n, r) << '\n';
	}

	return 0;
}