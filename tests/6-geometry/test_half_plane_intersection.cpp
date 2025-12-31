#include "../../src/6-geometry/convex_hull.cpp"
#include "../../src/6-geometry/half_plane_intersection.cpp"

// what: tests for hpi (half-plane intersection).
// time: random (convex) + edge cases; memory: O(n)
// constraint: bounded cases only; eps checks.
// usage: g++ -std=c++17 test_half_plane_intersection.cpp && ./a.out

mt19937_64 rng(7);
ll rnd(ll l, ll r) {
    uniform_int_distribution<ll> dis(l, r);
    return dis(rng);
}

ld area_poly(const vector<ptd> &p) {
    ld a = 0;
    for (int i = 0; i < sz(p); i++) {
        int j = (i + 1) % sz(p);
        a += p[i].x * p[j].y - p[i].y * p[j].x;
    }
    return fabsl(a) / 2;
}

bool in_hp(const line &l, const ptd &p) {
    return cross(l.t - l.s, p - l.s) >= -1e-8;
}

void test_hpi_square() {
    vector<line> ln;
    ln.push_back({{0, 1}, {0, 0}}); // x >= 0
    ln.push_back({{1, 0}, {1, 1}}); // x <= 1
    ln.push_back({{0, 0}, {1, 0}}); // y >= 0
    ln.push_back({{1, 1}, {0, 1}}); // y <= 1
    auto poly = hpi(ln);
    assert(sz(poly) == 4);
    assert(fabsl(area_poly(poly) - 1.0L) < 1e-7);
    for (auto &v : poly) {
        for (auto &l : ln) assert(in_hp(l, v));
    }
}

void test_hpi_triangle() {
    vector<line> ln;
    ln.push_back({{0, 1}, {0, 0}}); // x >= 0
    ln.push_back({{0, 0}, {1, 0}}); // y >= 0
    ln.push_back({{1, 0}, {0, 1}}); // x + y <= 1
    auto poly = hpi(ln);
    assert(sz(poly) == 3);
    assert(fabsl(area_poly(poly) - 0.5L) < 1e-7);
    for (auto &v : poly) {
        for (auto &l : ln) assert(in_hp(l, v));
    }
}

void test_hpi_empty() {
    vector<line> ln;
    ln.push_back({{0, 1}, {0, 0}});   // x >= 0
    ln.push_back({{-1, 0}, {-1, 1}}); // x <= -1
    auto poly = hpi(ln);
    assert(poly.empty());
}

void test_hpi_random_convex() {
    for (int tc = 0; tc < 2000; tc++) {
        int n = (int)rnd(10, 30);
        vector<pt> p;
        p.reserve(n);
        for (int i = 0; i < n; i++) p.push_back({rnd(-20, 20), rnd(-20, 20)});
        auto h = convex_hull(p);
        if (sz(h) < 3) continue;

        vector<ptd> hp;
        for (auto &v : h) hp.push_back({(ld)v.x, (ld)v.y});
        vector<line> ln;
        for (int i = 0; i < sz(hp); i++) {
            ln.push_back({hp[i], hp[(i + 1) % sz(hp)]});
        }
        auto poly = hpi(ln);
        assert(sz(poly) == sz(hp));
        ld a1 = area_poly(poly);
        ld a2 = area_poly(hp);
        assert(fabsl(a1 - a2) < 1e-6);
        for (auto &v : poly) {
            for (auto &l : ln) assert(in_hp(l, v));
        }
    }
}

int main() {
    test_hpi_square();
    test_hpi_triangle();
    test_hpi_empty();
    test_hpi_random_convex();
    return 0;
}
