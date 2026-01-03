#include "../../src/7-math/misc_sqrt.cpp"

// what: tests for sqrt_alg (divisors/prime factors on single integer).
// time: random + brute; memory: O(n)
// constraint: fixed seed.
// usage: g++ -std=c++17 test_misc_sqrt.cpp && ./a.out

mt19937_64 rng(14);
ll rnd_ll(ll l, ll r) {
    uniform_int_distribution<ll> dis(l, r);
    return dis(rng);
}

bool is_prime_ref(ll x) {
    if (x < 2) return 0;
    for (ll i = 2; i <= x / i; i++)
        if (x % i == 0) return 0;
    return 1;
}

vector<ll> div_ref(ll x) {
    vector<ll> d;
    for (ll i = 1; i <= x; i++)
        if (x % i == 0) d.pb(i);
    return d;
}

vector<ll> fac_ref(ll x) {
    vector<ll> p;
    for (ll i = 2; i <= x / i; i++) {
        while (x % i == 0) {
            p.pb(i);
            x /= i;
        }
    }
    if (x > 1) p.pb(x);
    return p;
}

int main() {
    assert(sqrt_alg::divisors(1) == vector<ll>({1}));
    assert(sqrt_alg::prime_fac(1).empty());
    assert(sqrt_alg::divisors(36) == vector<ll>({1, 2, 3, 4, 6, 9, 12, 18, 36}));
    assert(sqrt_alg::prime_fac(36) == vector<ll>({2, 2, 3, 3}));
    for (int it = 0; it < 1000; it++) {
        ll x = rnd_ll(1, 5000);
        auto d1 = sqrt_alg::divisors(x);
        auto d2 = div_ref(x);
        sort(all(d2));
        assert(d1 == d2);

        auto f1 = sqrt_alg::prime_fac(x);
        auto f2 = fac_ref(x);
        assert(f1 == f2);
        ll prod = 1;
        for (ll p : f1) {
            assert(is_prime_ref(p));
            prod *= p;
        }
        assert(prod == x);
    }
    return 0;
}
