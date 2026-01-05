#include "../../src/3-tree/tree_hld.cpp"

// what: tests for hld_tree (path sum).
// time: random + brute; memory: O(n^2)
// constraint: small n.
// usage: g++ -std=c++17 test_hld.cpp && ./a.out

mt19937_64 rng(7);
int rnd(int l, int r) {
    uniform_int_distribution<int> dis(l, r);
    return dis(rng);
}

vector<int> path_nodes(int n, const vector<vector<int>> &adj, int s, int e) {
    vector<int> par(n + 1, -1);
    queue<int> q;
    q.push(s);
    par[s] = s;
    while (!q.empty()) {
        int v = q.front();
        q.pop();
        if (v == e) break;
        for (int to : adj[v]) {
            if (par[to] != -1) continue;
            par[to] = v;
            q.push(to);
        }
    }
    vector<int> res;
    int v = e;
    while (v != par[v]) {
        res.push_back(v);
        v = par[v];
    }
    res.push_back(s);
    return res;
}

void t_fix() {
    int n = 4;
    vector<vector<int>> adj(n + 1);
    auto add = [&](int u, int v) {
        adj[u].push_back(v);
        adj[v].push_back(u);
    };
    add(1, 2);
    add(2, 3);
    add(2, 4);

    hld_tree h;
    h.init(n);
    for (int u = 1; u <= n; u++)
        for (int v : adj[u])
            if (u < v) h.add(u, v);
    h.build(1);
    vector<ll> val = {0, 1, 2, 3, 4};
    for (int i = 1; i <= n; i++) h.set(i, val[i]);
    auto p = path_nodes(n, adj, 3, 4);
    ll sum = 0;
    for (int v : p) sum += val[v];
    assert(h.qry(3, 4) == sum);
}

void t_rnd() {
    for (int it = 0; it < 200; it++) {
        int n = rnd(2, 9);
        vector<int> par(n + 1, 0);
        vector<vector<int>> adj(n + 1);
        for (int v = 2; v <= n; v++) {
            par[v] = rnd(1, v - 1);
            adj[v].push_back(par[v]);
            adj[par[v]].push_back(v);
        }
        hld_tree h;
        h.init(n);
        for (int v = 2; v <= n; v++) h.add(v, par[v]);
        h.build(1);
        vector<ll> val(n + 1);
        for (int i = 1; i <= n; i++) {
            val[i] = rnd(-5, 5);
            h.set(i, val[i]);
        }
        for (int q = 0; q < 50; q++) {
            int a = rnd(1, n), b = rnd(1, n);
            auto p = path_nodes(n, adj, a, b);
            ll sum = 0;
            for (int v : p) sum += val[v];
            assert(h.qry(a, b) == sum);
        }
    }
}

int main() {
    t_fix();
    t_rnd();
    return 0;
}
