#pragma once
#include "num.hpp"

// what: Chinese remainder theorem for possibly non-coprime mod (merge congruences).
// time: O(log mod) per merge; memory: O(1)
// constraint: mod > 0; lcm(mod1,mod2) must fit in ll; returns {-1,-1} if no solution.
// usage: pll x=crt::merge({r1,m1},{r2,m2}); // x = ret.fr (mod ret.sc)
struct crt {
    static pll norm(pll a) {
        // goal: normalize to 0 <= r < m
        if (a.sc <= 0) return {-1, -1};
        a.fr %= a.sc;
        if (a.fr < 0) a.fr += a.sc;
        return a;
    }
    static pll merge(pll a, pll b) {
        // result: x = ret.fr (mod ret.sc), or {-1,-1} if no solution.
        a = norm(a);
        b = norm(b);
        if (a.sc == -1 || b.sc == -1) return {-1, -1};
        if (a.sc == 1) return b;
        if (b.sc == 1) return a;

        ll m1 = a.sc, m2 = b.sc;
        ll r1 = a.fr, r2 = b.fr;
        ll g = euclid::gcd(m1, m2);
        if ((r2 - r1) % g) return {-1, -1};

        ll m1g = m1 / g, m2g = m2 / g;
        ll rhs = (r2 - r1) / g;
        rhs %= m2g;
        if (rhs < 0) rhs += m2g;
        ll inv = euclid::inv_mod(m1g % m2g, m2g);
        ll t = (ll)((__int128)rhs * inv % m2g);

        ll l = m1g * m2; // = lcm(m1,m2)
        ll r = (ll)(((__int128)r1 + (__int128)m1 * t) % l);
        if (r < 0) r += l;
        return {r, l};
    }
    static pll merge_all(const vector<pll> &cs) {
        pll cur = {0, 1};
        for (auto c : cs) cur = merge(cur, c);
        return cur;
    }
};
