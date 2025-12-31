#include "geom_base.cpp"

// what: point-in-polygon test by ray casting (boundary included).
// time: O(n); memory: O(1)
// constraint: polygon is simple (cw/ccw ok); returns true on boundary.
// usage: bool inside = in_poly(poly, q);
static bool in_box(const pt &a, const pt &b, const pt &p) {
    return min(a.x, b.x) <= p.x && p.x <= max(a.x, b.x) &&
           min(a.y, b.y) <= p.y && p.y <= max(a.y, b.y);
}

static bool on_seg(const pt &a, const pt &b, const pt &p) {
    return ccw(a, b, p) == 0 && in_box(a, b, p);
}

bool in_poly(const vector<pt> &poly, const pt &q) {
    int n = sz(poly);
    if (!n) return 0;
    for (int i = 0; i < n; i++) {
        if (on_seg(poly[i], poly[(i + 1) % n], q)) return 1;
    }
    int cnt = 0;
    for (int i = 0; i < n; i++) {
        pt a = poly[i], b = poly[(i + 1) % n];
        if ((a.y > q.y) != (b.y > q.y)) {
            ld x = (ld)(b.x - a.x) * (q.y - a.y) / (ld)(b.y - a.y) + a.x;
            if (x > q.x) cnt ^= 1;
        }
    }
    return cnt;
}
