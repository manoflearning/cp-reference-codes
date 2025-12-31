#include "../../src/6-geometry/geom_base.cpp"

// what: tests for geom_base (ccw/cross, seg_inter, line_inter).
// time: random + edge cases; memory: O(1)
// constraint: fixed seed; long double eps.
// usage: g++ -std=c++17 test_geom_base.cpp && ./a.out

mt19937_64 rng(7);
ll rnd(ll l, ll r) {
    uniform_int_distribution<ll> dis(l, r);
    return dis(rng);
}

pt rnd_pt(ll l, ll r) {
    return {rnd(l, r), rnd(l, r)};
}

void test_ccw_basic() {
    pt a{0, 0}, b{1, 0}, c{0, 1}, d{2, 0};
    assert(ccw(a, b, c) == 1);
    assert(ccw(a, c, b) == -1);
    assert(ccw(a, b, d) == 0);
    assert(cross(b - a, c - a) > 0);
    assert(dot(b - a, d - a) > 0);
}

void test_seg_inter_basic() {
    pt a{0, 0}, b{2, 2}, c{0, 2}, d{2, 0};
    assert(seg_inter(a, b, c, d));
    pt e{0, 0}, f{1, 1}, g{2, 0};
    assert(seg_inter(e, f, f, g));
    pt h{0, 0}, i{4, 0}, j{2, 0}, k{6, 0};
    assert(seg_inter(h, i, j, k));
    pt l{0, 0}, m{1, 0}, n{2, 0}, o{3, 0};
    assert(!seg_inter(l, m, n, o));
    pt p1{0, 0}, p2{0, 5}, q1{-1, 2}, q2{1, 2};
    assert(seg_inter(p1, p2, q1, q2));
}

void test_seg_inter_sym() {
    for (int it = 0; it < 20000; it++) {
        pt a = rnd_pt(-10, 10);
        pt b = rnd_pt(-10, 10);
        pt c = rnd_pt(-10, 10);
        pt d = rnd_pt(-10, 10);
        bool abcd = seg_inter(a, b, c, d);
        assert(abcd == seg_inter(b, a, c, d));
        assert(abcd == seg_inter(a, b, d, c));
        assert(abcd == seg_inter(c, d, a, b));
    }
}

void test_line_inter_basic() {
    ptd a{0, 0}, b{1, 0}, c{0, 0}, d{0, 1};
    ptd out;
    assert(line_inter(a, b, c, d, out));
    assert(fabsl(out.x) < 1e-12);
    assert(fabsl(out.y) < 1e-12);
    ptd e{0, 1}, f{1, 1};
    assert(!line_inter(a, b, e, f, out));
}

int main() {
    test_ccw_basic();
    test_seg_inter_basic();
    test_seg_inter_sym();
    test_line_inter_basic();
    return 0;
}
