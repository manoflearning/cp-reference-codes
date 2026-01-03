#include "../../src/7-math/nt_crt.cpp"

// what: tests for CRT merge/merge_all.
// time: random + brute; memory: O(1)
// constraint: fixed seed.
// usage: g++ -std=c++17 test_nt_crt.cpp && ./a.out

mt19937_64 rng(21);
ll rnd(ll l, ll r) {
    uniform_int_distribution<ll> dis(l, r);
    return dis(rng);
}

ll brute_crt(const vector<pll> &cs) {
    ll l = 1;
    for (auto [r, m] : cs) l = euclid::lcm(l, m);
    for (ll x = 0; x < l; x++) {
        bool ok = 1;
        for (auto [r, m] : cs) {
            ll rr = r % m;
            if (rr < 0) rr += m;
            if (x % m != rr) {
                ok = 0;
                break;
            }
        }
        if (ok) return x;
    }
    return -1;
}

void test_merge() {
    for (int it = 0; it < 2000; it++) {
        ll m1 = rnd(1, 50), m2 = rnd(1, 50);
        ll r1 = rnd(-50, 50), r2 = rnd(-50, 50);
        pll ans = crt::merge({r1, m1}, {r2, m2});
        ll brute = brute_crt({{r1, m1}, {r2, m2}});
        if (brute == -1) {
            assert(ans.sc == -1);
        } else {
            assert(ans.sc == euclid::lcm(m1, m2));
            assert(ans.fr == brute);
        }
    }
    pll t = crt::merge({-1, 5}, {1, 2});
    assert(t.sc == 10 && t.fr == 9);
    pll u = crt::merge({3, 1}, {7, 13});
    assert(u.sc == 13 && u.fr == 7);
    pll v = crt::merge({1, 2}, {0, 4});
    assert(v.sc == -1);
}

void test_merge_all() {
    for (int it = 0; it < 500; it++) {
        int k = (int)rnd(1, 4);
        vector<pll> cs;
        for (int i = 0; i < k; i++) {
            ll m = rnd(1, 30);
            ll r = rnd(-30, 30);
            cs.pb({r, m});
        }
        pll ans = crt::merge_all(cs);
        ll brute = brute_crt(cs);
        if (brute == -1) {
            assert(ans.sc == -1);
        } else {
            assert(ans.fr == brute);
        }
    }
    vector<pll> cs = {{1, 2}, {2, 3}, {3, 5}};
    pll a = crt::merge_all(cs);
    pll b = crt::merge(crt::merge(cs[0], cs[1]), cs[2]);
    assert(a == b);
}

int main() {
    test_merge();
    test_merge_all();
    return 0;
}
