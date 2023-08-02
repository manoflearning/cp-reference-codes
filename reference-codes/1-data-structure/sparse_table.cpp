// INPUT: Given a function f: { 1, 2, ..., m } -> { 1, 2, ..., m }.
// The function f is defined as f_1(x) = f(x), f_{n+1}(x) = f(f_n(x)).
// OUTPUT: Given n and x, print f_n(x).
// TIME COMPLEXITY: O(mlogn) for build sparse table, O(logn) for each query.

// BOJ 17435 AC Code
// https://www.acmicpc.net/problem/17435

#include <bits/stdc++.h>
using namespace std;

const int MAX = 202020, MAXD = 18;

int m, sp[MAX][MAXD + 1];

int main() {
	cin.tie(NULL); cout.tie(NULL);
	ios_base::sync_with_stdio(false);

	// input
	cin >> m;
	for (int i = 1; i <= m; i++) cin >> sp[i][0];

	// build sparse table
	for (int i = 1; i <= MAXD; i++) {
		for (int j = 1; j <= m; j++) {
			sp[j][i] = sp[sp[j][i - 1]][i - 1];
		}
	}

	// query
	int q; cin >> q;
	while (q--) {
		int n, x;
		cin >> n >> x;
		for (int i = MAXD; i >= 0; i--) {
			if (n & (1 << i)) x = sp[x][i];
		}
		cout << x << '\n';
	}

	return 0;
}