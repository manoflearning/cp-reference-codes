// INPUT: Given a tree with n vertices. Given a Q query (u, v).
// OUTPUT: For each query (u, v), print the LCA of u and v.
// TIME COMPLEXITY: O(nlogn) for build sparse table, O(logn) for each query.

// BOJ 11438 AC Code
// https://www.acmicpc.net/problem/11438

#include <bits/stdc++.h>
using namespace std;

const int MAX = 101010, MAXD = 16;  // 2^MAXD = 65536

vector<int> adj[MAX];
int n, dep[MAX], par[MAX][MAXD + 1];

void input() {
	cin >> n;
	for (int i = 0; i < n - 1; i++) {
		int u, v;
		cin >> u >> v;
		adj[u].push_back(v);
		adj[v].push_back(u);
	}
}

void dfs(int now, int prv) {
	par[now][0] = prv;
	dep[now] = dep[prv] + 1;
	for (auto i : adj[now]) {
		if (i == prv) continue;
		dfs(i, now);
	}
}

void buildSparseTable() {
	for (int i = 1; i <= MAXD; i++) {
		for (int v = 1; v <= n; v++) {
			par[v][i] = par[par[v][i - 1]][i - 1];
		}
	}
}

int lca(int u, int v) {
	if (dep[u] < dep[v]) swap(u, v);
	int diff = dep[u] - dep[v];
	for (int i = MAXD; i >= 0; i--)
		if (diff & (1 << i)) u = par[u][i];
	if (u == v) return u;
	for (int i = MAXD; i >= 0; i--) {
		if (par[u][i] ^ par[v][i]) {
			u = par[u][i];
			v = par[v][i];
		}
	}
	return par[u][0];
}

int main() {
	cin.tie(NULL); cout.tie(NULL);
	ios_base::sync_with_stdio(false);

	input();
	dfs(1, 0);
	buildSparseTable();
	
	int Q; cin >> Q;
	while (Q--) {
		int u, v;
		cin >> u >> v;
		cout << lca(u, v) << '\n';
	}
}