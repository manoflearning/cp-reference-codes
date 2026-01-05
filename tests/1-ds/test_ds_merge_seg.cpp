#include "../../src/1-ds/ds_merge_seg.cpp"

// what: tests for merge_seg, merge_seg_it.
// time: random + edge cases; memory: O(n log n)
// constraint: uses assert, fixed seed.
// usage: g++ -std=c++17 test_ds_merge_seg.cpp && ./a.out

mt19937_64 rng(3);
ll rnd(ll l, ll r) {
    uniform_int_distribution<ll> dis(l, r);
    return dis(rng);
}

int count_greater(const vector<int> &a, int l, int r, int k) {
    int ret = 0;
    for (int i = l; i <= r; i++) ret += (a[i] > k);
    return ret;
}

void test_merge_sort_tree_basic() {
    vector<int> a = {0, 5};
    merge_seg st;
    st.build(a);
    assert(st.query(1, 1, 4) == 1);
    assert(st.query(1, 1, 5) == 0);
}

void test_merge_sort_tree_random() {
    int n = 60;
    vector<int> a(n + 1, 0);
    for (int i = 1; i <= n; i++) a[i] = (int)rnd(-10, 10);

    merge_seg st;
    st.build(a);

    for (int it = 0; it < 4000; it++) {
        int l = (int)rnd(1, n);
        int r = (int)rnd(l, n);
        int k = (int)rnd(-10, 10);
        assert(st.query(l, r, k) == count_greater(a, l, r, k));
    }
}

void test_merge_sort_tree_iter_basic() {
    vector<int> a = {0, 2};
    merge_seg_it st;
    st.build(a);
    assert(st.query(1, 1, 1) == 1);
    assert(st.query(1, 1, 2) == 0);
}

void test_merge_sort_tree_iter_random() {
    int n = 60;
    vector<int> a(n + 1, 0);
    for (int i = 1; i <= n; i++) a[i] = (int)rnd(-10, 10);

    merge_seg_it st;
    st.build(a);

    for (int it = 0; it < 4000; it++) {
        int l = (int)rnd(1, n);
        int r = (int)rnd(l, n);
        int k = (int)rnd(-10, 10);
        assert(st.query(l, r, k) == count_greater(a, l, r, k));
    }
}

int main() {
    test_merge_sort_tree_basic();
    test_merge_sort_tree_random();
    test_merge_sort_tree_iter_basic();
    test_merge_sort_tree_iter_random();
    return 0;
}
