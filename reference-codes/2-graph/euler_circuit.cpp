// Hierholzer's Algorithm
// INPUT: Given a undirected graph.
// OUTPUT: Print the path of the Euler circuit of the graph.
// Euler Path is a path in a finite graph that visits every edge exactly once.
// Similarly, an Euler Circuit is an Euler Path that starts and ends on the same vertex.
// TIME COMPLEXITY: O(VE)

// BOJ 1199 AC Code
// https://www.acmicpc.net/problem/1199

#include <bits/stdc++.h>
using namespace std;

const int MAXV = 1010;

int n, adj[MAXV][MAXV], nxt[MAXV];
vector<int> eulerCircult;

void input() {
	cin >> n;
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			cin >> adj[i][j];
		}
	}
}

int doesEulerCircuitExist() {
	// If the degree of all nodes in the graph is even, then an euler circuit exists.
	// Otherwise, the euler circuit does not exist.
	// We can do similar way to determine the existence of euler path. 
	// If only two vertices have odd degree, than an eular path exists. Otherwise, the euler path does not exist.
	for (int i = 1; i <= n; i++) {
		int deg = 0;
		for (int j = 1; j <= n; j++) {
			deg += adj[i][j];
		}
		if (deg & 1) return 0;
	}
	return 1;
}

void dfs(int now) {
	for (int& x = nxt[now]; x <= n; x++) {
		while (x <= n && adj[now][x]) {
			adj[now][x]--;
			adj[x][now]--;
			dfs(x);
		}
	}
	eulerCircult.push_back(now);
}

int main() {
	cin.tie(NULL); cout.tie(NULL);
	ios_base::sync_with_stdio(false);

	input();
	
	if (!doesEulerCircuitExist()) {
		cout << -1;
		return 0;
	}

	for (int i = 1; i <= n; i++) nxt[i] = 1;
	dfs(1);
	for (auto i : eulerCircult) 
		cout << i << ' ';
}