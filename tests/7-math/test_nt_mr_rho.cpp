#include "../../src/7-math/nt_mr_rho.cpp"

// what: tests for miller_rabin/pollard_rho.
// time: random + brute; memory: O(1)
// constraint: fixed seed.
// usage: g++ -std=c++17 test_nt_mr_rho.cpp && ./a.out

mt19937_64 rng(22);
ll rnd(ll l, ll r) {
    uniform_int_distribution<ll> dis(l, r);
    return dis(rng);
}

bool is_prime_ref(ll x) {
    if (x < 2) return 0;
    for (ll i = 2; i * i <= x; i++)
        if (x % i == 0) return 0;
    return 1;
}

vl fac_ref(ll x) {
    vl f;
    for (ll p = 2; p * p <= x; p++) {
        while (x % p == 0) {
            f.pb(p);
            x /= p;
        }
    }
    if (x > 1) f.pb(x);
    sort(all(f));
    return f;
}

void test_is_prime() {
    for (ll x = 1; x <= 1000; x++) {
        assert(miller_rabin::is_prime(x) == is_prime_ref(x));
    }
    for (ll x : {1000000007LL, 1000000009LL, 2305843009213693951LL}) {
        assert(miller_rabin::is_prime(x));
    }
    for (ll x : {0LL, 1LL, 4LL, 6LL, 8LL, 9LL, 15LL, 21LL, 25LL}) {
        assert(!miller_rabin::is_prime(x));
    }
    for (ll x : {561LL, 1105LL, 41041LL, 3215031751LL}) {
        assert(!miller_rabin::is_prime(x));
    }
}

void test_factor() {
    for (int it = 0; it < 200; it++) {
        ll x = rnd(2, 1000000000);
        auto f1 = pollard_rho::factor(x);
        auto f2 = fac_ref(x);
        assert(f1 == f2);
    }
    assert(pollard_rho::factor(1).empty());
    assert(pollard_rho::factor(0).empty());
    auto fneg = pollard_rho::factor(-12);
    assert(fneg == vl({2, 2, 3}));
    auto fp = pollard_rho::factor(1000000007LL);
    assert(fp == vl({1000000007LL}));
    ll p = 1000003, q = 1000033;
    auto fs = pollard_rho::factor(p * q);
    assert(fs == vl({p, q}));
    ll big = 1000000007LL * 1000000009LL;
    auto fb = pollard_rho::factor(big);
    assert(fb == vl({1000000007LL, 1000000009LL}));
}

int main() {
    test_is_prime();
    test_factor();
    return 0;
}
