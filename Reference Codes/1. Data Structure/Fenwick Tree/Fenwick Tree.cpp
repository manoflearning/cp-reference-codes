// INPUT: Given an array of integers of size N.
// Given the query (a b c)
// If a = 1, change the value of the bth element to c,
// If a = 2, find the sum of the elements in the interval [b, c].
// OUTPUT: Given the query (2 b c), output the sum of elements in the interval [b, c].
// TIME COMPLEXITY: O(n) for initialize fenwick tree, O(logn) for each query,
// O(logn) for find the kth smallest number.

// BOJ 2042 AC Code
// https://www.acmicpc.net/problem/2042

#include <bits/stdc++.h>
using namespace std;
#define ll long long

struct Fenwick { // 0-indexed
	int flag, cnt; // array size
	vector<ll> arr, t;
	void build(int n) {
		for (flag = 1; flag < n; flag <<= 1, cnt++);
		arr.resize(flag);
		t.resize(flag);
		for (int i = 0; i < n; i++) cin >> arr[i];
		for (int i = 0; i < n; i++) {
			t[i] += arr[i];
			if (i | (i + 1) < flag) t[i | (i + 1)] += t[i];
		}
	}
	void add(int p, ll value) { // add value at position p
		arr[p] += value;
		while (p < flag) {
			t[p] += value;
			p |= p + 1;
		}
	}
	void modify(int p, ll value) { // set value at position p
		add(p, value - arr[p]);
	};
	ll query(int x) {
		ll ret = 0;
		while (x >= 0) ret += t[x], x = (x & (x + 1)) - 1;
		return ret;
	}
	ll query(int l, int r) {
		return query(r) - (l ? query(l - 1) : 0);
	}
	int kth(int k) { // find the kth smallest number (1-indexed)
		assert(t.back() >= k);
		int l = 0, r = arr.size();
		for (int i = 0; i <= cnt; i++) {
			int mid = (l + r) >> 1;
			ll val = mid ? t[mid - 1] : t.back();
			if (val >= k) r = mid;
			else l = mid, k -= val;
		}
		return l;
	}
}fw;

int main() {
	cin.tie(NULL); cout.tie(NULL);
	ios_base::sync_with_stdio(false);

	int n, m, k;
	cin >> n >> m >> k;

	fw.build(n);

	for (int i = 0; i < m + k; i++) {
		ll op, x, y;
		cin >> op >> x >> y;
		if (op == 1) fw.modify(x - 1, y);
		if (op == 2) cout << fw.query(x - 1, y - 1) << '\n';
	}
}