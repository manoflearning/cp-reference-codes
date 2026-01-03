#include "../1-ds/segment_tree.cpp"

// what: heavy-light decomposition for path sum on tree (node values).
// time: build O(n), update/query O(log^2 n); memory: O(n)
// constraint: 1-indexed tree.
// usage: hld_tree h; h.init(n); h.add(u,v); h.build(1); h.set(v,x); ll s=h.qry(u,v);
struct hld_tree {
    seg_tree seg;

    int n, tim;
    vvi adj;
    vi par, dep, siz, heavy, top, in;

    void init(int n_) {
        n = n_;
        tim = 0;
        adj.assign(n + 1, {});
        par.assign(n + 1, 0);
        dep.assign(n + 1, 0);
        siz.assign(n + 1, 0);
        heavy.assign(n + 1, -1);
        top.assign(n + 1, 0);
        in.assign(n + 1, 0);
    }
    void add(int u, int v) {
        adj[u].pb(v);
        adj[v].pb(u);
    }
    int dfs_sz(int v, int p) {
        // goal: compute subtree sizes and heavy child.
        par[v] = p;
        dep[v] = dep[p] + 1;
        siz[v] = 1;
        int mx = 0;
        for (int to : adj[v]) {
            if (to == p) continue;
            int s = dfs_sz(to, v);
            siz[v] += s;
            if (s > mx) mx = s, heavy[v] = to;
        }
        return siz[v];
    }
    void dfs_hld(int v, int h) {
        // invariant: top[v] is head of heavy path.
        top[v] = h;
        in[v] = ++tim;
        if (heavy[v] != -1) dfs_hld(heavy[v], h);
        for (int to : adj[v])
            if (to != par[v] && to != heavy[v]) dfs_hld(to, to);
    }
    void build(int root = 1) {
        dfs_sz(root, 0);
        dfs_hld(root, root);
        vl a(n + 1, 0);
        seg.build(a);
    }
    void set(int v, ll val) { seg.set(in[v], val); }
    ll qry(int a, int b) const {
        ll ret = 0;
        while (top[a] != top[b]) {
            if (dep[top[a]] < dep[top[b]]) swap(a, b);
            ret += seg.query(in[top[a]], in[a]);
            a = par[top[a]];
        }
        if (dep[a] > dep[b]) swap(a, b);
        ret += seg.query(in[a], in[b]);
        return ret;
    }
};
