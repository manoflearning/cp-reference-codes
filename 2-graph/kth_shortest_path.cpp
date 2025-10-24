#include "../common/common.hpp"

// call init(|V|) first, add_edge(u, v, x), then kth_walk(s, e, K)
// O(|E|log|E|+klogk) in total
// if there is negative edge, O((SPFA time) + |E|log|E| + klogk)
// multi-edges, loops are allowed.
// ALERT: max answer = K|E||X| could be too large.
const int MAXN = 303030, HSIZE = 20202020; // HSIZE >= 2|E|log|E|
const ll INF = 1e18;                       // INF >= |E||X| (not need to be larger than K|E||X|)
int n;
vector<pair<ll, int>> gph[MAXN], rgph[MAXN];
struct Lheap {
  struct Node {
    pll x;
    int l, r, s;
    Node(void) : x({0, 0}), l(0), r(0), s(0) {}
    Node(pll x) : x(x), l(0), r(0), s(1) {}
  } h[HSIZE];
  int cnt = 1;
  int mk(pll x) {
    h[cnt] = Node(x);
    return cnt++;
  }
  void norm(int x) {
    if (h[h[x].l].s < h[h[x].r].s) swap(h[x].l, h[x].r);
    h[x].s = h[h[x].r].s + 1;
  }
  int mrge(int x, int y) {
    if (!x || !y) return x ^ y;
    if (h[x].x > h[y].x) swap(x, y);
    int ret = mk(h[x].x);
    h[ret].l = h[x].l;
    h[ret].r = mrge(h[x].r, y);
    norm(ret);
    return ret;
  }
} hp;
void init(int _n) {
  n = _n;
  for (int i = 1; i <= n; ++i) gph[i].clear();
  for (int i = 1; i <= n; ++i) rgph[i].clear();
  hp.cnt = 1;
}
void add_edge(int u, int v, ll w) {
  gph[u].push_back({w, v});
  rgph[v].push_back({w, u});
}
// return less than K elements if there is no such walk
vector<ll> kth_walk(int s, int e, int K) {
  vector<int> nxt(n + 1);
  vector<int> top;
  vector<bool> vst(n + 1);
  vector<ll> dst(n + 1, INF);
  dst[e] = 0;
  typedef tuple<ll, int, int> tlii;
  // if there is no negative edge
  priority_queue<tlii, vector<tlii>, greater<tlii>> Q;
  Q.push({0, e, -1});
  while (!Q.empty()) {
    auto [d, x, p] = Q.top();
    Q.pop();
    if (vst[x]) continue;
    vst[x] = 1;
    nxt[x] = p;
    top.push_back(x);
    for (auto [c, y] : rgph[x])
      if (!vst[y] && dst[y] > d + c) dst[y] = d + c, Q.push({d + c, y, x});
  }
  // if there is negative edge
  // nxt[e] = -1;
  // for(int t = 0; t < n; ++t) {
  // 	for(int x = 0; x < n; ++x) for(auto [c, y] : rgph[x]) if(dst[y] > dst[x] + c)
  // 		dst[y] = dst[x] + c, nxt[y] = x;
  // }
  // // OR use SPFA
  // vector<int> ls[n];
  // for(int i = 0; i < n; ++i) if(nxt[i] != -1) ls[nxt[i]].push_back(i);
  // queue<int> Q; Q.push(e);
  // while(Q.size()) {
  // 	int x = Q.front(); Q.pop();
  // 	top.push_back(x);
  // 	for(auto y : ls[x]) Q.push(y);
  // }
  if (dst[s] >= INF) return vector<ll>();
  vector<bool> chc(n + 1);
  vector<int> rt(n + 1);
  for (auto x : top)
    if (dst[x] < INF) {
      if (nxt[x] != -1) rt[x] = rt[nxt[x]];
      for (auto [c, y] : gph[x])
        if (dst[y] < INF) {
          if (!chc[x] && y == nxt[x] && dst[x] == c + dst[y]) {
            chc[x] = 1;
            continue;
          }
          rt[x] = hp.mrge(rt[x], hp.mk({c + dst[y] - dst[x], y}));
        }
    }
  vector<ll> ret({dst[s]});
  priority_queue<pll, vector<pll>, greater<pll>> PQ;
  if (rt[s]) PQ.push({hp.h[rt[s]].x.fr, rt[s]});
  while (sz(ret) < K && !PQ.empty()) {
    auto [d, x] = PQ.top();
    PQ.pop();
    ret.push_back(dst[s] + d);
    if (rt[hp.h[x].x.sc]) PQ.push({d + hp.h[rt[hp.h[x].x.sc]].x.fr, rt[hp.h[x].x.sc]});
    if (hp.h[x].l) PQ.push({d - hp.h[x].x.fr + hp.h[hp.h[x].l].x.fr, hp.h[x].l});
    if (hp.h[x].r) PQ.push({d - hp.h[x].x.fr + hp.h[hp.h[x].r].x.fr, hp.h[x].r});
  }
  return ret;
}