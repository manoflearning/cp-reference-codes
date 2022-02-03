#include <iostream>
#include <vector>
using namespace std;

const int MAX = 1e5;
const int INF = 1e9 + 7;

struct dv {
	int d, v;
};

int N;
vector<dv> adj[MAX + 5];
vector<int> upper(MAX + 5, INF);

void scan();
bool bellman_ford();

int main() {
	cin.tie(NULL); cout.tie(NULL);
	ios_base::sync_with_stdio(false);

	scan();

	if (bellman_ford()) {
		for (int i = 2; i <= N; i++) {
			if (upper[i] == INF) cout << -1 << '\n';
			else cout << upper[i] << '\n';
		}
	}
	else cout << -1 << '\n';

	return 0;
}

void scan() {
	int M;
	cin >> N >> M;

	for (int i = 0; i < M; i++) {
		int u, v, d;
		cin >> u >> v >> d;
		adj[u].push_back({ d, v });
	}
}

bool bellman_ford() {
	upper[1] = 0;

	bool update = true;
	for (int i = 0; i <= N; i++) {
		update = false;
		for (int now = 1; now <= N; now++) {
			if (upper[now] == INF) continue;
			for (dv e : adj[now]) {
				int next = e.v;
				if (upper[next] > upper[now] + e.d) {
					upper[next] = upper[now] + e.d;
					update = true;
				}
			}
		}

		if (!update) break;
	}

	return !update;
}
