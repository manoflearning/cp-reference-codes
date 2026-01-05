#include "../../src/4-optimizations/assign_hung.cpp"

// what: tests for hungarian (min assignment).
// time: random + brute; memory: O(1)
// constraint: small n,m.
// usage: g++ -std=c++17 test_assign_hung.cpp && ./a.out

mt19937_64 rng(402);
int rnd(int l, int r) {
    uniform_int_distribution<int> dis(l, r);
    return dis(rng);
}

pair<ll, vector<int>> brute(int n, int m, const vector<vector<ll>> &a) {
    ll best = (1LL << 62);
    vector<int> best_m(n + 1, 0);
    vector<int> cur(n + 1, 0);
    vector<char> used(m + 1, 0);
    function<void(int, ll)> dfs = [&](int i, ll cost) {
        if (i == n + 1) {
            if (cost < best) best = cost, best_m = cur;
            return;
        }
        for (int j = 1; j <= m; j++) {
            if (used[j]) continue;
            used[j] = 1;
            cur[i] = j;
            dfs(i + 1, cost + a[i][j]);
            used[j] = 0;
        }
    };
    dfs(1, 0);
    return {best, best_m};
}

void t_fix() {
    int n = 1, m = 1;
    vector<vector<ll>> a(n + 1, vector<ll>(m + 1, 0));
    a[1][1] = 7;
    hungarian hu;
    auto [cost, match_l] = hu.run(n, m, a);
    assert(cost == 7);
    assert(match_l[1] == 1);
}

void t_rnd() {
    for (int it = 0; it < 200; it++) {
        int n = rnd(1, 6);
        int m = rnd(n, 7);
        vector<vector<ll>> a(n + 1, vector<ll>(m + 1, 0));
        for (int i = 1; i <= n; i++)
            for (int j = 1; j <= m; j++) a[i][j] = rnd(-5, 7);
        hungarian hu;
        auto got = hu.run(n, m, a);
        auto exp = brute(n, m, a);
        assert(got.fr == exp.fr);
        vector<char> used(m + 1, 0);
        ll sum = 0;
        for (int i = 1; i <= n; i++) {
            int j = got.sc[i];
            assert(1 <= j && j <= m);
            assert(!used[j]);
            used[j] = 1;
            sum += a[i][j];
        }
        assert(sum == got.fr);
    }
}

int main() {
    t_fix();
    t_rnd();
    return 0;
}
