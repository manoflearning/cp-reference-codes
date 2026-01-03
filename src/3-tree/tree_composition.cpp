#include "../common/common.hpp"

// what: virtual tree builder for subset DP using LCA and dfs order.
// time: build O(n log n), make O(k log k); memory: O(n log n)
// constraint: 1-indexed tree.
// usage: tree_comp tc; tc.init(n); tc.add(u,v); tc.build(root); auto nodes=tc.make(vs); // use tc.vt_adj
struct tree_comp {
    int n, lg, tim;
    vvi adj, up, vt_adj;
    vi tin, tout, dep;

    void init(int n_) {
        n = n_;
        lg = 1;
        while ((1 << lg) <= n) lg++;
        adj.assign(n + 1, {});
        up.assign(lg, vi(n + 1, 0));
        vt_adj.assign(n + 1, {});
        tin.assign(n + 1, 0);
        tout.assign(n + 1, 0);
        dep.assign(n + 1, 0);
        tim = 0;
    }
    void add(int u, int v) {
        adj[u].pb(v);
        adj[v].pb(u);
    }
    void dfs(int v, int p) {
        // goal: build tin/tout, depth, and parents.
        up[0][v] = p;
        dep[v] = dep[p] + 1;
        tin[v] = ++tim;
        for (int to : adj[v])
            if (to != p) dfs(to, v);
        tout[v] = tim;
    }
    void build(int root = 1) {
        dfs(root, 0);
        for (int k = 0; k + 1 < lg; k++)
            for (int v = 1; v <= n; v++)
                up[k + 1][v] = up[k][up[k][v]];
    }
    bool is_anc(int a, int b) const {
        return tin[a] <= tin[b] && tout[b] <= tout[a];
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
    vi make(vi vs) {
        if (vs.empty()) return {};
        sort(all(vs), [&](int a, int b) { return tin[a] < tin[b]; });
        vs.erase(unique(all(vs)), vs.end());
        int m = sz(vs);
        for (int i = 0; i + 1 < m; i++) vs.pb(lca(vs[i], vs[i + 1]));
        sort(all(vs), [&](int a, int b) { return tin[a] < tin[b]; });
        vs.erase(unique(all(vs)), vs.end());
        for (int v : vs) vt_adj[v].clear();
        vi st;
        st.pb(vs[0]);
        for (int i = 1; i < sz(vs); i++) {
            int v = vs[i];
            // invariant: stack is ancestor chain.
            while (!is_anc(st.back(), v)) st.pop_back();
            vt_adj[st.back()].pb(v);
            st.pb(v);
        }
        return vs;
    }
};
