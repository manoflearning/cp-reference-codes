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