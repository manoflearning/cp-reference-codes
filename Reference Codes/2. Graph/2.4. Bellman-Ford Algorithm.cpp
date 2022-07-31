// BOJ 11657 AC Code
// https://www.acmicpc.net/problem/11657
#include <bits/stdc++.h>
using namespace std;
#define ll long long

const int MAX = 1e5;
const ll INF = 1e18;

struct wv {
	ll w; int v;
};

int n, m;
vector<wv> adj[MAX + 5];
vector<ll> upper(MAX + 5, INF);

void input() {
	cin >> n >> m;

	for (int i = 0; i < m; i++) {
		int u, v, w;
		cin >> u >> v >> w;
		adj[u].push_back({ w, v });
	}
}

int bellman_ford() {
	upper[1] = 0;

	int update = 1;
	for (int i = 0; i <= n; i++) {
		update = 0;
		for (int now = 1; now <= n; now++) {
			if (upper[now] == INF) continue;
			for (wv e : adj[now]) {
				int next = e.v;
				if (upper[next] > upper[now] + e.w) {
					upper[next] = upper[now] + e.w;
					update = 1;
				}
			}
		}

		if (!update) break;
	}

	return !update;
}

int main() {
	cin.tie(NULL); cout.tie(NULL);
	ios_base::sync_with_stdio(false);

	input();

	if (bellman_ford()) {
		for (int i = 2; i <= n; i++) {
			if (upper[i] == INF) cout << -1 << '\n';
			else cout << upper[i] << '\n';
		}
	}
	else cout << -1 << '\n';

	return 0;
}