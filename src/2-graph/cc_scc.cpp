#include "../0-common/common.hpp"

// what: compute SCCs in a directed graph using Kosaraju's algorithm.
// time: O(n+m); memory: O(n+m)
// constraint: directed; 1-indexed; recursion depth O(n).
// usage: scc_kosa s; s.init(n); s.add_edge(u,v); int c=s.run();
struct scc_kosa {
    int n;
    vector<vector<int>> g, rg, sccs;
    vector<int> vis, comp, ord;

    void init(int n_) {
        n = n_;
        g.assign(n + 1, {});
        rg.assign(n + 1, {});
        sccs.clear();
        vis.assign(n + 1, 0);
        comp.assign(n + 1, -1);
        ord.clear();
    }
    void add_edge(int u, int v) {
        g[u].push_back(v);
        rg[v].push_back(u);
    }
    void dfs1(int v) {
        vis[v] = 1;
        for (int to : rg[v])
            if (!vis[to]) dfs1(to);
        ord.push_back(v);
    }
    void dfs2(int v, int id) {
        comp[v] = id;
        sccs[id].push_back(v);
        for (int to : g[v])
            if (comp[to] == -1) dfs2(to, id);
    }
    int run() {
        for (int v = 1; v <= n; v++)
            if (!vis[v]) dfs1(v);
        reverse(all(ord));
        for (int v : ord) {
            if (comp[v] != -1) continue;
            sccs.push_back({});
            dfs2(v, sz(sccs) - 1);
        }
        return sz(sccs);
    }
};

// what: compute SCCs in a directed graph using Tarjan's algorithm.
// time: O(n+m); memory: O(n+m)
// constraint: directed; 1-indexed; recursion depth O(n).
// usage: scc_tarjan s; s.init(n); s.add_edge(u,v); int c=s.run();
struct scc_tarjan {
    int n, tim;
    vector<vector<int>> g, sccs;
    vector<int> dfn, low, comp, st, ins;

    void init(int n_) {
        n = n_;
        tim = 0;
        g.assign(n + 1, {});
        sccs.clear();
        dfn.assign(n + 1, -1);
        low.assign(n + 1, 0);
        comp.assign(n + 1, -1);
        ins.assign(n + 1, 0);
        st.clear();
    }
    void add_edge(int u, int v) { g[u].push_back(v); }
    void dfs(int v) {
        dfn[v] = low[v] = ++tim;
        st.push_back(v);
        ins[v] = 1;
        for (int to : g[v]) {
            if (dfn[to] == -1) {
                dfs(to);
                low[v] = min(low[v], low[to]);
            } else if (ins[to]) {
                low[v] = min(low[v], dfn[to]);
            }
        }
        if (low[v] != dfn[v]) return;
        sccs.push_back({});
        int id = sz(sccs) - 1;
        while (1) {
            int x = st.back();
            st.pop_back();
            ins[x] = 0;
            comp[x] = id;
            sccs[id].push_back(x);
            if (x == v) break;
        }
    }
    int run() {
        for (int v = 1; v <= n; v++)
            if (dfn[v] == -1) dfs(v);
        return sz(sccs);
    }
};
