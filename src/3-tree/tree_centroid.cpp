#include "../0-common/common.hpp"

// what: centroid decomposition for tree, builds centroid parent/children for path queries.
// time: O(n log n); memory: O(n)
// constraint: 1-indexed tree.
// usage: cen_decomp cd; cd.init(n); cd.add_edge(u,v); cd.build(); int p=cd.par[v];
struct cen_decomp {
    int n;
    vector<vector<int>> adj, chd;
    vector<int> par, siz;
    vector<char> used;

    void init(int n_) {
        n = n_;
        adj.assign(n + 1, {});
        chd.assign(n + 1, {});
        par.assign(n + 1, 0);
        siz.assign(n + 1, 0);
        used.assign(n + 1, 0);
    }
    void add_edge(int u, int v) {
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    int get_sz(int v, int p) {
        // goal: subtree sizes for centroid search.
        siz[v] = 1;
        for (int to : adj[v]) {
            if (to == p || used[to]) continue;
            siz[v] += get_sz(to, v);
        }
        return siz[v];
    }
    int get_cent(int v, int p, int tot) {
        // invariant: siz is valid for current component.
        for (int to : adj[v]) {
            if (to == p || used[to]) continue;
            if (siz[to] > tot / 2) return get_cent(to, v, tot);
        }
        return v;
    }
    void build(int v = 1, int p = 0) {
        int tot = get_sz(v, p);
        int c = get_cent(v, p, tot);
        par[c] = p;
        if (p) chd[p].push_back(c);
        used[c] = 1;
        for (int to : adj[c])
            if (!used[to]) build(to, c);
    }
};
