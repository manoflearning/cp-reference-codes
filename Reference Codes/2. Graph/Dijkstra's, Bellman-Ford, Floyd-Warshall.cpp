// Dijkstra's Algorithm

// INPUT: Given a directed graph with positive weights on the edges. Given a starting vertex.
// OUTPUT: Outputs the shortest distance from the starting vertex to all vertices.
// TIME COMPLEXITY: O(ElogV)

// BOJ 1753 AC Code
// https://www.acmicpc.net/problem/1753

#include <bits/stdc++.h>
using namespace std;
#define ll long long

const ll INF = 1e18;
const int MAX = 202020;

struct wv {
	ll w; int v;
	bool operator<(const wv& rhs) const {
		return w > rhs.w;
	}
};

int n, m, st;
vector<wv> adj[MAX];
vector<ll> dist(MAX, INF);

void input() {
	cin >> n >> m >> st;
	for (int i = 0; i < m; i++) {
		int u, v, w;
		cin >> u >> v >> w;
		adj[u].push_back({ w, v });
	}
}

void dijkstra(int st) {
	priority_queue<wv> pq;
	pq.push({ 0, st });
	dist[st] = 0;
	while (!pq.empty()) {
		auto [w, v] = pq.top();
		pq.pop();
		if (w > dist[v]) continue;
		for (auto& i : adj[v]) {
			if (dist[i.v] > w + i.w) {
				dist[i.v] = w + i.w;
				pq.push({ w + i.w, i.v });
			}
		}
	}
}

int main() {
	cin.tie(NULL); cout.tie(NULL);
	ios_base::sync_with_stdio(false);

	input();

	dijkstra(st);

	for (int i = 1; i <= n; i++) {
		if (dist[i] == INF) cout << "INF\n";
		else cout << dist[i] << '\n';
	}

	return 0;
}

// Bellman-Ford Algorithm

// INPUT: Given a directed graph with weighted(possibly negative) edges and no negative cycles. Given a starting vertex.
// OUTPUT: Outputs the shortest distance from the starting vertex to all vertices.
// TIME COMPLEXITY: O(VE)

// BOJ 11657 AC Code
// https://www.acmicpc.net/problem/11657

#include <bits/stdc++.h>
using namespace std;
#define ll long long

const int MAX = 101010;
const ll INF = 1e18;

struct wv {
	ll w; int v;
};

int n, m;
vector<wv> adj[MAX];
vector<ll> upper(MAX, INF);

void input() {
	cin >> n >> m;
	for (int i = 0; i < m; i++) {
		int u, v, w;
		cin >> u >> v >> w;
		adj[u].push_back({ w, v });
	}
}

int bellmanFord() {
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

	if (bellmanFord()) {
		for (int i = 2; i <= n; i++) {
			if (upper[i] == INF) cout << -1 << '\n';
			else cout << upper[i] << '\n';
		}
	}
	else cout << -1 << '\n';

	return 0;
}

// Floyd-Warshall Algorithm

// INPUT: Given a directed graph with weighted(possibly negative) edges and no negative cycles.
// OUTPUT: Outputs the shortest distance from all vertices to all vertices.
// TIME COMPLEXITY: O(V^3)

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