#include "../../src/6-geometry/convex_hull.cpp"
#include "../../src/6-geometry/ray_casting.cpp"

// what: tests for in_poly (ray casting, boundary included).
// time: random (convex) + edge cases; memory: O(n)
// constraint: fixed seed; convex reference via half-plane check.
// usage: g++ -std=c++17 test_ray_casting.cpp && ./a.out

mt19937_64 rng(7);
ll rnd(ll l, ll r) {
    uniform_int_distribution<ll> dis(l, r);
    return dis(rng);
}

bool in_convex_ref(const vector<pt> &h, const pt &q) {
    int n = sz(h);
    if (!n) return 0;
    if (n == 1) return h[0] == q;
    if (n == 2) return on_seg(h[0], h[1], q);
    for (int i = 0; i < n; i++) {
        pt a = h[i], b = h[(i + 1) % n];
        if (cross(a, b, q) < 0) return 0;
    }
    return 1;
}

void test_in_poly_basic() {
    vector<pt> tri = {{0, 0}, {5, 0}, {0, 5}};
    assert(in_poly(tri, {1, 1}));
    assert(!in_poly(tri, {4, 4}));
    assert(in_poly(tri, {0, 0}));
    assert(in_poly(tri, {2, 0}));

    vector<pt> conc = {{0, 0}, {6, 0}, {6, 2}, {2, 2}, {2, 4}, {6, 4}, {6, 6}, {0, 6}};
    assert(in_poly(conc, {1, 3}));
    assert(!in_poly(conc, {3, 3}));
    assert(in_poly(conc, {0, 3}));
    assert(in_poly(conc, {2, 3}));
}

void test_in_poly_random_convex() {
    for (int tc = 0; tc < 1000; tc++) {
        int n = (int)rnd(3, 40);
        vector<pt> p;
        p.reserve(n);
        for (int i = 0; i < n; i++) p.push_back({rnd(-20, 20), rnd(-20, 20)});
        auto h = convex_hull(p);
        if (sz(h) < 3) continue;

        for (int it = 0; it < 200; it++) {
            pt q{rnd(-25, 25), rnd(-25, 25)};
            bool got = in_poly(h, q);
            bool exp = in_convex_ref(h, q);
            assert(got == exp);
        }
        for (int i = 0; i < sz(h); i++) {
            pt a = h[i], b = h[(i + 1) % sz(h)];
            ll dx = b.x - a.x, dy = b.y - a.y;
            ll g = std::gcd(llabs(dx), llabs(dy));
            pt mid{a.x + dx / g, a.y + dy / g};
            assert(in_poly(h, a));
            assert(in_poly(h, mid));
        }
    }
}

int main() {
    test_in_poly_basic();
    test_in_poly_random_convex();
    return 0;
}
