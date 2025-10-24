#include "../common/common.hpp"

const int MAXN = 303030;
struct UF {
  vector<int> uf;
  vector<ll> cw, w, t;
  void build(int n) {
    uf.resize(n + 1, -1);
    cw.resize(n + 1);
    iota(all(cw), 0);
    w.resize(n + 1);
    iota(all(w), 0);
    t.resize(n + 1, 1);
  }
  int find(int x) {
    if (uf[x] < 0) return x;
    return uf[x] = find(uf[x]);
  }
  void merge(int u, int v) {
    // int U = find(u), V = find(v);
    // assert(U != V);
    uf[v] = u;
    cw[u] += t[u] * w[v] + cw[v];
    w[u] += w[v];
    t[u] += t[v];
  }
} uf;
struct Node {
  ll cw, w, t;
  int v;
  bool operator<(const Node &o) const {
    return w * o.t > o.w * t;
  }
};
int n, ro;
vector<int> adj[MAXN];
int par[MAXN];
void input() {
  cin >> n >> ro;
  uf.build(n);
  for (int i = 0; i < n - 1; i++) {
    int u, v;
    cin >> u >> v;
    adj[u].push_back(v);
    adj[v].push_back(u);
  }
}
void dfs(int v, int prv) {
  par[v] = prv;
  for (auto &i : adj[v]) {
    if (i != prv) dfs(i, v);
  }
}
void solve() {
  priority_queue<Node> pq;
  for (int v = 1; v <= n; v++)
    if (v != ro) pq.push({uf.cw[v], uf.w[v], uf.t[v], v});
  while (!pq.empty()) {
    auto [cw, w, t, v] = pq.top();
    pq.pop();
    v = uf.find(v);
    if (w != uf.w[v]) continue;
    int p = uf.find(par[v]);
    uf.merge(p, v);
    if (p != ro) pq.push({uf.cw[p], uf.w[p], uf.t[p], p});
  }
}
int main() {
  input();
  dfs(ro, 0);
  solve();
  cout << uf.cw[ro];
}