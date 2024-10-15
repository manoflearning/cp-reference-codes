namespace sparse_table {
const int MAXN = 101010, MAXD = 16; // 2^MAXD = 65536

int n, dep[MAXN], par[MAXN][MAXD + 1];
vector<int> adj[MAXN];

void dfs(int now, int prv) {
  par[now][0] = prv;
  dep[now] = dep[prv] + 1;
  for (auto i : adj[now]) {
    if (i == prv) continue;
    dfs(i, now);
  }
}
void buildSparseTable() {
  for (int i = 1; i <= MAXD; i++) {
    for (int v = 1; v <= n; v++) {
      par[v][i] = par[par[v][i - 1]][i - 1];
    }
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
} // namespace sparse_table