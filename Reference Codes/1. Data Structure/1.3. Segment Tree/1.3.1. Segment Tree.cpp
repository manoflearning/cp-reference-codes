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

int flag;  // array size
struct Seg {  // 1-indexed
	vector<ll> t;
	void build(int n) {
		for (flag = 1; flag < n; flag <<= 1);
		t.resize(2 * flag);
		for (int i = flag; i < flag + n; i++) cin >> t[i];
		for (int i = flag - 1; i >= 1; i--) t[i] = t[i << 1] + t[i << 1 | 1];
	}
	void modify(int p, ll value) {  // set value at position p
		for (t[p += flag - 1] = value; p > 1; p >>= 1) t[p >> 1] = t[p] + t[p ^ 1];
	}
	ll query(int l, int r, int n = 1, int nl = 1, int nr = flag) {  // sum on interval [l, r]
		if (r < nl || nr < l) return 0;
		if (l <= nl && nr <= r) return t[n];
		int mid = (nl + nr) / 2;
		return query(l, r, n << 1, nl, mid) + query(l, r, n << 1 | 1, mid + 1, nr);
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
		if (op == 1) seg.modify(x, y);
		if (op == 2) cout << seg.query(x, y) << '\n';
	}

	return 0;
}