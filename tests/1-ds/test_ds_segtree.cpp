#include "../../src/1-ds/ds_segtree.cpp"

// what: tests for seg_tree, seg_tree_it, seg_tree_kth, seg_tree_lz, seg_sparse, seg_2d, seg2d_comp.
// time: random + edge cases; memory: O(n log n)
// constraint: uses assert, fixed seed.
// usage: g++ -std=c++17 test_ds_segtree.cpp && ./a.out

mt19937_64 rng(4);
ll rnd(ll l, ll r) {
    uniform_int_distribution<ll> dis(l, r);
    return dis(rng);
}

ll sum_range(const vector<ll> &a, int l, int r) {
    ll ret = 0;
    for (int i = l; i <= r; i++) ret += a[i];
    return ret;
}

int kth_naive_freq(const vector<ll> &a, ll k) {
    ll cur = 0;
    for (int i = 1; i < sz(a); i++) {
        cur += a[i];
        if (cur >= k) return i;
    }
    return -1;
}

void test_segt_basic() {
    vector<ll> a = {0, 3};
    seg_tree st;
    st.build(a);
    assert(st.query(1, 1) == 3);
    st.set(1, -2);
    assert(st.query(1, 1) == -2);
}

void test_segt_random() {
    int n = 50;
    vector<ll> a(n + 1, 0);
    for (int i = 1; i <= n; i++) a[i] = rnd(-5, 5);

    seg_tree st;
    st.build(a);

    for (int it = 0; it < 5000; it++) {
        int op = (int)rnd(0, 1);
        if (op == 0) {
            int p = (int)rnd(1, n);
            ll v = rnd(-5, 5);
            a[p] = v;
            st.set(p, v);
        } else {
            int l = (int)rnd(1, n);
            int r = (int)rnd(l, n);
            assert(st.query(l, r) == sum_range(a, l, r));
        }
    }
}

void test_segti_basic() {
    vector<ll> a = {0, 4};
    seg_tree_it st;
    st.build(a);
    assert(st.query(1, 1) == 4);
    st.set(1, 1);
    assert(st.query(1, 1) == 1);
}

void test_segti_random() {
    int n = 50;
    vector<ll> a(n + 1, 0);
    for (int i = 1; i <= n; i++) a[i] = rnd(-5, 5);

    seg_tree_it st;
    st.build(a);

    for (int it = 0; it < 5000; it++) {
        int op = (int)rnd(0, 1);
        if (op == 0) {
            int p = (int)rnd(1, n);
            ll v = rnd(-5, 5);
            a[p] = v;
            st.set(p, v);
        } else {
            int l = (int)rnd(1, n);
            int r = (int)rnd(l, n);
            assert(st.query(l, r) == sum_range(a, l, r));
        }
    }
}

void test_segk_basic() {
    int n = 3;
    seg_tree_kth st;
    st.init(n);
    st.add(1, 2);
    st.add(3, 1);
    assert(st.kth(1) == 1);
    assert(st.kth(2) == 1);
    assert(st.kth(3) == 3);
}

void test_segk_random() {
    int n = 40;
    vector<ll> a(n + 1, 0);
    seg_tree_kth st;
    st.init(n);

    for (int it = 0; it < 4000; it++) {
        int op = (int)rnd(0, 1);
        if (op == 0) {
            int p = (int)rnd(1, n);
            ll v = rnd(0, 3);
            a[p] += v;
            st.add(p, v);
        } else {
            ll tot = 0;
            for (int i = 1; i <= n; i++) tot += a[i];
            if (tot == 0) continue;
            ll k = rnd(1, tot);
            assert(st.kth(k) == kth_naive_freq(a, k));
        }
    }
}

void test_seglz_basic() {
    vector<ll> a = {0, 1, 2};
    seg_tree_lz st;
    st.build(a);
    st.add(1, 2, 3);
    assert(st.query(1, 2) == 1 + 2 + 6);
}

void test_seglz_random() {
    int n = 40;
    vector<ll> a(n + 1, 0);
    for (int i = 1; i <= n; i++) a[i] = rnd(-5, 5);

    seg_tree_lz st;
    st.build(a);

    for (int it = 0; it < 4000; it++) {
        int op = (int)rnd(0, 1);
        if (op == 0) {
            int l = (int)rnd(1, n);
            int r = (int)rnd(l, n);
            ll v = rnd(-3, 3);
            for (int i = l; i <= r; i++) a[i] += v;
            st.add(l, r, v);
        } else {
            int l = (int)rnd(1, n);
            int r = (int)rnd(l, n);
            assert(st.query(l, r) == sum_range(a, l, r));
        }
    }
}

void test_dyseg_basic() {
    seg_sparse st;
    st.add(MAXL, 5);
    st.add(MAXR, -2);
    assert(st.query(MAXL, MAXL) == 5);
    assert(st.query(MAXR, MAXR) == -2);
    assert(st.query(MAXL, MAXR) == 3);
}

