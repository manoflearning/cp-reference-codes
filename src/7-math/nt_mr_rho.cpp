#pragma once
#include "num.hpp"

// what: decide primality of a 64-bit integer using deterministic Miller-Rabin.
// time: O(k log n); memory: O(1)
// constraint: n fits in signed ll; uses __int128 mul.
// usage: if(miller_rabin::is_prime(n)) ...
struct miller_rabin {
    static ll mul(ll a, ll b, ll mod) { return (ll)((__int128)a * b % mod); }
    static ll pow_mod(ll a, ll e, ll mod) { return ::pow_mod(a, e, mod); }

    static bool is_prime(ll n) {
        if (n < 2) return 0;
        for (ll p : {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37}) {
            if (n == p) return 1;
            if (n % p == 0) return 0;
        }

        ll d = n - 1, s = 0;
        while ((d & 1) == 0) d >>= 1, s++;

        auto chk = [&](ll a) -> bool {
            if (a % n == 0) return 1;
            ll x = pow_mod(a, d, n);
            if (x == 1 || x == n - 1) return 1;
            for (int i = 1; i < s; i++) {
                x = mul(x, x, n);
                if (x == n - 1) return 1;
            }
            return 0;
        };

        // deterministic bases for 64-bit signed range (common CP set)
        for (ll a : {2, 325, 9375, 28178, 450775, 9780504, 1795265022})
            if (!chk(a)) return 0;
        return 1;
    }
};

// what: split a 64-bit integer into prime factors using randomized Pollard-Rho.
// time: fast in practice; memory: O(log n)
// constraint: randomized; uses miller_rabin.
// usage: auto f=pollard_rho::factor(n);
struct pollard_rho {
    static ll f(ll x, ll c, ll mod) { return (miller_rabin::mul(x, x, mod) + c) % mod; }

    static ll rho(ll n) {
        if ((n & 1) == 0) return 2;
        static mt19937_64 rng(712367);
        while (1) {
            ll c = uniform_int_distribution<ll>(1, n - 1)(rng);
            ll x = uniform_int_distribution<ll>(0, n - 1)(rng);
            ll y = x, d = 1;
            while (d == 1) {
                x = f(x, c, n);
                y = f(f(y, c, n), c, n);
                d = euclid::gcd(llabs(x - y), n);
            }
            if (d != n) return d;
        }
    }

    static void rec(ll n, vector<ll> &out) {
        if (n == 1) return;
        if (miller_rabin::is_prime(n)) {
            out.pb(n);
            return;
        }
        ll d = rho(n);
        rec(d, out);
        rec(n / d, out);
    }

    static vector<ll> factor(ll n) {
        // result: prime factors of |n| with repetition, sorted.
        vector<ll> out;
        if (n < 0) n = -n;
        if (n == 0) return out;
        rec(n, out);
        sort(all(out));
        return out;
    }
};
