#include "../../src/7-math/comb_cat_der.cpp"

// what: tests for catalan_mod/derange_mod.
// time: small dp; memory: O(n)
// constraint: small n.
// usage: g++ -std=c++17 test_comb_cat_der.cpp && ./a.out

vl cat_ref(int n) {
    vl dp(n + 1, 0);
    dp[0] = 1;
    for (int i = 1; i <= n; i++)
        for (int j = 0; j < i; j++) dp[i] += dp[j] * dp[i - 1 - j];
    return dp;
}

vl der_ref(int n) {
    vl dp(max(3, n + 1), 0);
    dp[0] = 1;
    dp[1] = 0;
    dp[2] = 1;
    for (int i = 3; i <= n; i++) dp[i] = (i - 1) * (dp[i - 1] + dp[i - 2]);
    return dp;
}

int main() {
    for (ll mod : {1000000007LL, 998244353LL}) {
        int n = 20;
        auto cat = cat_ref(n);
        catalan_mod ct;
        ct.init(n, mod);
        for (int i = 0; i <= n; i++) assert(ct.catalan(i) == cat[i] % mod);

        auto der = der_ref(n);
        derange_mod de;
        de.init(n, mod);
        for (int i = 0; i <= n; i++) assert(de.get(i) == der[i] % mod);
        for (int i = 3; i <= n; i++) {
            ll lhs = de.get(i);
            ll rhs = (ll)(i - 1) * (de.get(i - 1) + de.get(i - 2)) % mod;
            assert(lhs == rhs);
        }
    }
    return 0;
}
