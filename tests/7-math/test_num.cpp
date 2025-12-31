#include "../../src/7-math/num.hpp"

// what: tests for euclid/pow_mod.
// time: random + brute; memory: O(1)
// constraint: fixed seed.
// usage: g++ -std=c++17 test_num.cpp && ./a.out

mt19937_64 rng(11);
ll rnd(ll l, ll r) {
    uniform_int_distribution<ll> dis(l, r);
    return dis(rng);
}

ll mod_norm(ll a, ll mod) {
    a %= mod;
    if (a < 0) a += mod;
    return a;
}

ll mul_ref(ll a, ll b, ll mod) { return (ll)((__int128)mod_norm(a, mod) * mod_norm(b, mod) % mod); }

ll gcd_ref(ll a, ll b) {
    a = llabs(a);
    b = llabs(b);
    while (b) {
        ll t = a % b;
        a = b;
        b = t;
    }
    return a;
}

ll pow_ref(ll a, ll e, ll mod) {
    a %= mod;
    if (a < 0) a += mod;
    ll r = 1 % mod;
    for (ll i = 0; i < e; i++) r = (ll)((__int128)r * a % mod);
    return r;
}

void test_gcd_lcm_edge() {
    assert(euclid::gcd(0, 0) == 0);
    assert(euclid::gcd(0, 5) == 5);
    assert(euclid::gcd(-7, 0) == 7);
    assert(euclid::lcm(0, 0) == 0);
    assert(euclid::lcm(0, 7) == 0);
    assert(euclid::lcm(-3, 5) == 15);
}

void test_gcd_lcm() {
    for (int i = 0; i < 2000; i++) {
        ll a = rnd(-100000, 100000);
        ll b = rnd(-100000, 100000);
        ll g = euclid::gcd(a, b);
        assert(g == gcd_ref(a, b));
        ll l = euclid::lcm(a, b);
        if (a == 0 || b == 0) {
            assert(l == 0);
        } else {
            __int128 prod = (__int128)a / g * b;
            if (prod < 0) prod = -prod;
            assert((__int128)l == prod);
        }
    }
}

void test_egcd() {
    for (int i = 0; i < 2000; i++) {
        ll a = rnd(-100000, 100000);
        ll b = rnd(-100000, 100000);
        auto res = euclid::egcd(a, b);
        ll x = res.fr.fr, y = res.fr.sc, g = res.sc;
        assert(a * x + b * y == g);
        assert(g == euclid::gcd(a, b));
    }
}

void test_inv() {
    ll mod = 1000003;
    for (int i = 0; i < 2000; i++) {
        ll a = rnd(1, mod - 1);
        ll inv = euclid::inv_mod(a, mod);
        assert(inv != -1);
        assert(mul_ref(a, inv, mod) == 1);
    }
    ll inv_neg = euclid::inv_mod(-3, 11);
    assert(inv_neg != -1);
    assert(mul_ref(mod_norm(-3, 11), inv_neg, 11) == 1);
    ll bad = euclid::inv_mod(10, 1000);
    assert(bad == -1);
}

void test_lin_cong() {
    ll mod = 97;
    for (int i = 0; i < 500; i++) {
        ll a = rnd(0, mod - 1);
        ll b = rnd(0, mod - 1);
        ll x = euclid::lin_cong(a, b, mod);
        ll brute = -1;
        for (ll t = 0; t < mod; t++) {
            if ((a * t - b) % mod == 0) {
                brute = t;
                break;
            }
        }
        if (brute == -1) {
            assert(x == -1);
        } else {
            assert((a * x - b) % mod == 0);
        }
    }
    assert(euclid::lin_cong(2, 1, 4) == -1);
}

void test_pow_mod() {
    ll mod = 1000000007;
    assert(mod_norm(-1, mod) == mod - 1);
    assert(mod_norm(mod + 2, mod) == 2);
    for (int i = 0; i < 2000; i++) {
        ll a = rnd(0, mod - 1);
        ll b = rnd(0, mod - 1);
        ll e = rnd(0, 50);
        assert(mul_ref(a, b, mod) == (ll)((__int128)a * b % mod));
        assert(pow_mod(a, e, mod) == pow_ref(a, e, mod));
    }
    for (int i = 0; i < 2000; i++) {
        ll a = rnd(-mod, mod);
        ll e = rnd(0, 50);
        assert(pow_mod(a, e, mod) == pow_ref(a, e, mod));
    }
    for (int i = 0; i < 2000; i++) {
        ll a = rnd(0, mod - 1);
        ll e1 = rnd(0, 1000);
        ll e2 = rnd(0, 1000);
        ll p1 = pow_mod(a, e1, mod);
        ll p2 = pow_mod(a, e2, mod);
        ll p12 = pow_mod(a, e1 + e2, mod);
        assert(mul_ref(p1, p2, mod) == p12);
    }
    assert(pow_mod(5, 0, 1) == 0);
}

int main() {
    test_gcd_lcm_edge();
    test_gcd_lcm();
    test_egcd();
    test_inv();
    test_lin_cong();
    test_pow_mod();
    return 0;
}
