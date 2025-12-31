#include "../common/common.hpp"

// what: enumerate k-th shortest walk from s to t with non-negative weights (Eppstein-style).
// time: O((n+m)log m + klog k); memory: O(n+m+heap)
// constraint: 1-indexed; w >= 0; n <= MAXN-1; recursion depth O(log m).
// usage: kth_walk g; g.init(n); g.add(u,v,w); auto v=g.run(s,e,k);
struct kth_walk {
    static const int MAXN = 303030;
    static const ll INF = (ll)1e18;

    int n;
    vector<pll> g[MAXN], rg[MAXN];

    struct lhp {
        struct nd {
            pll x;
            int l, r, s;
        };
        vector<nd> h;
        void init() { h.assign(1, {{0, 0}, 0, 0, 0}); }
        int mk(pll x) {
            h.push_back({x, 0, 0, 1});
            return sz(h) - 1;
        }
        void norm(int x) {
            if (h[h[x].l].s < h[h[x].r].s) swap(h[x].l, h[x].r);
            h[x].s = h[h[x].r].s + 1;
        }
        int mrg(int x, int y) {
            if (!x || !y) return x ^ y;
            if (h[x].x > h[y].x) swap(x, y);
            int ret = mk(h[x].x);
            h[ret].l = h[x].l;
            h[ret].r = mrg(h[x].r, y);
            norm(ret);
            return ret;
        }
    } hp;

    void init(int n_) {
        n = n_;
        for (int i = 1; i <= n; i++) g[i].clear(), rg[i].clear();
        hp.init();
    }
    void add(int u, int v, ll w) {
        g[u].push_back({w, v});
        rg[v].push_back({w, u});
    }

    vector<ll> run(int s, int e, int k) {
        vector<int> nxt(n + 1, -1), ord, vis(n + 1);
        vector<ll> dist(n + 1, INF);

        // goal: shortest path tree from e on reversed graph.
        dist[e] = 0;
        using tli = tuple<ll, int, int>;
        priority_queue<tli, vector<tli>, greater<tli>> pq;
        pq.push({0, e, -1});
        while (!pq.empty()) {
            auto [d, x, p] = pq.top();
            pq.pop();
            if (vis[x]) continue;
            vis[x] = 1;
            nxt[x] = p;
            ord.push_back(x);
            for (auto [c, y] : rg[x]) {
                if (!vis[y] && dist[y] > d + c) {
                    dist[y] = d + c;
                    pq.push({dist[y], y, x});
                }
            }
        }
        if (dist[s] >= INF) return {};

        vector<int> rt(n + 1), chk(n + 1);
        for (int x : ord)
            if (dist[x] < INF) {
                if (nxt[x] != -1) rt[x] = rt[nxt[x]];
                for (auto [c, y] : g[x]) {
                    if (dist[y] >= INF) continue;
                    if (!chk[x] && y == nxt[x] && dist[x] == c + dist[y]) {
                        chk[x] = 1;
                        continue;
                    }
                    rt[x] = hp.mrg(rt[x], hp.mk({c + dist[y] - dist[x], y}));
                }
            }

        vector<ll> ans = {dist[s]};
        priority_queue<pll, vector<pll>, greater<pll>> pq2;
        if (rt[s]) pq2.push({hp.h[rt[s]].x.fr, rt[s]});
        while (sz(ans) < k && !pq2.empty()) {
            auto [d, x] = pq2.top();
            pq2.pop();
            ans.push_back(dist[s] + d);
            int y = hp.h[x].x.sc;
            if (rt[y]) pq2.push({d + hp.h[rt[y]].x.fr, rt[y]});
            if (hp.h[x].l) pq2.push({d - hp.h[x].x.fr + hp.h[hp.h[x].l].x.fr, hp.h[x].l});
            if (hp.h[x].r) pq2.push({d - hp.h[x].x.fr + hp.h[hp.h[x].r].x.fr, hp.h[x].r});
        }
        return ans;
    }
};
