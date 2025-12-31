#include "../../src/3-tree/tree_composition.cpp"

// what: tests for tree_comp (virtual tree builder).
// time: random + brute; memory: O(n^2)
// constraint: small n.
// usage: g++ -std=c++17 test_tree_comp.cpp && ./a.out

mt19937_64 rng(9);
int rnd(int l, int r) {
    uniform_int_distribution<int> dis(l, r);
    return dis(rng);
}

void dfs_vt(int v, const vector<vector<int>> &vt, vector<int> &vis) {
    vis[v] = 1;
    for (int to : vt[v]) dfs_vt(to, vt, vis);
}

void t_rnd() {
    for (int it = 0; it < 200; it++) {
        int n = rnd(2, 30);
        vector<int> par(n + 1, 0);
        for (int v = 2; v <= n; v++) par[v] = rnd(1, v - 1);
        tree_comp tc;
        tc.init(n);
        for (int v = 2; v <= n; v++) tc.add(v, par[v]);
        tc.build(1);

        int k = rnd(1, n);
        vector<int> vs;
        vector<int> used(n + 1);
        while (sz(vs) < k) {
            int x = rnd(1, n);
            if (used[x]) continue;
            used[x] = 1;
            vs.push_back(x);
        }

        auto nodes = tc.make(vs);
        vector<int> mark(n + 1);
        for (int v : nodes) mark[v] = 1;

        vector<int> vis(n + 1);
        dfs_vt(nodes[0], tc.vt_adj, vis);
        for (int v : nodes) assert(vis[v]);

        for (int v : nodes)
            for (int to : tc.vt_adj[v]) {
                assert(tc.is_anc(v, to));
                assert(mark[v] && mark[to]);
            }
    }
}

int main() {
    t_rnd();
    return 0;
}
