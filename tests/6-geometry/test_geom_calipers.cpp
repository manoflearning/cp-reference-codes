#include "../../src/6-geometry/geom_calipers.cpp"
#include "../../src/6-geometry/geom_hull.cpp"

// what: tests for hull_diam (rotating calipers).
// time: random + brute; memory: O(n)
// constraint: fixed seed; compares max dist2.
// usage: g++ -std=c++17 test_geom_calipers.cpp && ./a.out

mt19937_64 rng(7);
ll rnd(ll l, ll r) {
    uniform_int_distribution<ll> dis(l, r);
    return dis(rng);
}

ll brute_diam2(const vector<pt> &p) {
    ll best = 0;
    for (int i = 0; i < sz(p); i++) {
        for (int j = i; j < sz(p); j++) {
            best = max(best, dist2(p[i], p[j]));
        }
    }
    return best;
}

void test_diam_basic() {
    vector<pt> p = {{0, 0}, {1, 0}, {1, 1}, {0, 1}};
    auto h = convex_hull(p);
    auto res = hull_diam(h);
    assert(dist2(res.fr, res.sc) == 2);
}

void test_diam_random() {
    for (int tc = 0; tc < 2000; tc++) {
        int n = (int)rnd(1, 50);
        vector<pt> p;
        p.reserve(n);
        for (int i = 0; i < n; i++) p.push_back({rnd(-30, 30), rnd(-30, 30)});
        auto h = convex_hull(p);
        if (sz(h) == 0) continue;
        auto res = hull_diam(h);
        ll got = dist2(res.fr, res.sc);
        ll exp = brute_diam2(p);
        assert(got == exp);
    }
}

int main() {
    test_diam_basic();
    test_diam_random();
    return 0;
}
