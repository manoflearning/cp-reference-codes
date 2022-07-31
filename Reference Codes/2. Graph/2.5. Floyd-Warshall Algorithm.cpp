// BOJ 11404 AC Code
// https://www.acmicpc.net/problem/11404
#include <bits/stdc++.h>
using namespace std;
#define ll long long

const ll INF = 1e18;
const int MAXV = 101;

int n, m;
ll adj[MAXV][MAXV];

void init() {
	for (int i = 0; i < MAXV; i++) {
		for (int j = 0; j < MAXV; j++) {
			adj[i][j] = INF;
		}
	}
}

void input() {
	cin >> n >> m;
	for (int i = 0; i < m; i++) {
		int u, v; ll w;
		cin >> u >> v >> w;
		adj[u][v] = min(adj[u][v], w);
	}
}

void floyd() {
	for (int i = 1; i <= n; i++) adj[i][i] = 0;

	for (int k = 1; k <= n; k++) {
		for (int u = 1; u <= n; u++) {
			for (int v = 1; v <= n; v++) {
				adj[u][v] = min(adj[u][v], adj[u][k] + adj[k][v]);
			}
		}
	}
}

int main() {
	cin.tie(NULL); cout.tie(NULL);
	ios_base::sync_with_stdio(false);

	init();

	input();

	floyd();

	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			if (adj[i][j] == INF) cout << 0 << ' ';
			else cout << adj[i][j] << ' ';
		}
		cout << '\n';
	}

	return 0;
}