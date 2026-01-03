#include "../../src/1-ds/fenwick_tree.cpp"

// what: tests for fenwick, fenw_range, fenw_2d.
// time: random + edge cases; memory: O(n^2)
// constraint: uses assert, fixed seed.
// usage: g++ -std=c++17 test_fenwick_tree.cpp && ./a.out

mt19937_64 rng(2);
ll rnd(ll l, ll r) {
    uniform_int_distribution<ll> dis(l, r);
    return dis(rng);
}

ll sum_1d(const vl &a, int l, int r) {
    ll ret = 0;
    for (int i = l; i <= r; i++) ret += a[i];
    return ret;
}

int kth_naive(const vl &a, ll k) {
    ll cur = 0;
    for (int i = 0; i < sz(a); i++) {
        cur += a[i];
        if (cur >= k) return i;
    }
    return -1;
}

ll sum_2d(const vvl &a, int x1, int y1, int x2, int y2) {
    ll ret = 0;
    for (int i = x1; i <= x2; i++)
        for (int j = y1; j <= y2; j++) ret += a[i][j];
    return ret;
}

void test_fenwick_basic() {
    fenwick fw;
    vl a = {5};
    fw.build(a);
    assert(fw.sum(0, 0) == 5);
    assert(fw.kth(1) == 0);
    fw.set(0, 0);
    assert(fw.sum(0, 0) == 0);
    fw.add(0, 7);
    assert(fw.sum(0, 0) == 7);
}

void test_fenwick_random() {
    int n = 50;
    vl a(n);
    for (int i = 0; i < n; i++) a[i] = rnd(0, 5);

    fenwick fw;
    fw.build(a);

    for (int it = 0; it < 5000; it++) {
        int op = (int)rnd(0, 3);
        if (op == 0) {
            int p = (int)rnd(0, n - 1);
            ll v = rnd(0, 5);
            a[p] += v;
            fw.add(p, v);
        } else if (op == 1) {
            int p = (int)rnd(0, n - 1);
            ll v = rnd(0, 10);
            a[p] = v;
            fw.set(p, v);
        } else if (op == 2) {
            int l = (int)rnd(0, n - 1);
            int r = (int)rnd(l, n - 1);
            assert(fw.sum(l, r) == sum_1d(a, l, r));
        } else {
            ll tot = 0;
            for (ll v : a) tot += v;
            if (tot == 0) continue;
            ll k = rnd(1, tot);
            assert(fw.kth(k) == kth_naive(a, k));
        }
    }
}

void test_fenwick_rp_basic() {
    fenw_range fw;
    fw.init(1);
    fw.add(1, 1, 5);
    assert(fw.get(1) == 5);
}

void test_fenwick_rp_random() {
    int n = 40;
    vl a(n + 1, 0);
    fenw_range fw;
    fw.init(n);

    for (int it = 0; it < 4000; it++) {
        int op = (int)rnd(0, 1);
        if (op == 0) {
            int l = (int)rnd(1, n);
            int r = (int)rnd(l, n);
            ll v = rnd(-5, 5);
            fw.add(l, r, v);
            for (int i = l; i <= r; i++) a[i] += v;
        } else {
            int p = (int)rnd(1, n);
            assert(fw.get(p) == a[p]);
        }
    }
}

void test_fenwick_2d_basic() {
    fenw_2d fw;
    vvl a = {{3}};
    fw.build(a);
    assert(fw.sum(0, 0, 0, 0) == 3);
    fw.set(0, 0, -2);
    assert(fw.sum(0, 0, 0, 0) == -2);
}

void test_fenwick_2d_random() {
    int n = 8, m = 7;
    vvl a(n, vl(m, 0));
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++) a[i][j] = rnd(-3, 3);

    fenw_2d fw;
    fw.build(a);

    for (int it = 0; it < 4000; it++) {
        int op = (int)rnd(0, 2);
        if (op == 0) {
            int x = (int)rnd(0, n - 1);
            int y = (int)rnd(0, m - 1);
            ll v = rnd(-3, 3);
            a[x][y] += v;
            fw.add(x, y, v);
        } else if (op == 1) {
            int x = (int)rnd(0, n - 1);
            int y = (int)rnd(0, m - 1);
            ll v = rnd(-5, 5);
            a[x][y] = v;
            fw.set(x, y, v);
        } else {
            int x1 = (int)rnd(0, n - 1);
            int x2 = (int)rnd(x1, n - 1);
            int y1 = (int)rnd(0, m - 1);
            int y2 = (int)rnd(y1, m - 1);
            assert(fw.sum(x1, y1, x2, y2) == sum_2d(a, x1, y1, x2, y2));
        }
    }
}

int main() {
    test_fenwick_basic();
    test_fenwick_random();
    test_fenwick_rp_basic();
    test_fenwick_rp_random();
    test_fenwick_2d_basic();
    test_fenwick_2d_random();
    return 0;
}
