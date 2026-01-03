#include "../../src/7-math/conv_fft.cpp"

// what: tests for fft_conv/ntt_conv.
// time: random + brute; memory: O(n)
// constraint: fixed seed, small sizes.
// usage: g++ -std=c++17 test_conv_fft.cpp && ./a.out

mt19937_64 rng(23);
int rnd_int(int l, int r) {
    uniform_int_distribution<int> dis(l, r);
    return dis(rng);
}

vector<ll> conv_ref(const vector<ll> &a, const vector<ll> &b) {
    int n = sz(a), m = sz(b);
    vector<ll> c(n + m - 1, 0);
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++) c[i + j] += a[i] * b[j];
    return c;
}

vector<ll> conv_mod_ref(const vector<ll> &a, const vector<ll> &b, ll mod) {
    int n = sz(a), m = sz(b);
    if (mod == 1) return vector<ll>(n + m - 1, 0);
    vector<ll> c(n + m - 1, 0);
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++) {
            ll v = (ll)((__int128)a[i] * b[j] % mod);
            c[i + j] += v;
            if (c[i + j] >= mod) c[i + j] %= mod;
        }
    for (auto &x : c) x %= mod;
    return c;
}

void test_fft() {
    assert(fft_conv::mul({}, {}).empty());
    for (int it = 0; it < 200; it++) {
        int n = rnd_int(1, 20);
        int m = rnd_int(1, 20);
        vector<ll> a(n), b(m);
        for (int i = 0; i < n; i++) a[i] = rnd_int(-5, 5);
        for (int i = 0; i < m; i++) b[i] = rnd_int(-5, 5);
        auto ref = conv_ref(a, b);
        auto got = fft_conv::mul(a, b);
        for (int i = 0; i < sz(ref); i++) assert(got[i] == ref[i]);
    }
    for (int it = 0; it < 100; it++) {
        int n = rnd_int(1, 60);
        int m = rnd_int(1, 60);
        vector<ll> a(n), b(m);
        for (int i = 0; i < n; i++) a[i] = rnd_int(-100, 100);
        for (int i = 0; i < m; i++) b[i] = rnd_int(-100, 100);
        auto ref = conv_ref(a, b);
        auto got = fft_conv::mul(a, b);
        for (int i = 0; i < sz(ref); i++) assert(got[i] == ref[i]);
    }
}

void test_fft_mod() {
    const ll mod = 1000000007;
    assert(fft_conv::mul_mod({}, {}, mod).empty());
    for (int it = 0; it < 200; it++) {
        int n = rnd_int(1, 20);
        int m = rnd_int(1, 20);
        vector<ll> a(n), b(m);
        for (int i = 0; i < n; i++) a[i] = rnd_int(0, 1000);
        for (int i = 0; i < m; i++) b[i] = rnd_int(0, 1000);
        auto ref = conv_mod_ref(a, b, mod);
        auto got = fft_conv::mul_mod(a, b, mod);
        for (int i = 0; i < sz(ref); i++) assert(got[i] == ref[i]);
    }
    auto all0 = fft_conv::mul_mod(vector<ll>(5, 0), vector<ll>(7, 0), mod);
    for (ll v : all0) assert(v == 0);
}

void test_ntt() {
    const ll mod = ntt_conv::MOD;
    assert(ntt_conv::mul({}, {}).empty());
    for (int it = 0; it < 200; it++) {
        int n = rnd_int(1, 20);
        int m = rnd_int(1, 20);
        vector<ll> a(n), b(m);
        for (int i = 0; i < n; i++) a[i] = rnd_int(0, mod - 1);
        for (int i = 0; i < m; i++) b[i] = rnd_int(0, mod - 1);
        auto ref = conv_mod_ref(a, b, mod);
        auto got = ntt_conv::mul(a, b);
        assert(sz(got) == sz(ref));
        for (int i = 0; i < sz(ref); i++) assert(got[i] == ref[i]);
    }
}

void test_ntt_any() {
    for (ll mod : {1LL, 1000000007LL, 1000000009LL, (ll)1e12 + 39}) {
        for (int it = 0; it < 200; it++) {
            int n = rnd_int(1, 20);
            int m = rnd_int(1, 20);
            vector<ll> a(n), b(m);
            for (int i = 0; i < n; i++) a[i] = rnd_int(0, 1000);
            for (int i = 0; i < m; i++) b[i] = rnd_int(0, 1000);
            auto ref = conv_mod_ref(a, b, mod);
            auto got = ntt_any::mul(a, b, mod);
            assert(sz(got) == sz(ref));
            for (int i = 0; i < sz(ref); i++) assert(got[i] == ref[i]);
        }
    }
}

int main() {
    test_fft();
    test_fft_mod();
    test_ntt();
    test_ntt_any();
    return 0;
}
