#include "../../src/4-optimizations/flow_hk.cpp"

// what: tests for hk (Hopcroft-Karp).
// time: random + brute; memory: O(2^n)
// constraint: small n brute.
// usage: g++ -std=c++17 test_flow_hk.cpp && ./a.out

mt19937_64 rng(401);
int rnd(int l, int r) {
    uniform_int_distribution<int> dis(l, r);
    return dis(rng);
}

int brute_match(int n_l, int n_r, const vector<vector<int>> &g) {
    vector<vector<int>> dp(n_l + 1, vector<int>(1 << n_r, -1));
    function<int(int, int)> go = [&](int i, int mask) {
        if (i == n_l) return 0;
        int &ret = dp[i][mask];
        if (ret != -1) return ret;
        ret = go(i + 1, mask);
        for (int r : g[i])
            if (!(mask & (1 << r))) ret = max(ret, 1 + go(i + 1, mask | (1 << r)));
        return ret;
    };
    return go(0, 0);
}

void t_hk() {
    for (int it = 0; it < 300; it++) {
        int n_l = rnd(0, 10), n_r = rnd(0, 10);
        hk bm(n_l, n_r);
        vector<vector<int>> g(n_l);
        for (int l = 0; l < n_l; l++)
            for (int r = 0; r < n_r; r++)
                if (rnd(0, 1)) bm.add_edge(l, r), g[l].push_back(r);
        assert(bm.max_matching() == brute_match(n_l, n_r, g));
    }
}

int main() {
    t_hk();
    return 0;
}
