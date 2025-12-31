#pragma once
#include "modint.hpp"

// what: nCr in O(r) without mod (safe for small n).
// time: O(r); memory: O(1)
// constraint: watch for overflow in ll.
// usage: ll v = comb_lr::ncr(n, r);
struct comb_lr {
    static ll ncr(int n, int r) {
        if (r < 0 || n < r) return 0;
        r = min(r, n - r);
        ll ret = 1;
        for (int i = 1; i <= r; i++) {
            ret = ret * (n - r + i) / i;
        }
        return ret;
    }
};

// what: nCr by Pascal DP.
// time: O(n^2) init, O(1) query; memory: O(n^2)
// constraint: small n only.
// usage: comb_dp cb; cb.init(n); ll v=cb.ncr(n,r);
struct comb_dp {
    int n;
    vector<vector<ll>> dp;

    void init(int n_) {
        // goal: build dp up to n.
        n = n_;
        dp.assign(n + 1, vector<ll>(n + 1, 0));
        for (int i = 0; i <= n; i++) {
            dp[i][0] = dp[i][i] = 1;
            for (int j = 1; j < i; j++) dp[i][j] = dp[i - 1][j - 1] + dp[i - 1][j];
        }
    }

    ll ncr(int n_, int r) const {
        if (r < 0 || n_ < r || n_ > n) return 0;
        return dp[n_][r];
    }
};

// what: nCr mod p with factorials.
// time: O(n) init, O(1) query; memory: O(n)
// constraint: mod is prime; 0 <= n <= precomputed N.
// usage: comb_mod cb; cb.init(n, mod); ll v=cb.ncr(n, r);
struct comb_mod {
    int n;
    ll mod;
    vector<ll> fac, ifac;

    void init(int n_, ll mod_) {
        // goal: precompute fac/ifac up to n.
        n = n_;
        mod = mod_;
        fac.assign(n + 1, 1);
        ifac.assign(n + 1, 1);
        for (int i = 1; i <= n; i++) fac[i] = (ll)((__int128)fac[i - 1] * i % mod);
        ifac[n] = pow_mod(fac[n], mod - 2, mod);
        for (int i = n; i >= 1; i--) ifac[i - 1] = (ll)((__int128)ifac[i] * i % mod);
    }

    ll ncr(int n_, int r) const {
        if (r < 0 || n_ < r || n_ > n) return 0;
        ll ret = (ll)((__int128)fac[n_] * ifac[r] % mod);
        ret = (ll)((__int128)ret * ifac[n_ - r] % mod);
        return ret;
    }
};
