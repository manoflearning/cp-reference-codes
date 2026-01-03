#include "../../src/6-geometry/convex_hull.cpp"

// what: tests for convex_hull (monotone chain, no collinear points on edges).
// time: random + naive (jarvis); memory: O(n)
// constraint: fixed seed; compares hull vertex set.
// usage: g++ -std=c++17 test_convex_hull.cpp && ./a.out

mt19937_64 rng(7);
ll rnd(ll l, ll r) {
    uniform_int_distribution<ll> dis(l, r);
    return dis(rng);
}

static inline bool in_box(const pt &a, const pt &b, const pt &p) {
    return min(a.x, b.x) <= p.x && p.x <= max(a.x, b.x) &&
           min(a.y, b.y) <= p.y && p.y <= max(a.y, b.y);
}

static inline bool on_seg(const pt &a, const pt &b, const pt &p) {
    return ccw(a, b, p) == 0 && in_box(a, b, p);
}

vector<pt> uniq_pts(vector<pt> p) {
    sort(all(p));
    p.erase(unique(all(p)), p.end());
    return p;
}

vector<pt> jarvis(vector<pt> p) {
    p = uniq_pts(p);
    int n = sz(p);
    if (n <= 1) return p;
    int st = 0;
    for (int i = 1; i < n; i++) {
        if (p[i] < p[st]) st = i;
    }
    vector<pt> h;
    int cur = st;
    while (1) {
        h.pb(p[cur]);
        int nxt = (cur == 0 ? 1 : 0);
        for (int i = 0; i < n; i++)
            if (i != cur) {
                int t = ccw(p[cur], p[nxt], p[i]);
                if (t > 0 || (t == 0 && dist2(p[cur], p[i]) > dist2(p[cur], p[nxt]))) {
                    nxt = i;
                }
            }
        cur = nxt;
        if (cur == st) break;
    }
    return h;
}

bool is_convex_ccw(const vector<pt> &h) {
    if (sz(h) <= 2) return 1;
    for (int i = 0; i < sz(h); i++) {
        pt a = h[i];
        pt b = h[(i + 1) % sz(h)];
        pt c = h[(i + 2) % sz(h)];
        if (cross(a, b, c) <= 0) return 0;
    }
    return 1;
}

bool in_convex(const vector<pt> &h, const pt &q) {
    if (sz(h) == 0) return 0;
    if (sz(h) == 1) return h[0] == q;
    if (sz(h) == 2) return on_seg(h[0], h[1], q);
    for (int i = 0; i < sz(h); i++) {
        pt a = h[i], b = h[(i + 1) % sz(h)];
        if (cross(a, b, q) < 0) return 0;
    }
    return 1;
}

void test_hull_basic() {
    vector<pt> p = {{0, 0}, {3, 0}, {2, 0}, {1, 0}};
    auto h = convex_hull(p);
    vector<pt> exp = {{0, 0}, {3, 0}};
    assert(uniq_pts(h) == exp);

    p = {{0, 0}, {0, 1}, {1, 0}, {1, 1}, {0, 0}, {1, 0}};
    h = convex_hull(p);
    assert(sz(h) == 4);
    assert(is_convex_ccw(h));
    for (auto &v : uniq_pts(p)) assert(in_convex(h, v));
}

void test_hull_random() {
    for (int tc = 0; tc < 2000; tc++) {
        int n = (int)rnd(1, 50);
        vector<pt> p;
        p.reserve(n);
        for (int i = 0; i < n; i++) p.pb({rnd(-20, 20), rnd(-20, 20)});
        auto h1 = convex_hull(p);
        auto h2 = jarvis(p);
        auto s1 = uniq_pts(h1);
        auto s2 = uniq_pts(h2);
        assert(s1 == s2);
        assert(is_convex_ccw(h1) || sz(h1) <= 2);
        for (auto &v : uniq_pts(p)) assert(in_convex(h1, v));
    }
}

int main() {
    test_hull_basic();
    test_hull_random();
    return 0;
}
