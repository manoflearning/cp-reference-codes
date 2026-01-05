#include "../../src/7-math/linalg_mat.cpp"

// what: tests for matrix multiplication/power.
// time: random + small; memory: O(n^2)
// constraint: small n, fixed seed.
// usage: g++ -std=c++17 test_linalg_mat.cpp && ./a.out

mt19937_64 rng(25);
int rnd_int(int l, int r) {
    uniform_int_distribution<int> dis(l, r);
    return dis(rng);
}

ll fib_ref(int n, ll mod) {
    ll a = 0, b = 1;
    for (int i = 0; i < n; i++) {
        ll c = (a + b) % mod;
        a = b;
        b = c;
    }
    return a;
}

vector<vector<ll>> mul_ref(const vector<vector<ll>> &a, const vector<vector<ll>> &b, ll mod) {
    int n = sz(a), m = sz(b[0]), k = sz(a[0]);
    vector<vector<ll>> r(n, vector<ll>(m, 0));
    for (int i = 0; i < n; i++)
        for (int t = 0; t < k; t++)
            for (int j = 0; j < m; j++) {
                r[i][j] = (r[i][j] + a[i][t] * b[t][j]) % mod;
            }
    return r;
}

int main() {
    const ll mod = 1000000007;
    matrix base(2, 2, mod);
    base.a = {{1, 1}, {1, 0}};
    for (int n = 0; n <= 20; n++) {
        auto r = matrix::power(base, n);
        ll f = fib_ref(n, mod);
        ll got = r.a[0][1];
        assert(got == f);
    }
    auto id = matrix::ident(3, mod);
    matrix a(3, 3, mod);
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++) a.a[i][j] = rnd_int(0, 10);
    auto prod = a * id;
    assert(prod.a == a.a);
    auto pow0 = matrix::power(a, 0);
    assert(pow0.a == id.a);

    for (int it = 0; it < 200; it++) {
        matrix x(3, 3, mod), y(3, 3, mod);
        for (int i = 0; i < 3; i++)
            for (int j = 0; j < 3; j++) {
                x.a[i][j] = rnd_int(0, 20);
                y.a[i][j] = rnd_int(0, 20);
            }
        auto ref = mul_ref(x.a, y.a, mod);
        auto got = x * y;
        assert(got.a == ref);
    }
    return 0;
}
