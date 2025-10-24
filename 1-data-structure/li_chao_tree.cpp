#include "../common/common.hpp"

// INPUT: Initially, a 2d plane in which no linear function exists is given.
// Two types of queries are given.
// 1 a b : The linear function f(x) = ax + b is added.
// 2 x : Find the max(f(x)) among the linear functions given so far.
// OUTPUT: For each query 2 x, output the max(f(x)) among the linear functions given so far.
// TIME COMPLEXITY: O(qlogq)
#define Line pair<ll, ll>

const Line e = {0, -1e18};
struct LiChaoTree {
  ll f(Line l, ll x) { return l.first * x + l.second; }
  struct Node {
    ll xl, xr;
    int l, r;
    Line line;
  };
  vector<Node> t;
  void build(ll xlb, ll xub) {
    t.push_back({xlb, xub, -1, -1, e});
  }
  void insert(Line newLine, int n = 0) {
    ll xl = t[n].xl, xr = t[n].xr;
    ll xmid = (xl + xr) >> 1;

    Line llow = t[n].line, lhigh = newLine;
    if (f(llow, xl) >= f(lhigh, xl)) swap(llow, lhigh);

    if (f(llow, xr) <= f(lhigh, xr)) {
      t[n].line = lhigh;
      return;
    } else if (f(llow, xmid) < f(lhigh, xmid)) {
      t[n].line = lhigh;
      if (t[n].r == -1) {
        t[n].r = sz(t);
        t.push_back({xmid + 1, xr, -1, -1, e});
      }
      insert(llow, t[n].r);
    } else if (f(llow, xmid) >= f(lhigh, xmid)) {
      t[n].line = llow;
      if (t[n].l == -1) {
        t[n].l = sz(t);
        t.push_back({xl, xmid, -1, -1, e});
      }
      insert(lhigh, t[n].l);
    }
  }
  ll query(ll x, int n = 0) {
    if (n == -1) return e.second;
    ll xl = t[n].xl, xr = t[n].xr;
    ll xmid = (xl + xr) >> 1;

    ll ret = f(t[n].line, x);
    if (x <= xmid) ret = max(ret, query(x, t[n].l));
    else ret = max(ret, query(x, t[n].r));
    return ret;
  }
} lct;