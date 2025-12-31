#include "../common/common.hpp"

// what: SCC via Kosaraju.
// time: O(n+m); memory: O(n+m)
// constraint: directed; 1-indexed.
// usage: scc_ko s; s.init(n); s.add(u,v); int c=s.run();
struct scc_ko {
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
    void add(int u, int v) {
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

// what: SCC via Tarjan.
// time: O(n+m); memory: O(n+m)
// constraint: directed; 1-indexed.
// usage: scc_ta s; s.init(n); s.add(u,v); int c=s.run();
struct scc_ta {
    int n, tim;
    vector<vector<int>> g, sccs;
    vector<int> dfn, low, comp, st, inst;

    void init(int n_) {
        n = n_;
        tim = 0;
        g.assign(n + 1, {});
        sccs.clear();
        dfn.assign(n + 1, -1);
        low.assign(n + 1, 0);
        comp.assign(n + 1, -1);
        inst.assign(n + 1, 0);
        st.clear();
    }
    void add(int u, int v) { g[u].push_back(v); }
    void dfs(int v) {
        dfn[v] = low[v] = ++tim;
        st.push_back(v);
        inst[v] = 1;
        for (int to : g[v]) {
            if (dfn[to] == -1) {
                dfs(to);
                low[v] = min(low[v], low[to]);
            } else if (inst[to]) {
                low[v] = min(low[v], dfn[to]);
            }
        }
        if (low[v] != dfn[v]) return;
        sccs.push_back({});
        int id = sz(sccs) - 1;
        while (1) {
            int x = st.back();
            st.pop_back();
            inst[x] = 0;
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

// what: 2-SAT via SCC (Tarjan).
// time: O(n+m); memory: O(n+m)
// constraint: vars are 1..n; literal x<0 means not x.
// usage: two_sat s; s.init(n); s.add(a,b); bool ok=s.run(); // s.val
struct two_sat {
    int n, tim, sc;
    vector<vector<int>> g;
    vector<int> dfn, low, comp, st, inst, val;

    void init(int n_) {
        n = n_;
        g.assign(2 * n, {});
        dfn.assign(2 * n, -1);
        low.assign(2 * n, 0);
        comp.assign(2 * n, -1);
        inst.assign(2 * n, 0);
        st.clear();
        val.assign(n + 1, 0);
        tim = 0;
        sc = 0;
    }
    int id(int x) {
        // goal: x in [-n, n]\{0} -> node id.
        return x > 0 ? 2 * (x - 1) : 2 * (-x - 1) + 1;
    }
    void add(int a, int b) {
        // goal: (a v b) == (!a -> b) & (!b -> a)
        g[id(-a)].push_back(id(b));
        g[id(-b)].push_back(id(a));
    }
    void dfs(int v) {
        dfn[v] = low[v] = ++tim;
        st.push_back(v);
        inst[v] = 1;
        for (int to : g[v]) {
            if (dfn[to] == -1) {
                dfs(to);
                low[v] = min(low[v], low[to]);
            } else if (inst[to]) {
                low[v] = min(low[v], dfn[to]);
            }
        }
        if (low[v] != dfn[v]) return;
        while (1) {
            int x = st.back();
            st.pop_back();
            inst[x] = 0;
            comp[x] = sc;
            if (x == v) break;
        }
        sc++;
    }
    bool run() {
        for (int i = 0; i < 2 * n; i++)
            if (dfn[i] == -1) dfs(i);
        for (int i = 0; i < n; i++) {
            if (comp[2 * i] == comp[2 * i + 1]) return 0;
            val[i + 1] = comp[2 * i] > comp[2 * i + 1];
        }
        return 1;
    }
};
