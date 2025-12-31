#include "../../src/8-misc/kitamasa.cpp"

// what: tests for kitamasa linear recurrence.
// time: random + naive; memory: O(k)
// constraint: fixed seed, small n.
// usage: g++ -std=c++17 test_kitamasa.cpp && ./a.out

mt19937_64 rng(2);
ll rnd(ll l, ll r) {
    uniform_int_distribution<ll> dis(l, r);
    return dis(rng);
}

ll naive_rec(const vector<ll> &coef, const vector<ll> &init, ll n, ll mod) {
    int k = sz(coef);
    vector<ll> a = init;
    if (n < k) return mod_norm(a[n], mod);
    for (ll i = k; i <= n; i++) {
        ll v = 0;
        for (int j = 1; j <= k; j++) {
            v = mod_norm(v + (__int128)coef[j - 1] * a[i - j], mod);
        }
        a.push_back(v);
    }
    return a[n];
}

void test_random() {
    const ll mod = 1000000007LL;
    for (int it = 0; it < 200; it++) {
        int k = (int)rnd(1, 6);
        vector<ll> coef(k), init(k);
        for (int i = 0; i < k; i++) {
            coef[i] = rnd(0, mod - 1);
            init[i] = rnd(0, mod - 1);
        }
        ll n = rnd(0, 50);
        ll got = kitamasa(coef, init, n, mod);
        ll exp = naive_rec(coef, init, n, mod);
        assert(got == exp);
    }
}

int main() {
    test_random();
    return 0;
}
