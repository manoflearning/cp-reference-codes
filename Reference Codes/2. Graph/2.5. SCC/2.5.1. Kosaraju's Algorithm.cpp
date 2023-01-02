// Kosaraju's Algorithm
// INPUT: Given a directed graph.
// OUTPUT: Decompose this graph into SCCs and print them in lexicographical order.
// TIME COMPLEXITY: O(V + E)

// BOJ 2150 AC Code
// https://www.acmicpc.net/problem/2150

#include <bits/stdc++.h>
using namespace std;
#define sz(x) (int)(x).size()

const int MAXV = 10101;

int n, m;
vector<int> adj[MAXV], radj[MAXV];
int in[MAXV], out[MAXV], num, p[2 * MAXV];
int vi[MAXV], cnt;
vector<vector<int>> scc;

void input() {
	cin >> n >> m;
	for (int i = 0; i < m; i++) {
		int u, v;
		cin >> u >> v;
		adj[u].push_back(v);
		radj[v].push_back(u);
	}
}

void dfs(int v) {
	in[v] = ++num;
	for (auto& i : radj[v]) {
		if (!in[i]) dfs(i);
	}
	out[v] = ++num;
	p[num] = v;
}

void flood(int v) {
	scc[cnt].push_back(v);
	vi[v] = cnt;
	for (auto& i : adj[v]) {
		if (!vi[i]) flood(i);
	}
}

void kosaraju() {
	for (int v = 1; v <= n; v++) {
		if (!in[v]) dfs(v);
	}
	for (int v = 2 * n; v >= 1; v--) {
		if (!p[v]) continue;
		if (vi[p[v]]) continue;
		cnt++;
		scc.resize(cnt + 1);
		flood(p[v]);
	}
}

void print() {
	for (auto& i : scc)
		sort(i.begin(), i.end());
	sort(scc.begin(), scc.end());
	cout << sz(scc) - 1 << '\n';
	for (int i = 1; i < sz(scc); i++) {
		auto& arr = scc[i];
		for (auto& j : arr) cout << j << ' ';
		cout << -1 << '\n';
	}
}

int main() {
	cin.tie(NULL); cout.tie(NULL);
	ios_base::sync_with_stdio(false);
	
	input();
	kosaraju();
	print();
	
	return 0;
}