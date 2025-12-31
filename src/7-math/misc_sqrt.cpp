#pragma once
#include "../common/common.hpp"

// what: list all divisors and prime factors of a single integer by sqrt trial division.
// time: O(sqrt x); memory: O(1) extra
// constraint: x >= 1 and fits in ll.
// usage: auto d=sqrt_alg::divisors(x); auto pf=sqrt_alg::prime_fac(x);
struct sqrt_alg {
    static vector<ll> divisors(ll x) {
        // result: sorted divisors of x.
        vector<ll> d;
        for (ll i = 1; i <= x / i; i++) {
            if (x % i) continue;
            d.push_back(i);
            if (i * i != x) d.push_back(x / i);
        }
        sort(all(d));
        return d;
    }

    static vector<ll> prime_fac(ll x) {
        // result: prime factors of x (with repetition).
        vector<ll> p;
        while ((x & 1) == 0) {
            p.push_back(2);
            x >>= 1;
        }
        for (ll i = 3; i <= x / i; i += 2) {
            while (x % i == 0) {
                p.push_back(i);
                x /= i;
            }
        }
        if (x > 1) p.push_back(x);
        return p;
    }
};
