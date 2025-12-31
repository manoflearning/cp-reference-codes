#pragma once
#include "../common/common.hpp"

// what: small matrix helper for modular multiply and fast exponentiation.
// time: multiply O(n*m*k); power O(log e * n^3); memory: O(n*m)
// constraint: mod > 0; dims must match for multiply.
// usage: matrix a(n,n,mod); auto r=matrix::power(a, e);
struct matrix {
    ll mod;
    vector<vector<ll>> a;

    matrix(int n = 0, int m = 0, ll mod_ = 1) : mod(mod_), a(n, vector<ll>(m, 0)) {}

    static matrix ident(int n, ll mod) {
        matrix r(n, n, mod);
        for (int i = 0; i < n; i++) r.a[i][i] = 1 % mod;
        return r;
    }

    matrix operator*(const matrix &o) const {
        int n = sz(a);
        int m = sz(o.a[0]);
        int k = sz(a[0]);
        matrix r(n, m, mod);
        for (int i = 0; i < n; i++) {
            for (int t = 0; t < k; t++) {
                if (a[i][t] == 0) continue;
                for (int j = 0; j < m; j++) {
                    ll add = (ll)((__int128)a[i][t] * o.a[t][j] % mod);
                    r.a[i][j] += add;
                    if (r.a[i][j] >= mod) r.a[i][j] -= mod;
                }
            }
        }
        return r;
    }

    static matrix power(matrix base, ll exp) {
        // goal: fast exponentiation.
        matrix res = ident(sz(base.a), base.mod);
        while (exp) {
            if (exp & 1) res = res * base;
            base = base * base;
            exp >>= 1;
        }
        return res;
    }
};
