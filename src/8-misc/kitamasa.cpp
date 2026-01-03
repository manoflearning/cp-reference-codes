#include "../common/common.hpp"

// what: compute n-th term of a linear recurrence using Kitamasa.
// time: O(k^2 log n); memory: O(k^2)
// constraint: coef.size() == init.size(); mod >= 1.
// usage: coef[i] for A_{n-1-i}; ll an = kitamasa(coef, init, n, mod);
using poly = vl;

ll mod_norm(ll x, ll mod) {
    x %= mod;
    if (x < 0) x += mod;
    return x;
}

poly poly_mul(const poly &a, const poly &b, ll mod) {
    poly ret(sz(a) + sz(b) - 1, 0);
    for (int i = 0; i < sz(a); i++) {
        for (int j = 0; j < sz(b); j++) {
            ret[i + j] = mod_norm(ret[i + j] + (__int128)a[i] * b[j], mod);
        }
    }
    return ret;
}

poly poly_div(const poly &a, const poly &f, ll mod) {
    // goal: reduce a(x) mod f(x), where f is monic
    poly ret = a;
    for (int i = sz(ret) - 1; i >= sz(f) - 1; i--) {
        if (ret[i] == 0) continue;
        for (int j = 0; j < sz(f); j++) {
            int idx = i + j - sz(f) + 1;
            ret[idx] = mod_norm(ret[idx] - (__int128)ret[i] * f[j], mod);
        }
    }
    ret.resize(sz(f) - 1);
    return ret;
}

ll kitamasa(const vl &coef, const vl &init, ll n, ll mod) {
    int k = sz(coef);
    assert(k == sz(init));
    if (n < k) return mod_norm(init[n], mod);
    poly d = {1};    // result
    poly x = {0, 1}; // x^(2^i)
    poly f(k + 1, 0);
    f.back() = 1;
    for (int i = 0; i < k; i++) f[k - 1 - i] = mod_norm(-coef[i], mod);
    while (n) {
        if (n & 1) d = poly_div(poly_mul(d, x, mod), f, mod);
        n >>= 1;
        x = poly_div(poly_mul(x, x, mod), f, mod);
    }
    ll ret = 0;
    for (int i = 0; i < k; i++) {
        ret = mod_norm(ret + (__int128)init[i] * d[i], mod);
    }
    return ret;
}
