#include "../common/common.hpp"

// what: greedy merge on tree by exchange argument (problem-specific cost).
// time: O(n log n); memory: O(n)
// constraint: 1-indexed tree; defaults w[i]=i, t[i]=1.
// usage: tree_xchg tx; tx.init(n, root); tx.add(u,v); ll ans=tx.run();
struct tree_xchg {
    struct uf {
        vector<int> par;
        vector<ll> cw, w, t;
        void init(int n) {
            par.assign(n + 1, -1);
            cw.resize(n + 1);
            w.resize(n + 1);
            t.assign(n + 1, 1);
            iota(all(cw), 0);
            iota(all(w), 0);
        }
        int find(int x) { return par[x] < 0 ? x : par[x] = find(par[x]); }
        void merge(int u, int v) {
            // goal: merge v into u (both roots).
            par[v] = u;
            cw[u] += t[u] * w[v] + cw[v];
            w[u] += w[v];
            t[u] += t[v];
        }
    } ds;
    struct node {
        ll cw, w, t;
        int v;
        bool operator<(const node &o) const { return w * o.t > o.w * t; }
    };

    int n, root;
    vector<vector<int>> adj;
    vector<int> par;

    void init(int n_, int r) {
        n = n_;
        root = r;
        adj.assign(n + 1, {});
        par.assign(n + 1, 0);
        ds.init(n);
    }
    void add(int u, int v) {
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    void dfs(int v, int p) {
        par[v] = p;
        for (int to : adj[v])
            if (to != p) dfs(to, v);
    }
    ll run() {
        dfs(root, 0);
        priority_queue<node> pq;
        for (int v = 1; v <= n; v++)
            if (v != root) pq.push({ds.cw[v], ds.w[v], ds.t[v], v});
        while (!pq.empty()) {
            auto [cw, w, t, v] = pq.top();
            pq.pop();
            v = ds.find(v);
            if (w != ds.w[v]) continue;
            int p = ds.find(par[v]);
            ds.merge(p, v);
            if (p != root) pq.push({ds.cw[p], ds.w[p], ds.t[p], p});
        }
        return ds.cw[root];
    }
};
