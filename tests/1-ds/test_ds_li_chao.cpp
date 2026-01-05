#include "../../src/1-ds/ds_li_chao.cpp"

// what: tests for li_chao (max of lines on integer x-range).
// time: random + edge cases; memory: O(n)
// constraint: uses assert, fixed seed.
// usage: g++ -std=c++17 test_ds_li_chao.cpp && ./a.out

mt19937_64 rng(6);
ll rnd(ll l, ll r) {
    uniform_int_distribution<ll> dis(l, r);
    return dis(rng);
}

ll eval_line(const lc_line &ln, ll x) { return ln.m * x + ln.b; }

ll max_naive(const vector<lc_line> &lns, ll x) {
    ll ret = NEG_INF;
    for (auto &ln : lns) ret = max(ret, eval_line(ln, x));
    return ret;
}

void test_li_chao_basic() {
    li_chao lc;
    lc.init(-5, 5);
    vector<lc_line> lns;
    lns.push_back({2, 1});
    lc.add(lns.back());
    assert(lc.query(-5) == max_naive(lns, -5));
    assert(lc.query(5) == max_naive(lns, 5));

    lns.push_back({2, -3});
    lc.add(lns.back());
    assert(lc.query(0) == max_naive(lns, 0));
}

void test_li_chao_random() {
    ll xl = -100, xr = 100;
    li_chao lc;
    lc.init(xl, xr);
    vector<lc_line> lns;

    for (int it = 0; it < 3000; it++) {
        int op = (lns.empty() ? 0 : (int)rnd(0, 1));
        if (op == 0) {
            ll a = rnd(-5, 5);
            ll b = rnd(-20, 20);
            lns.push_back({a, b});
            lc.add(lns.back());
        } else {
            ll x = rnd(xl, xr);
            assert(lc.query(x) == max_naive(lns, x));
        }
    }
}

int main() {
    test_li_chao_basic();
    test_li_chao_random();
    return 0;
}
