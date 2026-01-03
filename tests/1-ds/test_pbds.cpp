#include "../../src/1-ds/pbds.cpp"

// what: tests for pbds ordered set/multiset with order stats.
// time: random + edge cases; memory: O(n)
// constraint: uses assert, fixed seed.
// usage: g++ -std=c++17 test_pbds.cpp && ./a.out

mt19937_64 rng(11);
ll rnd(ll l, ll r) {
    uniform_int_distribution<ll> dis(l, r);
    return dis(rng);
}

ll kth_set(const set<ll> &s, int k) {
    auto it = s.begin();
    advance(it, k);
    return *it;
}

ll kth_multiset(const multiset<ll> &ms, int k) {
    auto it = ms.begin();
    advance(it, k);
    return *it;
}

void test_oset_basic() {
    oset s;
    s.insert(5);
    s.insert(1);
    s.insert(3);
    assert(s.order_of_key(1) == 0);
    assert(s.order_of_key(4) == 2);
    assert(*s.find_by_order(0) == 1);
    assert(*s.find_by_order(2) == 5);
}

void test_oset_random() {
    oset s;
    set<ll> st;
    for (int it = 0; it < 3000; it++) {
        int op = (int)rnd(0, 2);
        if (op == 0) {
            ll x = rnd(-10, 10);
            s.insert(x);
            st.insert(x);
        } else if (op == 1) {
            if (st.empty()) continue;
            ll x = kth_set(st, (int)rnd(0, sz(st) - 1));
            s.erase(x);
            st.erase(x);
        } else {
            ll x = rnd(-10, 10);
            assert((int)s.order_of_key(x) == (int)distance(st.begin(), st.lower_bound(x)));
            if (!st.empty()) {
                int k = (int)rnd(0, sz(st) - 1);
                assert(*s.find_by_order(k) == kth_set(st, k));
            }
        }
    }
}

void test_omset_basic() {
    omset s;
    m_insert(s, 2);
    m_insert(s, 2);
    m_insert(s, 5);
    assert(m_order(s, 2) == 0);
    assert(m_order(s, 5) == 2);
    assert(m_kth(s, 0) == 2);
    assert(m_kth(s, 1) == 2);
    m_erase(s, 2);
    assert(m_order(s, 5) == 1);
}

void test_omset_random() {
    omset s;
    multiset<ll> ms;
    for (int it = 0; it < 4000; it++) {
        int op = (int)rnd(0, 2);
        if (op == 0) {
            ll x = rnd(-5, 5);
            m_insert(s, x);
            ms.insert(x);
        } else if (op == 1) {
            if (ms.empty()) continue;
            ll x = kth_multiset(ms, (int)rnd(0, sz(ms) - 1));
            m_erase(s, x);
            ms.erase(ms.find(x));
        } else {
            ll x = rnd(-5, 5);
            assert(m_order(s, x) == (int)distance(ms.begin(), ms.lower_bound(x)));
            if (!ms.empty()) {
                int k = (int)rnd(0, sz(ms) - 1);
                assert(m_kth(s, k) == kth_multiset(ms, k));
            }
        }
    }
}

int main() {
    test_oset_basic();
    test_oset_random();
    test_omset_basic();
    test_omset_random();
    return 0;
}
