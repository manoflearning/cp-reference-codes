#include "../../src/8-misc/diff_cons.cpp"

// what: tests for difference constraints (negative cycle detection + solution).
// time: random + floyd; memory: O(n^2)
// constraint: fixed seed, small n.
// usage: g++ -std=c++17 test_diff_cons.cpp && ./a.out

mt19937_64 rng(2);
int rnd_int(int l, int r) {
    uniform_int_distribution<int> dis(l, r);
    return dis(rng);
}

bool has_neg_cycle(int n, const vector<tuple<int, int, ll>> &edges) {
    const ll INF = (1LL << 60);
    vector<vector<ll>> d(n + 1, vector<ll>(n + 1, INF));
    for (int i = 1; i <= n; i++) d[i][i] = 0;
    for (auto [u, v, w] : edges) d[u][v] = min(d[u][v], w);
    for (int k = 1; k <= n; k++) {
        for (int i = 1; i <= n; i++) {
            if (d[i][k] == INF) continue;
            for (int j = 1; j <= n; j++) {
                if (d[k][j] == INF) continue;
                ll nv = d[i][k] + d[k][j];
                if (nv < d[i][j]) d[i][j] = nv;
            }
        }
    }
    for (int i = 1; i <= n; i++)
        if (d[i][i] < 0) return true;
    return false;
}

void test_random() {
    for (int it = 0; it < 200; it++) {
        int n = rnd_int(2, 8);
        int m = rnd_int(1, 20);
        diff_cons dc(n);
        vector<tuple<int, int, ll>> edges;
        for (int i = 0; i < m; i++) {
            int u = rnd_int(1, n);
            int v = rnd_int(1, n);
            ll w = rnd_int(-5, 5);
            dc.add_le(u, v, w);
            edges.push_back({u, v, w});
        }
        bool ok = dc.solve();
        bool neg = has_neg_cycle(n, edges);
        assert(ok == !neg);
        if (ok) {
            vector<ll> x = dc.val();
            for (auto [u, v, w] : edges) {
                assert(x[v] <= x[u] + w);
            }
        }
    }
}

int main() {
    test_random();
    return 0;
}
