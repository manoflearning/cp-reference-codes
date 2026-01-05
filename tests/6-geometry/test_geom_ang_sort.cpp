#include "../../src/6-geometry/geom_ang_sort.cpp"

// what: tests for sort_ang (polar angle sort).
// time: random + reference by atan2; memory: O(n)
// constraint: fixed seed; avoids collinear rays in random.
// usage: g++ -std=c++17 test_geom_ang_sort.cpp && ./a.out

mt19937_64 rng(7);
ll rnd(ll l, ll r) {
    uniform_int_distribution<ll> dis(l, r);
    return dis(rng);
}

ld ang(const pt &a, const pt &o) {
    ld y = (ld)(a.y - o.y);
    ld x = (ld)(a.x - o.x);
    ld t = atan2l(y, x);
    if (t < 0) t += 2 * acosl(-1.0L);
    return t;
}

void test_sort_ang_basic() {
    vector<pt> p = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}};
    sort_ang(p, {0, 0});
    vector<pt> exp = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}};
    assert(p == exp);

    p = {{2, 0}, {1, 0}, {0, 1}};
    sort_ang(p, {0, 0});
    exp = {{1, 0}, {2, 0}, {0, 1}};
    assert(p == exp);
}

void test_sort_ang_random() {
    const ld PI = acosl(-1.0L);
    for (int tc = 0; tc < 2000; tc++) {
        pt o{rnd(-5, 5), rnd(-5, 5)};
        int n = 30;
        vector<pt> p;
        for (int it = 0; sz(p) < n && it < 100000; it++) {
            pt v{rnd(-20, 20), rnd(-20, 20)};
            if (v == o) continue;
            bool ok = 1;
            for (auto &u : p) {
                pt a = u - o, b = v - o;
                if (cross(a, b) == 0) ok = 0;
            }
            if (ok) p.push_back(v);
        }
        assert(sz(p) == n);

        vector<pt> got = p;
        sort_ang(got, o);
        vector<pt> exp = p;
        sort(all(exp), [&](const pt &a, const pt &b) {
            ld aa = ang(a, o), bb = ang(b, o);
            if (fabsl(aa - bb) > 1e-18) return aa < bb;
            return dist2(o, a) < dist2(o, b);
        });
        assert(got == exp);

        for (int i = 0; i < sz(got); i++) {
            pt a = got[i] - o, b = got[(i + 1) % sz(got)] - o;
            assert(cross(a, b) != 0);
        }
    }
}

int main() {
    test_sort_ang_basic();
    test_sort_ang_random();
    return 0;
}
