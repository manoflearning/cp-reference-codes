#include <bits/stdc++.h>
using namespace std;
const int MAXV = 202020;
vector<int> adj[MAXV], g[MAXV];
int siz[MAXV], dep[MAXV], par[MAXV];
int top[MAXV], in[MAXV], out[MAXV], pv;
void dfs(int v, int prv) {
	for (auto& i : adj[v]) {
		if (i == prv) continue;
		g[v].push_back(i);
		dfs(i, v);
	}
}
int dfs1(int v) {
	siz[v] = 1;
	for (auto& i : g[v]) {
		dep[i] = dep[v] + 1, par[i] = v;
		siz[v] += dfs1(i);
		if (siz[i] > siz[g[v][0]]) swap(i, g[v][0]);
	}
	return siz[v];
}
void dfs2(int v) {
	in[v] = ++pv;
	for (auto& i : g[v]) {
		top[i] = (i == g[v][0] ? top[v] : i);
		dfs2(i);
	}
	out[v] = pv;
}
int main() {
	cin.tie(NULL); cout.tie(NULL);
	ios_base::sync_with_stdio(false);
	dfs(1, 0);
	top[1] = 1;
	dfs1(1); 
	dfs2(1);
	return 0;
}