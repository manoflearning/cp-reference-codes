#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

const int MAXV = 2 * 1e5;

vector<int> adj[MAXV + 5], g[MAXV + 5];
int sz[MAXV + 5], dep[MAXV + 5], par[MAXV + 5];
int top[MAXV + 5], in[MAXV + 5], out[MAXV + 5], pv;

void dfs(int v, int prv);
int dfs1(int v);
void dfs2(int v);

int main() {
	cin.tie(NULL); cout.tie(NULL);
	ios_base::sync_with_stdio(false);

	dfs(1, 0);
	top[1] = 1;
	dfs1(1); dfs2(1);

	return 0;
}

void dfs(int v, int prv) {
	for (auto& i : adj[v]) {
		if (i == prv) continue;
		g[v].push_back(i);
		dfs(i, v);
	}
}

int dfs1(int v) {
	sz[v] = 1;
	for (auto& i : g[v]) {
		dep[i] = dep[v] + 1, par[i] = v;
		sz[v] += dfs1(i);
		if (sz[i] > sz[g[v][0]]) swap(i, g[v][0]);
	}
	return sz[v];
}

void dfs2(int v) {
	in[v] = ++pv;
	for (auto& i : g[v]) {
		top[i] = (i == g[v][0] ? top[v] : i);
		dfs2(i);
	}
	out[v] = pv;
}
