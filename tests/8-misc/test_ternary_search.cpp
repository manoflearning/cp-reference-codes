#include "../../src/8-misc/ternary_search.cpp"

// what: tests for ternary search (int + real).
// time: random + brute; memory: O(1)
// constraint: unimodal functions.
// usage: g++ -std=c++17 test_ternary_search.cpp && ./a.out

ll f_int_max(ll x) {
    ll d = x - 7;
    return -d * d + 100;
}

ll f_int_min(ll x) {
    ll d = x + 3;
    return d * d + 5;
}

void test_int() {
    ll l = -100, r = 100;
    auto [x1, v1] = ternary_int_max(l, r, f_int_max);
    ll bx = l, bv = f_int_max(l);
    for (ll x = l + 1; x <= r; x++) {
        ll v = f_int_max(x);
        if (v > bv) bv = v, bx = x;
    }
    assert(x1 == bx && v1 == bv);

    auto [x2, v2] = ternary_int_min(l, r, f_int_min);
    bx = l, bv = f_int_min(l);
    for (ll x = l + 1; x <= r; x++) {
        ll v = f_int_min(x);
        if (v < bv) bv = v, bx = x;
    }
    assert(x2 == bx && v2 == bv);
}

void test_real() {
    auto f_min = [&](ld x) { return (x - 2.5L) * (x - 2.5L); };
    ld x = ternary_real_min(-10, 10, f_min);
    assert(fabsl(x - 2.5L) < 1e-6L);

    auto f_max = [&](ld x) { return -(x - 1.3L) * (x - 1.3L); };
    x = ternary_real_max(-5, 5, f_max);
    assert(fabsl(x - 1.3L) < 1e-6L);
}

int main() {
    test_int();
    test_real();
    return 0;
}