void test_dyseg_random() {
    seg_sparse st;
    map<int, ll> mp;
    int lo = 1, hi = 1000;

    for (int it = 0; it < 4000; it++) {
        int op = (int)rnd(0, 1);
        if (op == 0) {
            int p = (int)rnd(lo, hi);
            ll v = rnd(-5, 5);
            mp[p] += v;
            st.add(p, v);
        } else {
            int l = (int)rnd(lo, hi);
            int r = (int)rnd(l, hi);
            ll ret = 0;
            for (auto &kv : mp)
                if (l <= kv.fr && kv.fr <= r) ret += kv.sc;
            assert(st.query(l, r) == ret);
        }
    }
}

ll sum_rect(const vector<vector<ll>> &a, int x1, int y1, int x2, int y2) {
    ll ret = 0;
    for (int i = x1; i <= x2; i++)
        for (int j = y1; j <= y2; j++) ret += a[i][j];
    return ret;
}

void test_seg2d_basic() {
    vector<vector<ll>> a = {{0, 0}, {0, 7}};
    seg_2d st;
    st.build(a);
    assert(st.query(1, 1, 1, 1) == 7);
    st.set(1, 1, -1);
    assert(st.query(1, 1, 1, 1) == -1);
}

void test_seg2d_random() {
    int n = 7;
    vector<vector<ll>> a(n + 1, vector<ll>(n + 1, 0));
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++) a[i][j] = rnd(-3, 3);

    seg_2d st;
    st.build(a);

    for (int it = 0; it < 3000; it++) {
        int op = (int)rnd(0, 1);
        if (op == 0) {
            int x = (int)rnd(1, n);
            int y = (int)rnd(1, n);
            ll v = rnd(-5, 5);
            a[x][y] = v;
            st.set(x, y, v);
        } else {
            int x1 = (int)rnd(1, n);
            int x2 = (int)rnd(x1, n);
            int y1 = (int)rnd(1, n);
            int y2 = (int)rnd(y1, n);
            assert(st.query(x1, x2, y1, y2) == sum_rect(a, x1, y1, x2, y2));
        }
    }
}

struct op2d {
    int type; // 0 = set, 1 = query
    int x1, x2, y1, y2;
    ll val;
};

void test_seg2dc_basic() {
    int n = 1;
    seg2d_comp st(n);
    vector<op2d> ops;
    ops.push_back({0, 1, 0, 1, 0, 5});
    ops.push_back({1, 1, 1, 1, 1, 0});
    ops.push_back({0, 1, 0, 1, 0, -2});
    ops.push_back({1, 1, 1, 1, 1, 0});

    for (auto &op : ops) {
        if (op.type == 0) st.mark_set(op.x1, op.y1);
        else st.mark_query(op.x1, op.x2, op.y1, op.y2);
    }
    st.prep();

    vector<vector<ll>> a(n + 1, vector<ll>(n + 1, 0));
    for (auto &op : ops) {
        if (op.type == 0) {
            a[op.x1][op.y1] = op.val;
            st.set(op.x1, op.y1, op.val);
        } else {
            ll got = st.query(op.x1, op.x2, op.y1, op.y2);
            ll exp = sum_rect(a, op.x1, op.y1, op.x2, op.y2);
            if (got != exp) {
                cerr << "seg2d_comp mismatch: "
                     << "x1=" << op.x1 << " x2=" << op.x2
                     << " y1=" << op.y1 << " y2=" << op.y2
                     << " got=" << got << " exp=" << exp << "\n";
                abort();
            }
        }
    }
}

void test_seg2dc_random() {
    int n = 6;
    seg2d_comp st(n);
    vector<op2d> ops;
    int q = 2000;
    for (int i = 0; i < q; i++) {
        int type = (int)rnd(0, 1);
        if (type == 0) {
            int x = (int)rnd(1, n);
            int y = (int)rnd(1, n);
            ll v = rnd(-5, 5);
            ops.push_back({0, x, 0, y, 0, v});
        } else {
            int x1 = (int)rnd(1, n);
            int x2 = (int)rnd(x1, n);
            int y1 = (int)rnd(1, n);
            int y2 = (int)rnd(y1, n);
            ops.push_back({1, x1, x2, y1, y2, 0});
        }
    }

    for (auto &op : ops) {
        if (op.type == 0) st.mark_set(op.x1, op.y1);
        else st.mark_query(op.x1, op.x2, op.y1, op.y2);
    }
    st.prep();

    vector<vector<ll>> a(n + 1, vector<ll>(n + 1, 0));
    for (auto &op : ops) {
        if (op.type == 0) {
            a[op.x1][op.y1] = op.val;
            st.set(op.x1, op.y1, op.val);
        } else {
            ll got = st.query(op.x1, op.x2, op.y1, op.y2);
            ll exp = sum_rect(a, op.x1, op.y1, op.x2, op.y2);
            if (got != exp) {
                cerr << "seg2d_comp mismatch: "
                     << "x1=" << op.x1 << " x2=" << op.x2
                     << " y1=" << op.y1 << " y2=" << op.y2
                     << " got=" << got << " exp=" << exp << "\n";
                abort();
            }
        }
    }
}

int main() {
    test_segt_basic();
    test_segt_random();
    test_segti_basic();
    test_segti_random();
    test_segk_basic();
    test_segk_random();
    test_seglz_basic();
    test_seglz_random();
    test_dyseg_basic();
    test_dyseg_random();
    test_seg2d_basic();
    test_seg2d_random();
    test_seg2dc_basic();
    test_seg2dc_random();
    return 0;
}
