#include <iostream>
#include <vector>
#include <queue>
using namespace std;

const int MAXV = 2 * 1e5;
const int INF = 1e9 + 7;

struct dv {
	int d, v;
	bool operator<(dv& rhs) {
		return d < rhs.d;
	}
};

int N, st;
vector<dv> adj[MAXV + 5];
vector<int> dist(MAXV + 5, INF);

void input() {
	int E;
	cin >> N >> E >> st;

	for (int i = 0; i < E; i++) {
		int u, v, d;
		cin >> u >> v >> d;
		adj[u].push_back({ d, v });
		adj[v].push_back({ d, u });
	}
}

void dijkstra(int st) {
	priority_queue<dv> pq;

	pq.push({ 0, st });
	dist[st] = 0;

	while (!pq.empty()) {
		int now = pq.top().v, d = -pq.top().d;
		pq.pop();

		for (auto& e : adj[now]) {
			int next = e.v;
			if (dist[next] > dist[now] + e.d) {
				dist[next] = dist[now] + e.d;
				pq.push({ -dist[next], next });
			}
		}
	}
}

int main() {
	cin.tie(NULL); cout.tie(NULL);
	ios_base::sync_with_stdio(false);

	input();

	dijkstra(st);

	for (int i = 1; i <= N; i++) {
		if (dist[i] == INF) cout << "can't go\n";
		else cout << dist[i] << '\n';
	}

	return 0;
}
