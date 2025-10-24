#include "../common/common.hpp"

namespace hld {
const int MAXN = 202020;

int flag;    // array size
struct Seg { // 1-indexed
  vector<ll> t;
  void build(int n) {
    for (flag = 1; flag < n; flag <<= 1);
    t.resize(flag << 1);
  }
  void modify(int p, ll value) { // set value at position p
    for (t[p += flag - 1] = value; p > 1; p >>= 1) t[p >> 1] = t[p] + t[p ^ 1];
  }
  ll query(int l, int r, int n = 1, int nl = 1, int nr = flag) { // sum on interval [l, r]
    if (r < nl || nr < l) return 0;
    if (l <= nl && nr <= r) return t[n];
    int mid = (nl + nr) / 2;
    return query(l, r, n << 1, nl, mid) + query(l, r, n << 1 | 1, mid + 1, nr);
  }
} seg;

int n;
vector<int> adj[MAXN], g[MAXN];
int siz[MAXN], dep[MAXN], par[MAXN];
int top[MAXN], in[MAXN], pv;

void dfs(int v, int prv) {
  for (auto &i : adj[v]) {
    if (i == prv) continue;
    g[v].push_back(i);
    dfs(i, v);
  }
}
int dfs1(int v) {
  siz[v] = 1;
  for (auto &i : g[v]) {
    dep[i] = dep[v] + 1, par[i] = v;
    siz[v] += dfs1(i);
    if (siz[i] > siz[g[v][0]]) swap(i, g[v][0]);
  }
  return siz[v];
}
void dfs2(int v) {
  in[v] = ++pv;
  for (auto &i : g[v]) {
    top[i] = (i == g[v][0] ? top[v] : i);
    dfs2(i);
  }
}
void modify(int v, ll value) {
  seg.modify(in[v], value);
}
ll query(int u, int v) {
  ll ret = 0;
  while (top[u] ^ top[v]) {
    if (dep[top[u]] < dep[top[v]]) swap(u, v);
    int st = top[u];
    ret += seg.query(in[st], in[u]);
    u = par[st];
  }
  if (dep[u] > dep[v]) swap(u, v);
  return ret += seg.query(in[u], in[v]);
}
void hld() {
  dfs(1, 0);
  top[1] = 1;
  dfs1(1);
  dfs2(1);
  seg.build(n);
}
} // namespace hld