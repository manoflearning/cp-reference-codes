#include "../../src/6-geometry/segment_intersection.cpp"

// what: tests for seg_inter_p (intersection point).
// time: random + edge cases; memory: O(1)
// constraint: fixed seed; checks point-on-segment with eps.
// usage: g++ -std=c++17 test_segment_intersection.cpp && ./a.out

mt19937_64 rng(7);
ll rnd(ll l, ll r) {
    uniform_int_distribution<ll> dis(l, r);
    return dis(rng);
}

pt rnd_pt(ll l, ll r) {
    return {rnd(l, r), rnd(l, r)};
}

bool on_seg_ld(const pt &a, const pt &b, const ptd &p) {
    ptd pa{(ld)a.x, (ld)a.y};
    ptd p_b{(ld)b.x, (ld)b.y};
    ptd ab = p_b - pa;
    ptd ap = p - pa;
    if (fabsl(cross(ab, ap)) > 1e-8) return 0;
    ld lx = min((ld)a.x, (ld)b.x) - 1e-8;
    ld rx = max((ld)a.x, (ld)b.x) + 1e-8;
    ld ly = min((ld)a.y, (ld)b.y) - 1e-8;
    ld ry = max((ld)a.y, (ld)b.y) + 1e-8;
    return lx <= p.x && p.x <= rx && ly <= p.y && p.y <= ry;
}

void test_seg_inter_p_basic() {
    pt a{0, 0}, b{2, 2}, c{0, 2}, d{2, 0};
    ptd out;
    assert(seg_inter_p(a, b, c, d, out));
    assert(fabsl(out.x - 1.0L) < 1e-9);
    assert(fabsl(out.y - 1.0L) < 1e-9);
    assert(on_seg_ld(a, b, out));
    assert(on_seg_ld(c, d, out));

    pt e{0, 0}, f{2, 0}, g{2, 0}, h{2, 2};
    assert(seg_inter_p(e, f, g, h, out));
    assert(fabsl(out.x - 2.0L) < 1e-9);
    assert(fabsl(out.y - 0.0L) < 1e-9);

    pt i{0, 0}, j{4, 0}, k{2, 0}, l{6, 0};
    assert(seg_inter_p(i, j, k, l, out));
    assert(on_seg_ld(i, j, out));
    assert(on_seg_ld(k, l, out));

    pt m{0, 0}, n{1, 0}, o{2, 0}, p{3, 0};
    assert(!seg_inter_p(m, n, o, p, out));
}

void test_seg_inter_p_random() {
    for (int it = 0; it < 20000; it++) {
        pt a = rnd_pt(-20, 20);
        pt b = rnd_pt(-20, 20);
        pt c = rnd_pt(-20, 20);
        pt d = rnd_pt(-20, 20);
        ptd out;
        bool ok = seg_inter_p(a, b, c, d, out);
        if (ok) {
            assert(seg_inter(a, b, c, d));
            assert(on_seg_ld(a, b, out));
            assert(on_seg_ld(c, d, out));
        } else {
            assert(!seg_inter(a, b, c, d));
        }
    }
}

int main() {
    test_seg_inter_p_basic();
    test_seg_inter_p_random();
    return 0;
}
