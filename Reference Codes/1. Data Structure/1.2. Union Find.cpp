// BOJ 1717 AC Code
// https://www.acmicpc.net/problem/1717
#include <bits/stdc++.h>
using namespace std;

const int MAX = 1010101;

int n;
vector<int> p(MAX, -1);

int find(int x) {
	if (p[x] < 0) return x;
	return p[x] = find(p[x]);
}

void merge(int a, int b) {
	int A = find(a), B = find(b);
	if (A == B) return;
	p[A] += p[B];
	p[B] = A;
}

int main() {
	cin.tie(NULL); cout.tie(NULL);
	ios_base::sync_with_stdio(false);

	cin >> n;

	int q; cin >> q;
	while (q--) {
		int op, u, v;
		cin >> op >> u >> v;

		if (op == 0) merge(u, v);
		if (op == 1) {
			if (find(u) == find(v)) cout << "YES\n";
			else cout << "NO\n";
		}
	}

	return 0;
}
