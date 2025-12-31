#include "geom_base.cpp"

// what: minimum enclosing circle of points (Welzl-style iterative).
// time: expected O(n); memory: O(1)
// constraint: uses fixed RNG for shuffle; works with doubles (ptd).
// usage: circle c = min_circle(p);
struct circle {
    ptd c;
    ld r;
};

inline bool in_circle(const circle &c, const ptd &p) {
    return dist(c.c, p) <= c.r + 1e-12;
}

circle circle_from(const ptd &a, const ptd &b) {
    ptd c{(a.x + b.x) / 2.0L, (a.y + b.y) / 2.0L};
    return {c, dist(a, b) / 2.0L};
}

circle circle_from(const ptd &a, const ptd &b, const ptd &c) {
    ptd ab = b - a, ac = c - a;
    if (fabsl(cross(ab, ac)) < EPS) {
        circle c1 = circle_from(a, b);
        circle c2 = circle_from(a, c);
        circle c3 = circle_from(b, c);
        circle best = c1;
        if (c2.r > best.r) best = c2;
        if (c3.r > best.r) best = c3;
        return best;
    }
    ld A = ab.x * ab.x + ab.y * ab.y;
    ld B = ac.x * ac.x + ac.y * ac.y;
    ld C = cross(ab, ac);
    ptd o{(ac.y * A - ab.y * B) / (2 * C),
          (ab.x * B - ac.x * A) / (2 * C)};
    o = o + a;
    return {o, dist(o, a)};
}

circle min_circle(vector<ptd> p) {
    static mt19937 rng(712367);
    shuffle(all(p), rng);
    circle c{{0, 0}, -1};
    for (int i = 0; i < sz(p); i++) {
        if (c.r >= 0 && in_circle(c, p[i])) continue;
        c = {p[i], 0};
        for (int j = 0; j < i; j++) {
            if (in_circle(c, p[j])) continue;
            c = circle_from(p[i], p[j]);
            for (int k = 0; k < j; k++) {
                if (in_circle(c, p[k])) continue;
                c = circle_from(p[i], p[j], p[k]);
            }
        }
    }
    return c;
}
