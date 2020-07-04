#include <iostream>
#include <vector>
#include <queue>
using namespace std;

const int MAXV = 2 * 1e5;
const int INF = 1e9 + 7;

struct dv {
	int d, v;
};

struct cmp {
	bool operator() (dv a, dv b) {
		return a.d > b.d;
	}
};

int V, st;
vector<dv> adj[MAXV + 5];
vector<int> dist(MAXV + 5, INF);

void input();
void dijkstra(int st);

int main() {
	cin.tie(NULL); cout.tie(NULL);
	ios_base::sync_with_stdio(false);

	input();

	dijkstra(st);

	for (int i = 1; i <= V; i++) {
		if (dist[i] == INF) cout << "INF\n";
		else cout << dist[i] << '\n';
	}

	return 0;
}

void input() {
	int E;
	cin >> V >> E >> st;

	for (int i = 0; i < E; i++) {
		int u, v, d;
		cin >> u >> v >> d;
		adj[u].push_back({ d, v });
		adj[v].push_back({ d, u });
	}
}

void dijkstra(int st) {
	priority_queue<dv, vector<dv>, cmp> pq;

	pq.push({ 0, st });
	dist[st] = 0;

	while (!pq.empty()) {
		int now = pq.top().v, d = pq.top().d;
		pq.pop();

		for (auto& e : adj[now]) {
			int next = e.v;
			if (dist[next] > dist[now] + e.d) {
				dist[next] = dist[now] + e.d;
				pq.push({ dist[next], next });
			}
		}
	}
}
