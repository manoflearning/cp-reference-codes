#include <iostream>
#include <vector>
using namespace std;
#define ll long long

struct Seg {
	int flag;  // array size
	vector<ll> t, lazy;

	void build(int N) {
		for (flag = 1; flag < N; flag <<= 1);
		t.resize(2 * flag);
		lazy.resize(2 * flag);

		for (int i = flag; i < flag + N; i++) cin >> t[i];
		for (int i = flag - 1; i >= 1; i--) t[i] = t[i << 1] + t[i << 1 | 1];
	}
	void modify(int L, int R, int value) {
		return modify(L, R, 1, 1, flag, value);
	}
	// add a value to all elements in interval [L, R]
	void modify(int L, int R, int n, int nL, int nR, int value) {
		propagate(n, nL, nR);

		if (R < nL || nR < L) return;
		if (L <= nL && nR <= R) {
			lazy[n] += value;
			propagate(n, nL, nR);
			return;
		}

		int mid = (nL + nR) / 2;
		modify(L, R, n << 1, nL, mid, value);
		modify(L, R, n << 1 | 1, mid + 1, nR, value);

		t[n] = t[n << 1] + t[n << 1 | 1];
	}
	ll query(int L, int R) {
		return query(L, R, 1, 1, flag);
	}
	ll query(int L, int R, int n, int nL, int nR) {  // sum on interval [L, R]
		propagate(n, nL, nR);

		if (R < nL || nR < L) return 0;
		if (L <= nL && nR <= R) return t[n];

		int mid = (nL + nR) / 2;
		return query(L, R, n << 1, nL, mid) + query(L, R, n << 1 | 1, mid + 1, nR);
	}
	void propagate(int n, int nL, int nR) {
		if (lazy[n] != 0) {
			if (n < flag) {
				lazy[n << 1] += lazy[n];
				lazy[n << 1 | 1] += lazy[n];
			}
			t[n] += lazy[n] * (nR - nL + 1);
			lazy[n] = 0;
		}
	}
}seg;

int main() {
	cin.tie(NULL); cout.tie(NULL);
	ios_base::sync_with_stdio(false);

	int N; cin >> N;

	seg.build(N);

	seg.modify(1, 1, 1);
	cout << seg.query(3, 11) << '\n';

	return 0;
}
