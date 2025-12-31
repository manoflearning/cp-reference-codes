#pragma once

#include "../common/common.hpp"

// what: extended euclid toolkit.
// time: O(log n); memory: O(1)
// constraint: works for any ll.
// usage: auto eg=euclid::egcd(a,b); ll inv=euclid::inv_mod(a,mod);
struct euclid {
    static ll gcd(ll a, ll b) {
        if (a < 0) a = -a;
        if (b < 0) b = -b;
        while (b) {
            ll t = a % b;
            a = b;
            b = t;
        }
        return a;
    }
    static ll lcm(ll a, ll b) {
        if (!a || !b) return 0;
        ll v = a / gcd(a, b) * b;
        if (v < 0) v = -v;
        return v;
    }

    static pair<pll, ll> egcd(ll a, ll b) {
        // result: {{x, y}, g} s.t. a*x + b*y = g = gcd(a, b)
        ll s = 0, os = 1;
        ll t = 1, ot = 0;
        ll r = b, orr = a;
        while (r) {
            ll q = orr / r;
            ll nr = orr - q * r;
            orr = r;
            r = nr;
            ll ns = os - q * s;
            os = s;
            s = ns;
            ll nt = ot - q * t;
            ot = t;
            t = nt;
        }
        if (orr < 0) {
            orr = -orr;
            os = -os;
            ot = -ot;
        }
        return {{os, ot}, orr};
    }

    static ll inv_mod(ll a, ll mod) {
        // result: x in [0, mod) s.t. a*x = 1 (mod mod), or -1 if not invertible.
        a %= mod;
        if (a < 0) a += mod;
        auto res = egcd(a, mod);
        if (res.sc != 1) return -1;
        ll x = res.fr.fr % mod;
        if (x < 0) x += mod;
        return x;
    }

    static ll lin_cong(ll a, ll b, ll mod) {
        // what: solve a*x = b (mod mod).
        // result: one x in [0, mod) if exists, else -1.
        auto res = egcd(a, mod);
        ll g = res.sc;
        if (b % g) return -1;
        ll x = (ll)((__int128)res.fr.fr * (b / g) % mod);
        if (x < 0) x += mod;
        return x;
    }
};

// what: modular exponentiation.
// time: O(log e); memory: O(1)
// constraint: mod > 0.
// usage: ll p=pow_mod(a,e,mod);
inline ll pow_mod(ll a, ll e, ll mod) {
    ll r = 1 % mod;
    a %= mod;
    if (a < 0) a += mod;
    while (e) {
        if (e & 1) r = (ll)((__int128)r * a % mod);
        a = (ll)((__int128)a * a % mod);
        e >>= 1;
    }
    return r;
}
