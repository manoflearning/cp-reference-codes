#pragma once
#include "comb_binom.cpp"

// what: precompute Catalan numbers modulo a prime.
// time: O(n) init, O(1) query; memory: O(n)
// constraint: mod is prime; n < mod (so inv(n+1) exists).
// usage: catalan_mod ct; ct.init(n, mod); ll v=ct.catalan(k);
struct catalan_mod {
    comb_mod cb;
    ll mod;

    void init(int n, ll mod_) {
        // goal: precompute factorials up to 2n.
        mod = mod_;
        cb.init(2 * n, mod);
    }

    ll catalan(int n) const {
        ll ret = cb.ncr(2 * n, n);
        ll inv = euclid::inv_mod(n + 1, mod);
        return (ll)((__int128)ret * inv % mod);
    }
};

// what: precompute derangement numbers modulo mod.
// time: O(n) init, O(1) query; memory: O(n)
// constraint: mod > 1.
// usage: derange_mod de; de.init(n, mod); ll v=de.get(k);
struct derange_mod {
    ll mod;
    vector<ll> dp;

    void init(int n, ll mod_) {
        // goal: precompute derangements up to n.
        mod = mod_;
        dp.assign(max(3, n + 1), 0);
        dp[0] = 1;
        dp[1] = 0;
        dp[2] = 1 % mod;
        for (int i = 3; i <= n; i++) {
            ll sum = (dp[i - 1] + dp[i - 2]) % mod;
            dp[i] = (ll)((__int128)(i - 1) * sum % mod);
        }
    }

    ll get(int n) const { return dp[n]; }
};
