#include "../../src/3-tree/lca_sparse.cpp"

// what: tests for lca_sparse.
// time: random + brute; memory: O(n^2)
// constraint: small n.
// usage: g++ -std=c++17 test_lca_sparse_table.cpp && ./a.out

mt19937_64 rng(8);
int rnd(int l, int r) {
    uniform_int_distribution<int> dis(l, r);
    return dis(rng);
}

int lca_na(int n, const vector<vector<int>> &adj, int root, int a, int b) {
    vector<int> par(n + 1, 0), dep(n + 1, 0);
    queue<int> q;
    q.push(root);
    par[root] = root;
    while (!q.empty()) {
        int v = q.front();
        q.pop();
        for (int to : adj[v]) {
            if (to == par[v]) continue;
            par[to] = v;
            dep[to] = dep[v] + 1;
            q.push(to);
        }
    }
    while (dep[a] > dep[b]) a = par[a];
    while (dep[b] > dep[a]) b = par[b];
    while (a != b) a = par[a], b = par[b];
    return a;
}

void t_rnd() {
    for (int it = 0; it < 200; it++) {
        int n = rnd(2, 20);
        vector<int> par(n + 1, 0);
        vector<vector<int>> adj(n + 1);
        for (int v = 2; v <= n; v++) {
            par[v] = rnd(1, v - 1);
            adj[v].push_back(par[v]);
            adj[par[v]].push_back(v);
        }
        lca_sparse l;
        l.init(n);
        for (int v = 2; v <= n; v++) l.add(v, par[v]);
        l.build(1);
        for (int q = 0; q < 50; q++) {
            int a = rnd(1, n), b = rnd(1, n);
            assert(l.lca(a, b) == lca_na(n, adj, 1, a, b));
        }
    }
}

int main() {
    t_rnd();
    return 0;
}
