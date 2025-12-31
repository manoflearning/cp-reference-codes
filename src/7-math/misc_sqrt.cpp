#pragma once
#include "../common/common.hpp"

// what: sqrt-time number theory basics (divisors, prime factorization).
// time: O(sqrt x); memory: O(1) extra
// constraint: x >= 1.
// usage: auto d=sqrt_alg::divisors(x); auto pf=sqrt_alg::prime_fac(x);
struct sqrt_alg {
    static vector<int> divisors(int x) {
        // result: sorted divisors of x.
        vector<int> d;
        for (int i = 1; 1LL * i * i <= x; i++) {
            if (x % i) continue;
            d.push_back(i);
            if (i * i != x) d.push_back(x / i);
        }
        sort(all(d));
        return d;
    }

    static vector<int> prime_fac(int x) {
        // result: prime factors of x (with repetition).
        vector<int> p;
        while ((x & 1) == 0) {
            p.push_back(2);
            x >>= 1;
        }
        for (int i = 3; 1LL * i * i <= x; i += 2) {
            while (x % i == 0) {
                p.push_back(i);
                x /= i;
            }
        }
        if (x > 1) p.push_back(x);
        return p;
    }
};
