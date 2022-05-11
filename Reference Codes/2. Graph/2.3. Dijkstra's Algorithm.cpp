#include <iostream>
#include <vector>
#include <queue>
using namespace std;
#define ll long long

const int MAX = 202020;
const int INF = 1e9 + 7;

struct wv {
	ll w;
	int v;
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
		adj[v].push_back({ w, u });
	}
}

void dijkstra(int st) {
	priority_queue<wv> pq;

	pq.push({ 0, st });
	dist[st] = 0;

	while (!pq.empty()) {
		int v = pq.top().v, w = pq.top().w;
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
		if (dist[i] == INF) cout << "can't go\n";
		else cout << dist[i] << '\n';
	}

	return 0;
}
