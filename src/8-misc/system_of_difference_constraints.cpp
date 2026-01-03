#include "../common/common.hpp"

// what: solve difference constraints x_v - x_u <= w with Bellman-Ford.
// time: O(nm) via Bellman-Ford; memory: O(n+m)
// constraint: 0-indexed vars; no overflow in relaxations.
// usage: diff_cons dc(n); dc.add_le(u,v,w); bool ok=dc.solve(); auto x=dc.val();
struct diff_cons {
    struct edge {
        int to;
        ll w;
    };

    int n;
    vector<vector<edge>> g;
    vl dist;

    diff_cons(int n_ = 0) { init(n_); }

    void init(int n_) {
        n = n_;
        g.assign(n, {});
        dist.assign(n, 0);
    }

    void add_le(int u, int v, ll w) {
        // goal: x_v - x_u <= w
        g[u].pb({v, w});
    }

    void add_ge(int u, int v, ll w) {
        // goal: x_v - x_u >= w  <=>  x_u - x_v <= -w
        add_le(v, u, -w);
    }

    void add_eq(int u, int v, ll w) {
        // goal: x_v - x_u = w
        add_le(u, v, w);
        add_le(v, u, -w);
    }

    bool solve() {
        // invariant: dist is current potential, all nodes reachable from super source
        dist.assign(n, 0);
        for (int it = 0; it < n; it++) {
            bool upd = false;
            for (int v = 0; v < n; v++) {
                for (const auto &e : g[v]) {
                    if (dist[e.to] > dist[v] + e.w) {
                        dist[e.to] = dist[v] + e.w;
                        upd = true;
                    }
                }
            }
            if (!upd) return true;
        }
        for (int v = 0; v < n; v++) {
            for (const auto &e : g[v]) {
                if (dist[e.to] > dist[v] + e.w) return false;
            }
        }
        return true;
    }

    vl val() const { return dist; }
};
