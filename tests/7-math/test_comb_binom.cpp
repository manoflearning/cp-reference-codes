#include "../../src/7-math/comb_binom.cpp"

// what: tests for comb_lr/comb_dp/comb_mod.
// time: random + brute; memory: O(n^2)
// constraint: fixed seed.
// usage: g++ -std=c++17 test_comb_binom.cpp && ./a.out

mt19937_64 rng(15);
int rnd_int(int l, int r) {
    uniform_int_distribution<int> dis(l, r);
    return dis(rng);
}

ll ncr_ref(int n, int r) {
    if (r < 0 || n < r) return 0;
    r = min(r, n - r);
    __int128 ret = 1;
    for (int i = 1; i <= r; i++) ret = ret * (n - r + i) / i;
    return (ll)ret;
}

ll mul_ref(ll a, ll b, ll mod) { return (ll)((__int128)a * b % mod); }

ll ncr_mod_ref(int n, int r, ll mod) {
    if (r < 0 || n < r) return 0;
    r = min(r, n - r);
    ll ret = 1;
    for (int i = 1; i <= r; i++) {
        ret = mul_ref(ret, n - r + i, mod);
        ll inv = euclid::inv_mod(i, mod);
        ret = mul_ref(ret, inv, mod);
    }
    return ret;
}

void test_lr() {
    assert(comb_lr::ncr(5, -1) == 0);
    assert(comb_lr::ncr(5, 6) == 0);
    assert(comb_lr::ncr(0, 0) == 1);
    for (int i = 0; i < 500; i++) {
        int n = rnd_int(0, 30);
        int r = rnd_int(0, 30);
        assert(comb_lr::ncr(n, r) == ncr_ref(n, r));
        assert(comb_lr::ncr(n, r) == comb_lr::ncr(n, n - r));
    }
}

void test_dp() {
    comb_dp cb;
    cb.init(30);
    assert(cb.ncr(31, 1) == 0);
    for (int i = 0; i < 500; i++) {
        int n = rnd_int(0, 30);
        int r = rnd_int(0, 30);
        assert(cb.ncr(n, r) == ncr_ref(n, r));
        assert(cb.ncr(n, r) == cb.ncr(n, n - r));
    }
}

void test_mod() {
    ll mod = 1000000007;
    comb_mod cb;
    cb.init(2000, mod);
    for (int i = 0; i < 500; i++) {
        int n = rnd_int(0, 2000);
        int r = rnd_int(0, 2000);
        assert(cb.ncr(n, r) == ncr_mod_ref(n, r, mod));
    }
    comb_mod cb2;
    cb2.init(100, 101);
    for (int n = 0; n <= 20; n++)
        for (int r = 0; r <= n; r++) assert(cb2.ncr(n, r) == ncr_mod_ref(n, r, 101));
}

int main() {
    test_lr();
    test_dp();
    test_mod();
    return 0;
}
