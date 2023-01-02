// INPUT: Given a directed graph.
// OUTPUT: Output one of the topological sorting results of the graph.
// TIME COMPLEXITY: O(n + m)

// BOJ 2252 AC Code
// https://www.acmicpc.net/problem/2252

#include <bits/stdc++.h>
using namespace std;

const int MAX = 101010;

int n, m;
vector<int> adj[MAX], stk;
int vi[MAX], fi[MAX], isCycle;

void input() {
	cin >> n >> m;
	for (int i = 0; i < m; i++) {
		int u, v;
		cin >> u >> v;
		adj[u].push_back(v);
	}
}

void dfs(int v) {
	vi[v] = 1;
	for (int next : adj[v]) {
		if (!vi[next]) dfs(next);
		else if (!fi[next]) isCycle = 1;
	}
	fi[v] = 1;
	stk.push_back(v);
}

void topologicalSort() {
	for (int i = 1; i <= n; i++) {
		if (!vi[i]) dfs(i);
	}
	if (isCycle) cout << 0;
	else {
		for (int i = stk.size() - 1; i >= 0; i--) 
			cout << stk[i] << ' ';
	}
}

int main() {
	cin.tie(NULL); cout.tie(NULL);
	ios_base::sync_with_stdio(false);

	input();
	topologicalSort();

	return 0;
}