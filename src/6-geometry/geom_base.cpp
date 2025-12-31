#pragma once
#include "../common/common.hpp"

// what: 2D primitives and orientation/intersection helpers for integer and double points.
// time: O(1) per op; memory: O(1)
// constraint: pt uses ll (overflow if |coord| too large); ptd uses EPS.
// usage: pt a{0,0}; int s = ccw(a,b,c); if (seg_inter(a,b,c,d)) ...
struct pt {
    ll x, y;
    bool operator<(const pt &rhs) const { return x == rhs.x ? y < rhs.y : x < rhs.x; }
    bool operator==(const pt &rhs) const { return x == rhs.x && y == rhs.y; }
    pt operator+(const pt &rhs) const { return {x + rhs.x, y + rhs.y}; }
    pt operator-(const pt &rhs) const { return {x - rhs.x, y - rhs.y}; }
};
struct ptd {
    ld x, y;
    ptd operator+(const ptd &rhs) const { return {x + rhs.x, y + rhs.y}; }
    ptd operator-(const ptd &rhs) const { return {x - rhs.x, y - rhs.y}; }
};

constexpr ld EPS = 1e-9;

ll cross(const pt &a, const pt &b) { return a.x * b.y - a.y * b.x; }
ll cross(const pt &a, const pt &b, const pt &c) { return cross(b - a, c - a); }
ll dot(const pt &a, const pt &b) { return a.x * b.x + a.y * b.y; }
ll dist2(const pt &a, const pt &b) {
    ll dx = a.x - b.x, dy = a.y - b.y;
    return dx * dx + dy * dy;
}
int ccw(const pt &a, const pt &b, const pt &c) {
    // result: sign of cross product (orientation).
    ll v = cross(a, b, c);
    return (v > 0) - (v < 0);
}
bool seg_inter(const pt &a, const pt &b, const pt &c, const pt &d) {
    // result: true if segments ab and cd intersect.
    auto in_box = [&](const pt &u, const pt &v, const pt &p) { return min(u.x, v.x) <= p.x && p.x <= max(u.x, v.x) && min(u.y, v.y) <= p.y && p.y <= max(u.y, v.y); };
    auto on_seg = [&](const pt &u, const pt &v, const pt &p) { return ccw(u, v, p) == 0 && in_box(u, v, p); };
    int ab1 = ccw(a, b, c), ab2 = ccw(a, b, d), cd1 = ccw(c, d, a), cd2 = ccw(c, d, b);
    if (ab1 == 0 && on_seg(a, b, c)) return 1;
    if (ab2 == 0 && on_seg(a, b, d)) return 1;
    if (cd1 == 0 && on_seg(c, d, a)) return 1;
    if (cd2 == 0 && on_seg(c, d, b)) return 1;
    return ab1 * ab2 < 0 && cd1 * cd2 < 0;
}

ld cross(const ptd &a, const ptd &b) { return a.x * b.y - a.y * b.x; }
ld cross(const ptd &a, const ptd &b, const ptd &c) { return cross(b - a, c - a); }
ld dot(const ptd &a, const ptd &b) { return a.x * b.x + a.y * b.y; }
ld dist(const ptd &a, const ptd &b) {
    ld dx = a.x - b.x, dy = a.y - b.y;
    return sqrtl(dx * dx + dy * dy);
}
bool line_inter(const ptd &a, const ptd &b, const ptd &c, const ptd &d, ptd &out) {
    // result: intersection point of two lines if not parallel.
    ld vx1 = b.x - a.x, vy1 = b.y - a.y, vx2 = d.x - c.x, vy2 = d.y - c.y;
    ld det = vx1 * (-vy2) - (-vx2) * vy1;
    if (fabsl(det) < EPS) return 0;
    ld s = ((c.x - a.x) * (-vy2) + (c.y - a.y) * vx2) / det;
    out.x = a.x + vx1 * s;
    out.y = a.y + vy1 * s;
    return 1;
}
