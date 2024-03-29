// 1. Euler Tour Technique (LCA)
// INPUT: Given a tree with N nodes. Given M queries of the form (u, v).
// OUTPUT: For each query, print lca(u, v).
// TIME COMPLEXITY: O(N) for initialize, O(logN) for each query.

// BOJ 11438 AC Code
// https://www.acmicpc.net/problem/11438

#include <bits/stdc++.h>
using namespace std;
#define ll long long

int arr[202020], dep[101010];

int flag;  // array size
struct Seg {  // 1-indexed
	vector<pair<int, int>> t;
	void build(int N) {
		for (flag = 1; flag < N; flag <<= 1);
		t.resize(flag << 1);
		for (int i = flag; i < flag + N; i++) {
			int v = arr[i - flag + 1];
			t[i] = { dep[v], v };
		}
		for (int i = flag - 1; i >= 1; i--) 
			t[i] = min(t[i << 1], t[i << 1 | 1]);
	}
	pair<int, int> query(int l, int r, int n = 1, int nl = 1, int nr = flag) {
		if (r < nl || nr < l) return { 1e9, 1e9 };
		if (l <= nl && nr <= r) return t[n];
		int mid = (nl + nr) / 2;
		return min(query(l, r, n << 1, nl, mid), query(l, r, n << 1 | 1, mid + 1, nr));
	}
}seg;

int n, loc[101010], cnt = 1;
vector<int> adj[101010];

void dfs(int v, int prv) {
	loc[v] = cnt;
	arr[cnt++] = v;
	for (auto& i : adj[v]) {
		if (i == prv) continue;
		dep[i] = dep[v] + 1;
		dfs(i, v);
		arr[cnt++] = v;
	}
}

int main() {
	cin.tie(NULL); cout.tie(NULL);
	ios_base::sync_with_stdio(false);

	cin >> n;
	for (int i = 0; i < n - 1; i++) {
		int u, v;
		cin >> u >> v;
		adj[u].push_back(v);
		adj[v].push_back(u);
	}

	dfs(1, 0);

	seg.build(2 * n - 1);

	int m; cin >> m;
	for (int i = 0; i < m; i++) {
		int u, v;
		cin >> u >> v;
		if (loc[u] > loc[v]) swap(u, v);
		cout << seg.query(loc[u], loc[v]).second << '\n';
	}
}

// Euler Tour Technique (Sum of Subtree)
// INPUT: Given a tree with N nodes. Given a value on each nodes. 
// Given M queries of the form (p x y) or (u x).
// If the query is (p x y), add y to all nodes in the subtree of node x (except x).
// If the query is (u x), find the value of node x.
// OUTPUT: For each query of the form (u x), print the value of node x.
// TIME COMPLEXITY: O(N) for initialize, O(logN) for each query.

// BOJ 2820 AC Code
// https://www.acmicpc.net/problem/2820

#include <bits/stdc++.h>
using namespace std;
#define ll long long

int a[505050], in[505050], out[505050];

int flag;  // array size
struct Seg {  // 1-indexed
	vector<ll> t, lazy;
	void build(int n) {
		for (flag = 1; flag < n; flag <<= 1);
		t.resize(2 * flag);
		lazy.resize(2 * flag);
        for (int v = 1; v <= n; v++) {
            t[in[v] + flag - 1] = a[v];
        }
		for (int i = flag - 1; i >= 1; i--) t[i] = t[i << 1] + t[i << 1 | 1];
	}
	// add a value to all elements in interval [l, r]
	void modify(int l, int r, ll value, int n = 1, int nl = 1, int nr = flag) {
		propagate(n, nl, nr);
		if (r < nl || nr < l) return;
		if (l <= nl && nr <= r) {
			lazy[n] += value;
			propagate(n, nl, nr);
			return;
		}
		int mid = (nl + nr) >> 1;
		modify(l, r, value, n << 1, nl, mid);
		modify(l, r, value, n << 1 | 1, mid + 1, nr);
		t[n] = t[n << 1] + t[n << 1 | 1];
	}
	ll query(int l, int r, int n = 1, int nl = 1, int nr = flag) {  // sum on interval [l, r]
		propagate(n, nl, nr);
		if (r < nl || nr < l) return 0;
		if (l <= nl && nr <= r) return t[n];
		int mid = (nl + nr) / 2;
		return query(l, r, n << 1, nl, mid) + query(l, r, n << 1 | 1, mid + 1, nr);
	}
	void propagate(int n, int nl, int nr) {
		if (lazy[n] != 0) {
			if (n < flag) {
				lazy[n << 1] += lazy[n];
				lazy[n << 1 | 1] += lazy[n];
			}
			t[n] += lazy[n] * (nr - nl + 1);
			lazy[n] = 0;
		}
	}
}seg;

int n, m, cnt;
vector<int> adj[505050];

void dfs(int v, int prv) {
	in[v] = ++cnt;
	for (auto& i : adj[v]) {
		if (i != prv) dfs(i, v);
	}
	out[v] = cnt;
}

int main() {
	cin.tie(NULL); cout.tie(NULL);
	ios_base::sync_with_stdio(false);

	cin >> n >> m;
	for (int v = 1; v <= n; v++) {
		cin >> a[v];
		if (v == 1) continue;
		int u; cin >> u;
		adj[v].push_back(u);
		adj[u].push_back(v);
	}

	dfs(1, 0);

	seg.build(cnt);

	for (int i = 0; i < m; i++) {
		char op; 
		int x, y;
		cin >> op >> x;
		if (op == 'p') {
			cin >> y;
			seg.modify(in[x] + 1, out[x], y);
		}
		if (op == 'u')
			cout << seg.query(in[x], in[x]) << '\n';
	}
}