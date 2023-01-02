// INPUT: Given an array of integers of size N.
// Given the query (a b c)
// If a = 1, change the value of the bth element to c,
// If a = 2, find the sum of the elements in the interval [b, c].
// OUTPUT: Given the query (2 b c), output the sum of elements in the interval [b, c].
// TIME COMPLEXITY: O(n) for initialize segment tree, O(logn) for each query.

// BOJ 2042 AC Code
// https://www.acmicpc.net/problem/2042

#include <bits/stdc++.h>
using namespace std;
#define ll long long

const int MAXN = 1010101;  // limit for array size

struct Seg {  // 0-indexed
	int n;  // array size
	ll t[2 * MAXN];
	void build(int N) {
		n = N;
		for (int i = 0; i < n; i++) cin >> t[n + i];
		for (int i = n - 1; i >= 1; i--) t[i] = t[i << 1] + t[i << 1 | 1];
	}
	void modify(int p, ll value) {  // set value at position p
		for (t[p += n] = value; p > 1; p >>= 1) t[p >> 1] = t[p] + t[p ^ 1];
	}
	ll query(int l, int r) {  // sum on interval [l, r)
		ll ret = 0;
		for (l += n, r += n; l < r; l >>= 1, r >>= 1) {
			if (l & 1) ret += t[l++];
			if (r & 1) ret += t[--r];
		}
		return ret;
	}
}seg;

int main() {
	cin.tie(NULL); cout.tie(NULL);
	ios_base::sync_with_stdio(false);

	int n, m, k;
	cin >> n >> m >> k;

	seg.build(n);

	for (int i = 0; i < m + k; i++) {
		ll op, x, y;
		cin >> op >> x >> y;
		if (op == 1) seg.modify(x - 1, y);
		if (op == 2) cout << seg.query(x - 1, y) << '\n';
	}

	return 0;
}