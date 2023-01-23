// INPUT: Given n+1 sets {0}, {1}, ..., {n}.
// Two types of operations are given. 0 a b is the union operation.
// 1 a b is an operation that checks whether a and b are in the same set.
// OUTPUT: For inputs starting with 1, the result is output as YES/NO.
// TIME COMPLEXITY: O(α(n)) for each operation (α is inverse Ackermann function)

// BOJ 1717 AC Code
// https://www.acmicpc.net/problem/1717

#include <bits/stdc++.h>
using namespace std;

const int MAX = 1010101;

int n;
vector<int> uf(MAX, -1);

int find(int x) {
	if (uf[x] < 0) return x;
	return uf[x] = find(uf[x]);
}

void merge(int a, int b) {
	int A = find(a), B = find(b);
	if (A == B) return;
	uf[A] += uf[B];
	uf[B] = A;
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