#include "../../src/7-math/linalg_gauss.cpp"

// what: tests for gauss_real/gauss_mod/gauss_xor.
// time: random + brute; memory: O(n^2)
// constraint: fixed seed, small sizes.
// usage: g++ -std=c++17 test_linalg_gauss.cpp && ./a.out

mt19937_64 rng(24);
int rnd_int(int l, int r) {
    uniform_int_distribution<int> dis(l, r);
    return dis(rng);
}

void test_gauss_real() {
    vector<vector<ld>> a = {
        {2, 1, 1},
        {1, 3, 2},
        {1, 0, 0},
    };
    auto orig = a;
    assert(gauss_real::inv(a));
    int n = sz(a);
    vector<vector<ld>> prod(n, vector<ld>(n, 0));
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            for (int k = 0; k < n; k++) prod[i][j] += orig[i][k] * a[k][j];
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            assert(fabsl(prod[i][j] - (i == j)) < 1e-9);

    vector<vector<ld>> b = {
        {1, 2},
        {2, 4},
    };
    assert(!gauss_real::inv(b));
}

void test_gauss_mod() {
    int n = 6, m = 6;
    int mod = 101;
    vvi A(n, vi(m));
    vi x(m), b(n);
    for (int i = 0; i < m; i++) x[i] = rnd_int(0, mod - 1);
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++) A[i][j] = rnd_int(0, mod - 1);
    for (int i = 0; i < n; i++) {
        ll sum = 0;
        for (int j = 0; j < m; j++) sum += (ll)A[i][j] * x[j];
        b[i] = sum % mod;
    }
    vvi aug(n, vi(m + 1));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) aug[i][j] = A[i][j];
        aug[i][m] = b[i];
    }
    auto sol = gauss_mod::solve(aug, mod);
    assert(!sol.empty());
    for (int i = 0; i < n; i++) {
        ll sum = 0;
        for (int j = 0; j < m; j++) sum += (ll)A[i][j] * sol[j];
        assert(sum % mod == b[i]);
    }

    vvi bad = {
        {1, 0, 0},
        {1, 0, 1},
    };
    auto no = gauss_mod::solve(bad, 5);
    assert(no.empty());
}

void test_gauss_xor() {
    int n = 40, m = 20;
    vi x(m);
    for (int i = 0; i < m; i++) x[i] = rnd_int(0, 1);
    vector<bitset<GAUSS_BSZ>> aug(n);
    for (int i = 0; i < n; i++) {
        int rhs = 0;
        for (int j = 0; j < m; j++) {
            int v = rnd_int(0, 1);
            if (v) aug[i].set(j);
            rhs ^= (v & x[j]);
        }
        if (rhs) aug[i].set(m);
    }
    auto sol = gauss_xor::solve(aug, m);
    assert(!sol.empty());
    for (int i = 0; i < n; i++) {
        int rhs = 0;
        for (int j = 0; j < m; j++)
            if (aug[i].test(j)) rhs ^= sol[j];
        assert(rhs == (int)aug[i].test(m));
    }

    vector<bitset<GAUSS_BSZ>> bad(2);
    bad[0].set(0);
    bad[1].set(0);
    bad[1].set(1);
    auto sol2 = gauss_xor::solve(bad, 1);
    assert(sol2.empty());
}

int main() {
    test_gauss_real();
    test_gauss_mod();
    test_gauss_xor();
    return 0;
}
