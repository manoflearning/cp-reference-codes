#include "../../src/8-misc/fraction_data_type.cpp"

// what: tests for fraction (normalize, ops, comparisons).
// time: random + edge cases; memory: O(1)
// constraint: fixed seed, small values.
// usage: g++ -std=c++17 test_fraction_data_type.cpp && ./a.out

mt19937_64 rng(2);
ll rnd(ll l, ll r) {
    uniform_int_distribution<ll> dis(l, r);
    return dis(rng);
}

pair<ll, ll> norm_pair(ll n, ll d) {
    if (d < 0) n = -n, d = -d;
    ll g = fraction::gcd_ll(n, d);
    if (g) n /= g, d /= g;
    return {n, d};
}

void test_basic() {
    fraction a(1, 2), b(2, 4), c(-3, -6);
    assert(a == b);
    assert(a == c);
    fraction d(3, -9);
    assert(d.n == -1 && d.d == 3);
    fraction e(0, -5);
    assert(e.n == 0 && e.d == 1);
}

void test_ops_random() {
    for (int it = 0; it < 2000; it++) {
        ll a = rnd(-9, 9), b = rnd(1, 9);
        ll c = rnd(-9, 9), d = rnd(1, 9);
        if (c == 0) c = 1;
        if (rnd(0, 1)) b = -b;
        if (rnd(0, 1)) d = -d;
        fraction x(a, b), y(c, d);
        auto [xn, xd] = norm_pair(a, b);
        auto [yn, yd] = norm_pair(c, d);
        assert(x.n == xn && x.d == xd);
        assert(y.n == yn && y.d == yd);
        auto add = norm_pair(a * d + c * b, b * d);
        auto sub = norm_pair(a * d - c * b, b * d);
        auto mul = norm_pair(a * c, b * d);
        auto div = norm_pair(a * d, b * c);
        fraction xadd = x + y;
        fraction xsub = x - y;
        fraction xmul = x * y;
        fraction xdiv = x / y;
        assert(xadd.n == add.first && xadd.d == add.second);
        assert(xsub.n == sub.first && xsub.d == sub.second);
        assert(xmul.n == mul.first && xmul.d == mul.second);
        assert(xdiv.n == div.first && xdiv.d == div.second);
        bool lt = (__int128)xn * yd < (__int128)yn * xd;
        assert((x < y) == lt);
    }
}

int main() {
    test_basic();
    test_ops_random();
    return 0;
}
