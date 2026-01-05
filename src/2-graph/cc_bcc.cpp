#include "../0-common/common.hpp"

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
        ed.push_back({u, v});
        adj[u].push_back({v, id});
        adj[v].push_back({u, id});
    }
    void dfs(int v, int pe) {
        dfn[v] = low[v] = ++tim;
        int ch = 0;
        for (auto [to, id] : adj[v]) {
            if (id == pe) continue;
            if (dfn[to] != -1) {
                // edge: back edge to ancestor.
                low[v] = min(low[v], dfn[to]);
                if (dfn[to] < dfn[v]) st.push_back(id);
                continue;
            }
            st.push_back(id);
            ch++;
            dfs(to, id);
            low[v] = min(low[v], low[to]);
            if (pe != -1 && low[to] >= dfn[v]) ap.push_back(v);
            if (low[to] > dfn[v]) ae.push_back({min(v, to), max(v, to)});
            if (low[to] >= dfn[v]) {
                vector<pii> comp;
                while (1) {
                    int eid = st.back();
                    st.pop_back();
                    comp.push_back(ed[eid]);
                    if (eid == id) break;
                }
                bccs.push_back(comp);
            }
        }
        if (pe == -1 && ch > 1) ap.push_back(v);
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
