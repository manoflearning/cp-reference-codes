#include <iostream>
#include <vector>
using namespace std;

const int MAX = 1e5, MAXD = 16;

vector<int> adj[MAX + 5];
int N, dep[MAX + 5], par[MAX + 5][MAXD + 5];

void dfs(int now, int prv);
int lca(int u, int v);

int main() {
	cin.tie(NULL); cout.tie(NULL);
	ios_base::sync_with_stdio(false);

	dfs(1, 0);

	//Á¡È­½Ä
	for (int i = 1; i <= MAXD; i++) {
		for (int v = 1; v <= N; v++) {
			par[v][i] = par[par[v][i - 1]][i - 1];
		}
	}

	int Q; cin >> Q;
	while (Q--) {
		int u, v;
		cin >> u >> v;

		cout << lca(u, v) << '\n';
	}

	return 0;
}

void dfs(int now, int prv) {
	par[now][0] = prv;
	dep[now] = dep[prv] + 1;
	for (int i : adj[now]) {
		if (i == prv) continue;
		dfs(i, now);
	}
}

int lca(int u, int v) {
	if (dep[u] < dep[v]) swap(u, v);

	int diff = dep[u] - dep[v];
	for (int i = MAXD; i >= 0; i--)
		if (diff & (1 << i)) u = par[u][i];

	if (u == v) return u;

	for (int i = MAXD; i >= 0; i--) {
		if (par[u][i] ^ par[v][i]) {
			u = par[u][i];
			v = par[v][i];
		}
	}
	return par[u][0];
}
