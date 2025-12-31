#include "../../src/7-math/modint.hpp"

// what: tests for modint (static + dynamic).
// time: random + brute; memory: O(1)
// constraint: fixed seed.
// usage: g++ -std=c++17 test_modint.cpp && ./a.out

mt19937_64 rng(12);
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

void test_static() {
    constexpr ll MOD = 1000000007;
    using mint = modint<MOD>;
    for (int i = 0; i < 2000; i++) {
        ll a = rnd(-MOD, MOD);
        ll b = rnd(-MOD, MOD);
        mint x = a, y = b;
        assert(ll(x + y) == mod_norm(a + b, MOD));
        assert(ll(x - y) == mod_norm(a - b, MOD));
        assert(ll(x * y) == mul_ref(a, b, MOD));
    }
    for (int i = 0; i < 2000; i++) {
        ll a = rnd(1, MOD - 1);
        mint x = a;
        mint inv = x.inv();
        assert(ll(x * inv) == 1);
        ll e = rnd(0, 60);
        assert(ll(x.pow(e)) == pow_mod(a, e, MOD));
    }
    using mint2 = modint<2>;
    for (int i = 0; i < 2000; i++) {
        ll a = rnd(-10, 10);
        ll b = rnd(-10, 10);
        mint2 x = a, y = b;
        ll xa = mod_norm(a, 2);
        ll xb = mod_norm(b, 2);
        assert(ll(x + y) == (xa + xb) % 2);
        assert(ll(x * y) == (xa * xb) % 2);
    }
    mint2 one = 1;
    assert(ll(one.inv()) == 1);
}

void test_dyn() {
    using dm = dyn_modint<0>;
    ll mod = 998244353;
    dm::set_mod(mod);
    for (int i = 0; i < 2000; i++) {
        ll a = rnd(-mod, mod);
        ll b = rnd(-mod, mod);
        dm x = a, y = b;
        assert(ll(x + y) == mod_norm(a + b, mod));
        assert(ll(x - y) == mod_norm(a - b, mod));
        assert(ll(x * y) == mul_ref(a, b, mod));
    }
    for (int i = 0; i < 2000; i++) {
        ll a = rnd(1, mod - 1);
        dm x = a;
        dm inv = x.inv();
        assert(ll(x * inv) == 1);
        ll e = rnd(0, 60);
        assert(ll(x.pow(e)) == pow_mod(a, e, mod));
    }

    using dm2 = dyn_modint<1>;
    dm2::set_mod(7);
    dm2 a = 5, b = 3;
    assert(ll(a + b) == 1);
    dm2::set_mod(11);
    dm2 c = 5, d = 3;
    assert(ll(c + d) == 8);

    dm::set_mod(1);
    dm z = 10;
    assert(ll(z + z) == 0);
    assert(ll(z * z) == 0);
}

int main() {
    test_static();
    test_dyn();
    return 0;
}
