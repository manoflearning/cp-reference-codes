#include "../common/common.hpp"

// what: find biconnected components and articulation points/bridges in an undirected graph.
// time: O(n+m); memory: O(n+m)
// constraint: 1-indexed; no self-loops; recursion depth O(n).
// usage: bcc_graph g; g.init(n); g.add(u,v); g.run(); // g.bccs, g.ap, g.ae
struct bcc_graph {
    int n, tim;
    vector<vector<pii>> adj;
    vector<int> dfn, low, ap, st;
    vector<pii> ed, ae;
    vector<vector<pii>> bccs;

    void init(int n_) {
        n = n_;
        tim = 0;
        adj.assign(n + 1, {});
        dfn.assign(n + 1, -1);
        low.assign(n + 1, 0);
        ap.clear();
        ae.clear();
        st.clear();
        ed.clear();
        bccs.clear();
    }
    void add(int u, int v) {
        int id = sz(ed);
        ed.pb({u, v});
        adj[u].pb({v, id});
        adj[v].pb({u, id});
    }
    void dfs(int v, int pe) {
        dfn[v] = low[v] = ++tim;
        int ch = 0;
        for (auto [to, id] : adj[v]) {
            if (id == pe) continue;
            if (dfn[to] != -1) {
                // edge: back edge to ancestor.
                low[v] = min(low[v], dfn[to]);
                if (dfn[to] < dfn[v]) st.pb(id);
                continue;
            }
            st.pb(id);
            ch++;
            dfs(to, id);
            low[v] = min(low[v], low[to]);
            if (pe != -1 && low[to] >= dfn[v]) ap.pb(v);
            if (low[to] > dfn[v]) ae.pb({min(v, to), max(v, to)});
            if (low[to] >= dfn[v]) {
                vector<pii> comp;
                while (1) {
                    int eid = st.back();
                    st.pop_back();
                    comp.pb(ed[eid]);
                    if (eid == id) break;
                }
                bccs.pb(comp);
            }
        }
        if (pe == -1 && ch > 1) ap.pb(v);
    }
    void run() {
        for (int v = 1; v <= n; v++)
            if (dfn[v] == -1) dfs(v, -1);
        sort(all(ap));
        ap.erase(unique(all(ap)), ap.end());
        sort(all(ae));
        ae.erase(unique(all(ae)), ae.end());
    }
};
