#include "../../src/2-graph/sp_kth.cpp"

// what: tests for k-th shortest walk.
// time: random + brute; memory: O(n+m)
// constraint: small n, positive weights.
// usage: g++ -std=c++17 test_sp_kth.cpp && ./a.out

mt19937_64 rng(5);
int rnd(int l, int r) {
    uniform_int_distribution<int> dis(l, r);
    return dis(rng);
}

kth_walk ks;

vector<ll> kth_na(int n, const vector<vector<pll>> &g, int s, int e, int k) {
    vector<int> cnt(n + 1);
    priority_queue<pll, vector<pll>, greater<pll>> pq;
    pq.push({0, s});
    vector<ll> res;
    while (!pq.empty() && sz(res) < k) {
        auto [d, v] = pq.top();
        pq.pop();
        cnt[v]++;
        if (cnt[v] > k) continue;
        if (v == e) res.push_back(d);
        if (cnt[v] <= k)
            for (auto [w, to] : g[v]) pq.push({d + w, to});
    }
    return res;
}

void t_fix() {
    int n = 3;
    vector<vector<pll>> g(n + 1);
    g[1].push_back({1, 2});
    g[2].push_back({1, 3});
    ks.init(n);
    ks.add_edge(1, 2, 1);
    ks.add_edge(2, 3, 1);
    auto a = kth_na(n, g, 1, 3, 3);
    auto b = ks.run(1, 3, 3);
    assert(a == b);
}

void t_rnd() {
    for (int it = 0; it < 200; it++) {
        int n = rnd(2, 6);
        int m = rnd(0, n * (n - 1));
        vector<vector<pll>> g(n + 1);
        ks.init(n);
        for (int i = 0; i < m; i++) {
            int u = rnd(1, n), v = rnd(1, n);
            ll w = rnd(1, 5);
            g[u].push_back({w, v});
            ks.add_edge(u, v, w);
        }
        int s = rnd(1, n), e = rnd(1, n), k = rnd(1, 10);
        auto a = kth_na(n, g, s, e, k);
        auto b = ks.run(s, e, k);
        assert(a == b);
    }
}

int main() {
    t_fix();
    t_rnd();
    return 0;
}
