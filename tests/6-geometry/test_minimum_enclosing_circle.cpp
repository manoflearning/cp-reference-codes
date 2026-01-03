#include "../../src/6-geometry/minimum_enclosing_circle.cpp"

// what: tests for min_circle (minimum enclosing circle).
// time: random + brute (n<=8); memory: O(n)
// constraint: fixed seed; compares radius with eps.
// usage: g++ -std=c++17 test_minimum_enclosing_circle.cpp && ./a.out

mt19937_64 rng(7);
ll rnd(ll l, ll r) {
    uniform_int_distribution<ll> dis(l, r);
    return dis(rng);
}

circle c2(const ptd &a, const ptd &b) {
    ptd c{(a.x + b.x) / 2.0L, (a.y + b.y) / 2.0L};
    return {c, dist(a, b) / 2.0L};
}

circle c3(const ptd &a, const ptd &b, const ptd &c) {
    ld ax = a.x, ay = a.y;
    ld bx = b.x, by = b.y;
    ld cx = c.x, cy = c.y;
    ld d = 2 * (ax * (by - cy) + bx * (cy - ay) + cx * (ay - by));
    if (fabsl(d) < 1e-18) return {{0, 0}, 1e100};
    ld a2 = ax * ax + ay * ay;
    ld b2 = bx * bx + by * by;
    ld c2 = cx * cx + cy * cy;
    ld ux = (a2 * (by - cy) + b2 * (cy - ay) + c2 * (ay - by)) / d;
    ld uy = (a2 * (cx - bx) + b2 * (ax - cx) + c2 * (bx - ax)) / d;
    ptd o{ux, uy};
    return {o, dist(o, a)};
}

bool cover(const circle &c, const vector<ptd> &p) {
    for (auto &v : p) {
        if (dist(c.c, v) > c.r + 1e-10) return 0;
    }
    return 1;
}

circle brute_mec(const vector<ptd> &p) {
    circle best{{0, 0}, 1e100};
    for (int i = 0; i < sz(p); i++) {
        circle cur{p[i], 0};
        if (cover(cur, p) && cur.r < best.r) best = cur;
    }
    for (int i = 0; i < sz(p); i++) {
        for (int j = i + 1; j < sz(p); j++) {
            circle cur = c2(p[i], p[j]);
            if (cover(cur, p) && cur.r < best.r) best = cur;
        }
    }
    for (int i = 0; i < sz(p); i++) {
        for (int j = i + 1; j < sz(p); j++) {
            for (int k = j + 1; k < sz(p); k++) {
                circle cur = c3(p[i], p[j], p[k]);
                if (cur.r > 1e50) continue;
                if (cover(cur, p) && cur.r < best.r) best = cur;
            }
        }
    }
    return best;
}

void test_mec_basic() {
    vector<ptd> p = {{0, 0}};
    auto c = min_circle(p);
    assert(fabsl(c.r) < 1e-12);
    assert(fabsl(c.c.x) < 1e-12);
    assert(fabsl(c.c.y) < 1e-12);

    p = {{0, 0}, {2, 0}};
    c = min_circle(p);
    assert(fabsl(c.r - 1) < 1e-9);
    assert(fabsl(c.c.x - 1) < 1e-9);
    assert(fabsl(c.c.y) < 1e-9);

    p = {{1, 0}, {0, 1}, {-1, 0}};
    c = min_circle(p);
    assert(fabsl(c.r - 1) < 1e-8);
    assert(fabsl(c.c.x) < 1e-8);
    assert(fabsl(c.c.y) < 1e-8);
}

void test_mec_random_brute() {
    for (int tc = 0; tc < 5000; tc++) {
        int n = (int)rnd(1, 8);
        vector<ptd> p;
        p.reserve(n);
        for (int i = 0; i < n; i++) {
            ptd v{(ld)rnd(-5, 5), (ld)rnd(-5, 5)};
            p.pb(v);
        }
        auto got = min_circle(p);
        auto exp = brute_mec(p);
        assert(cover(got, p));
        assert(fabsl(got.r - exp.r) < 1e-7);
    }
}

int main() {
    test_mec_basic();
    test_mec_random_brute();
    return 0;
}
