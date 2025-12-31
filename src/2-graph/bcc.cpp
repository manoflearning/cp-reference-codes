#include "../common/common.hpp"

// what: biconnected components + articulation points/edges (undirected).
// time: O(n+m); memory: O(n+m)
// constraint: 1-indexed; recursion depth O(n).
// usage: bcc g; g.init(n); g.add(u,v); g.run(); // g.bccs, g.ap, g.ae
struct bcc {
    int n, tim;
    vector<vector<int>> adj;
    vector<int> dfn, low, ap;
    vector<pii> ae, st;
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
        bccs.clear();
    }
    void add(int u, int v) {
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    void dfs(int v, int p) {
        dfn[v] = low[v] = ++tim;
        int ch = 0;
        for (int to : adj[v]) {
            if (to == p) continue;
            if (dfn[to] != -1) {
                // edge: back edge to ancestor.
                low[v] = min(low[v], dfn[to]);
                if (dfn[to] < dfn[v]) st.push_back({v, to});
                continue;
            }
            // goal: tree edge, expand subtree.
            st.push_back({v, to});
            ch++;
            dfs(to, v);
            low[v] = min(low[v], low[to]);
            if (p != -1 && low[to] >= dfn[v]) ap.push_back(v);
            if (low[to] > dfn[v]) ae.push_back({min(v, to), max(v, to)});
            if (low[to] >= dfn[v]) {
                vector<pii> comp;
                while (1) {
                    pii e = st.back();
                    st.pop_back();
                    comp.push_back(e);
                    if (e == pii{v, to}) break;
                }
                bccs.push_back(comp);
            }
        }
        if (p == -1 && ch > 1) ap.push_back(v);
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
