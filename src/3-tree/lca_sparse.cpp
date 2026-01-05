#include "../0-common/common.hpp"

// what: LCA via binary lifting for rooted tree.
// time: build O(n log n), query O(log n); memory: O(n log n)
// constraint: 1-indexed tree.
// usage: lca_sparse l; l.init(n); l.add(u,v); l.build(1); int w=l.lca(u,v);
struct lca_sparse {
    int n, lg;
    vector<vector<int>> adj, up;
    vector<int> dep;

    void init(int n_) {
        n = n_;
        lg = 1;
        while ((1 << lg) <= n) lg++;
        adj.assign(n + 1, {});
        up.assign(lg, vector<int>(n + 1, 0));
        dep.assign(n + 1, 0);
    }
    void add(int u, int v) {
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    void dfs(int v, int p) {
        // goal: set parent and depth.
        up[0][v] = p;
        dep[v] = dep[p] + 1;
        for (int to : adj[v])
            if (to != p) dfs(to, v);
    }
    void build(int root = 1) {
        dfs(root, 0);
        for (int k = 0; k + 1 < lg; k++)
            for (int v = 1; v <= n; v++)
                up[k + 1][v] = up[k][up[k][v]];
    }
    int lca(int a, int b) const {
        if (dep[a] < dep[b]) swap(a, b);
        int diff = dep[a] - dep[b];
        for (int k = 0; k < lg; k++)
            if (diff & (1 << k)) a = up[k][a];
        if (a == b) return a;
        for (int k = lg - 1; k >= 0; k--) {
            if (up[k][a] != up[k][b]) {
                a = up[k][a];
                b = up[k][b];
            }
        }
        return up[0][a];
    }
};
