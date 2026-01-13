#include "../../src/1-ds/ds_segtree_pst.cpp"

// what: tests for seg_pst (persistent segment tree).
// time: random + edge cases; memory: O(n log n)
// constraint: fixed seed.
// usage: g++ -std=c++17 test_ds_segtree_pst.cpp && ./a.out

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

void test_pst_basic() {
    int n = 3;
    seg_pst st;
    st.init(n);
    st.set(1, 1);
    st.set(2, 2);
    st.set(3, 3);
    st.set(2, 5);
    assert(st.query(1, 3, 3) == 6);
    assert(st.query(1, 3, 4) == 9);
}

void test_pst_random() {
    int n = 20;
    vector<vector<ll>> ver;
    seg_pst st;
    st.init(n);
    ver.push_back(vector<ll>(n + 1, 0));

    for (int it = 0; it < 2000; it++) {
        int op = (int)rnd(0, 1);
        if (op == 0) {
            int p = (int)rnd(1, n);
            ll v = rnd(-5, 5);
            vector<ll> nw = ver.back();
            nw[p] = v;
            ver.push_back(nw);
            st.set(p, v);
        } else {
            int id = (int)rnd(0, sz(ver) - 1);
            int l = (int)rnd(1, n);
            int r = (int)rnd(l, n);
            assert(st.query(l, r, id) == sum_range(ver[id], l, r));
        }
    }
}

void test_pst_kth_basic() {
    int n = 5;
    seg_pst st;
    st.init(n);
    st.set(1, 2);
    st.set(3, 1);
    st.set(4, 3);
    assert(st.kth(1, 3) == 1);
    assert(st.kth(2, 3) == 1);
    assert(st.kth(3, 3) == 3);
    assert(st.kth(6, 3) == 4);
    st.set(2, 4);
    assert(st.kth(3, 4) == 2);
    assert(st.kth(10, 4) == 4);
    st.set(4, 0);
    assert(st.kth(7, 5) == 3);
}

void test_pst_kth_random() {
    int n = 40;
    vector<vector<ll>> ver;
    seg_pst st;
    st.init(n);
    ver.push_back(vector<ll>(n + 1, 0));

    for (int it = 0; it < 2000; it++) {
        int op = (int)rnd(0, 1);
        if (op == 0) {
            int p = (int)rnd(1, n);
            ll v = rnd(0, 5);
            vector<ll> nw = ver.back();
            nw[p] = v;
            ver.push_back(nw);
            st.set(p, v);
        } else {
            int id = (int)rnd(0, sz(ver) - 1);
            ll tot = 0;
            for (int i = 1; i <= n; i++) tot += ver[id][i];
            if (tot == 0) continue;
            ll k = rnd(1, tot);
            assert(st.kth(k, id) == kth_naive_freq(ver[id], k));
            assert(st.kth(1, id) == kth_naive_freq(ver[id], 1));
            assert(st.kth(tot, id) == kth_naive_freq(ver[id], tot));
        }
    }
}

int main() {
    test_pst_basic();
    test_pst_random();
    test_pst_kth_basic();
    test_pst_kth_random();
    return 0;
}
