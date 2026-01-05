#include "../../src/8-misc/num_frac.cpp"

// what: tests for fraction (normalize, ops, comparisons).
// time: random + edge cases; memory: O(1)
// constraint: fixed seed, small values.
// usage: g++ -std=c++17 test_num_frac.cpp && ./a.out

mt19937_64 rng(2);
ll rnd(ll l, ll r) {
    uniform_int_distribution<ll> dis(l, r);
    return dis(rng);
}

pll norm_pair(ll n, ll d) {
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
        assert(xadd.n == add.fr && xadd.d == add.sc);
        assert(xsub.n == sub.fr && xsub.d == sub.sc);
        assert(xmul.n == mul.fr && xmul.d == mul.sc);
        assert(xdiv.n == div.fr && xdiv.d == div.sc);
        bool lt = (__int128)xn * yd < (__int128)yn * xd;
        assert((x < y) == lt);
    }
}

int main() {
    test_basic();
    test_ops_random();
    return 0;
}
