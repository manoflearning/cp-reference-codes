#include "../../src/1-ds/erasable_pq.cpp"

// what: tests for erase_pq (erasable pq).
// time: random + edge cases; memory: O(n)
// constraint: uses assert, fixed seed.
// usage: g++ -std=c++17 test_erasable_pq.cpp && ./a.out

mt19937_64 rng(1);
ll rnd(ll l, ll r) {
    uniform_int_distribution<ll> dis(l, r);
    return dis(rng);
}

ll pick_multiset(multiset<ll> &ms) {
    int idx = (int)rnd(0, (int)ms.size() - 1);
    auto it = ms.begin();
    advance(it, idx);
    return *it;
}

void test_edge_cases() {
    erase_pq<ll> pq;
    multiset<ll> ms;

    pq.push(5), ms.insert(5);
    pq.push(5), ms.insert(5);
    pq.push(3), ms.insert(3);
    assert(pq.top() == *prev(ms.end()));

    pq.erase(5), ms.erase(ms.find(5));
    assert(pq.top() == *prev(ms.end()));

    pq.pop(), ms.erase(prev(ms.end()));
    assert(pq.top() == *prev(ms.end()));

    pq.erase(3), ms.erase(ms.find(3));
    assert(ms.empty());
    assert(pq.empty());

    for (int i = 0; i < 5; i++) pq.push(-1), ms.insert(-1);
    for (int i = 0; i < 4; i++) pq.erase(-1), ms.erase(ms.find(-1));
    assert(pq.top() == *prev(ms.end()));
}

void test_randomized() {
    erase_pq<ll> pq;
    multiset<ll> ms;

    for (int it = 0; it < 3000; it++) {
        int op = ms.empty() ? 0 : (int)rnd(0, 3);
        if (op == 0) {
            ll x = rnd(-5, 5);
            pq.push(x), ms.insert(x);
        } else if (op == 1) {
            ll x = pick_multiset(ms);
            pq.erase(x), ms.erase(ms.find(x));
        } else if (op == 2) {
            pq.pop(), ms.erase(prev(ms.end()));
        } else {
            assert(pq.top() == *prev(ms.end()));
        }
        assert(pq.size() == (int)ms.size());
        if (ms.empty()) {
            assert(pq.empty());
        } else {
            assert(pq.top() == *prev(ms.end()));
        }
    }
}

int main() {
    test_edge_cases();
    test_randomized();
    return 0;
}
