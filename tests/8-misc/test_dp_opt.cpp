#include "../../src/8-misc/dp_opt.cpp"

// what: tests for dp optimizations (cht, knuth, dnc, slope trick).
// time: random + naive; memory: O(n^2)
// constraint: fixed seed, small n.
// usage: g++ -std=c++17 test_dp_opt.cpp && ./a.out

mt19937_64 rng(2);
ll rnd(ll l, ll r) {
    uniform_int_distribution<ll> dis(l, r);
    return dis(rng);
}

void test_cht() {
    int n = 200, q = 200;
    vl m(n), b(n);
    ll cur = 1000;
    for (int i = 0; i < n; i++) {
        cur -= rnd(0, 5);
        m[i] = cur;
        b[i] = rnd(-1000, 1000);
    }
    cht_mono ch;
    for (int i = 0; i < n; i++) ch.add_line(m[i], b[i]);
    for (int i = 0; i < q; i++) {
        ll x = rnd(-1000, 1000);
        ll best = (1LL << 62);
        for (int j = 0; j < n; j++) best = min(best, m[j] * x + b[j]);
        assert(ch.get(x) == best);
    }
}

void test_knuth() {
    int n = 40;
    vl a(n);
    for (int i = 0; i < n; i++) a[i] = rnd(0, 10);
    vl ps(n + 1, 0);
    for (int i = 0; i < n; i++) ps[i + 1] = ps[i] + a[i];
    auto cost = [&](int i, int j) { return ps[j + 1] - ps[i]; };
    const ll INF = (1LL << 62);
    vvl dp(n, vl(n, 0));
    for (int len = 2; len <= n; len++) {
        for (int i = 0; i + len - 1 < n; i++) {
            int j = i + len - 1;
            ll best = INF;
            for (int k = i; k < j; k++) {
                best = min(best, dp[i][k] + dp[k + 1][j] + cost(i, j));
            }
            dp[i][j] = best;
        }
    }
    knuth_opt ko;
    ko.build(n, cost);
    assert(ko.dp[0][n - 1] == dp[0][n - 1]);
}

void test_dnc() {
    int n = 50, k = 4;
    vl base(n, 0);
    auto cost = [&](int j, int i) {
        ll d = i - j;
        return d * d;
    };
    dnc_opt dc;
    dc.run(k, n, base, cost);
    const ll INF = (1LL << 62);
    vvl dp(k + 1, vl(n, INF));
    dp[0] = base;
    for (int g = 1; g <= k; g++) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j <= i; j++) {
                dp[g][i] = min(dp[g][i], dp[g - 1][j] + cost(j, i));
            }
        }
    }
    const vl &got = dc.dp();
    for (int i = 0; i < n; i++) assert(got[i] == dp[k][i]);
}

ll slope_naive(const vl &a) {
    int n = sz(a);
    ll mn = *min_element(all(a)) - n;
    ll mx = *max_element(all(a)) + n;
    int m = (int)(mx - mn + 1);
    const ll INF = (1LL << 62);
    vl dp_prev(m, INF), dp_cur(m, INF);
    for (int v = 0; v < m; v++) dp_prev[v] = llabs(a[0] - (mn + v));
    for (int i = 1; i < n; i++) {
        ll best = INF;
        for (int v = 0; v < m; v++) {
            if (v) best = min(best, dp_prev[v - 1]);
            dp_cur[v] = (best == INF ? INF : best + llabs(a[i] - (mn + v)));
        }
        dp_prev.swap(dp_cur);
    }
    return *min_element(all(dp_prev));
}

void test_slope_trick() {
    for (int it = 0; it < 200; it++) {
        int n = (int)rnd(1, 8);
        vl a(n);
        for (int i = 0; i < n; i++) a[i] = rnd(-5, 5);
        assert(slope_trick(a) == slope_naive(a));
    }
}

int main() {
    test_cht();
    test_knuth();
    test_dnc();
    test_slope_trick();
    return 0;
}
