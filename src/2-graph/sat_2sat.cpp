#include "../0-common/common.hpp"

// what: solve 2-SAT by SCC condensation (Tarjan-based).
// time: O(n+m); memory: O(n+m)
// constraint: vars are 1..n; literal x<0 means not x; recursion depth O(n).
// usage: two_sat s; s.init(n); s.add(a,b); bool ok=s.run(); // s.val
struct two_sat {
    int n, tim, cid;
    vector<vector<int>> g;
    vector<int> dfn, low, comp, st, ins, val;

    void init(int n_) {
        n = n_;
        g.assign(2 * n, {});
        dfn.assign(2 * n, -1);
        low.assign(2 * n, 0);
        comp.assign(2 * n, -1);
        ins.assign(2 * n, 0);
        st.clear();
        val.assign(n + 1, 0);
        tim = 0;
        cid = 0;
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
        while (1) {
            int x = st.back();
            st.pop_back();
            ins[x] = 0;
            comp[x] = cid;
            if (x == v) break;
        }
        cid++;
    }
    bool run() {
        for (int i = 0; i < 2 * n; i++)
            if (dfn[i] == -1) dfs(i);
        for (int i = 0; i < n; i++) {
            if (comp[2 * i] == comp[2 * i + 1]) return 0;
            val[i + 1] = comp[2 * i] < comp[2 * i + 1];
        }
        return 1;
    }
};
