#include "../../src/8-misc/simd.cpp"

// what: tests for SIMD snippets (i32 + f32).
// time: random + naive; memory: O(n)
// constraint: compile with -mavx2; fixed seed.
// usage: g++ -std=c++17 -mavx2 test_simd.cpp && ./a.out

mt19937_64 rng(2);
int rnd_int(int l, int r) {
    uniform_int_distribution<int> dis(l, r);
    return dis(rng);
}

void test_i32() {
    int n = 257;
    vector<int> a(n), b(n), c(n), d(n);
    for (int i = 0; i < n; i++) {
        a[i] = rnd_int(-1000, 1000);
        b[i] = rnd_int(-1000, 1000);
    }
    simd_i32::add(a.data(), b.data(), c.data(), n);
    for (int i = 0; i < n; i++) d[i] = a[i] + b[i];
    assert(c == d);

    ll s1 = simd_i32::sum(a.data(), n);
    ll s2 = 0;
    for (int i = 0; i < n; i++) s2 += a[i];
    assert(s1 == s2);

    for (int it = 0; it < 50; it++) {
        int l = rnd_int(0, n - 1);
        int r = rnd_int(l, n - 1);
        int mn = INT_MAX;
        for (int i = l; i <= r; i++) mn = min(mn, a[i]);
        assert(simd_i32::range_min(a.data(), l, r) == mn);
    }

    int v = a[rnd_int(0, n - 1)];
    int c1 = simd_i32::count_eq(a.data(), n, v);
    int c2 = 0;
    for (int i = 0; i < n; i++) c2 += (a[i] == v);
    assert(c1 == c2);
}

void test_f32() {
    int n = 128;
    vector<float> a(n), b(n), c(n);
    for (int i = 0; i < n; i++) {
        a[i] = (float)rnd_int(-5, 5);
        b[i] = (float)rnd_int(-5, 5);
        c[i] = a[i];
    }
    simd_f32::add_inplace(c.data(), b.data(), n);
    for (int i = 0; i < n; i++) assert(c[i] == a[i] + b[i]);

    float d1 = simd_f32::dot(a.data(), b.data(), n);
    float d2 = 0.0f;
    for (int i = 0; i < n; i++) d2 += a[i] * b[i];
    assert(fabs(d1 - d2) < 1e-3f);
}

int main() {
    test_i32();
    test_f32();
    return 0;
}
