#pragma once
#include "../common/common.hpp"

// what: 2D geometry base (pt/ptd, ccw/cross/dot, segment/line utils).
// time: O(1) per op; memory: O(1)
// constraint: pt uses ll (overflow if |coord| too large); ptd uses EPS.
// usage: pt a{0,0}; int s = ccw(a,b,c); if (seg_inter(a,b,c,d)) ...
struct pt {
    ll x, y;
    bool operator<(const pt &rhs) const {
        return x == rhs.x ? y < rhs.y : x < rhs.x;
    }
    bool operator==(const pt &rhs) const {
        return x == rhs.x && y == rhs.y;
    }
    pt operator+(const pt &rhs) const {
        return {x + rhs.x, y + rhs.y};
    }
    pt operator-(const pt &rhs) const {
        return {x - rhs.x, y - rhs.y};
    }
};

struct ptd {
    ld x, y;
    ptd operator+(const ptd &rhs) const {
        return {x + rhs.x, y + rhs.y};
    }
    ptd operator-(const ptd &rhs) const {
        return {x - rhs.x, y - rhs.y};
    }
};

constexpr ld EPS = 1e-9;

inline int sgn(ld v) {
    return (v > EPS) - (v < -EPS);
}

inline bool eq(ld a, ld b) {
    return fabsl(a - b) < EPS;
}

inline ll cross(const pt &a, const pt &b) {
    return a.x * b.y - a.y * b.x;
}

inline ll cross(const pt &a, const pt &b, const pt &c) {
    return cross(b - a, c - a);
}

inline ll dot(const pt &a, const pt &b) {
    return a.x * b.x + a.y * b.y;
}

inline ll dist2(const pt &a, const pt &b) {
    ll dx = a.x - b.x;
    ll dy = a.y - b.y;
    return dx * dx + dy * dy;
}

inline int ccw(const pt &a, const pt &b, const pt &c) {
    ll v = cross(a, b, c);
    return (v > 0) - (v < 0);
}

inline bool in_box(const pt &a, const pt &b, const pt &p) {
    return min(a.x, b.x) <= p.x && p.x <= max(a.x, b.x) &&
           min(a.y, b.y) <= p.y && p.y <= max(a.y, b.y);
}

inline bool on_seg(const pt &a, const pt &b, const pt &p) {
    return ccw(a, b, p) == 0 && in_box(a, b, p);
}

inline bool seg_inter(const pt &a, const pt &b, const pt &c, const pt &d) {
    int ab1 = ccw(a, b, c), ab2 = ccw(a, b, d);
    int cd1 = ccw(c, d, a), cd2 = ccw(c, d, b);
    if (ab1 == 0 && ab2 == 0) {
        return max(min(a.x, b.x), min(c.x, d.x)) <=
                   min(max(a.x, b.x), max(c.x, d.x)) &&
               max(min(a.y, b.y), min(c.y, d.y)) <=
                   min(max(a.y, b.y), max(c.y, d.y));
    }
    return ab1 * ab2 <= 0 && cd1 * cd2 <= 0;
}

inline ld cross(const ptd &a, const ptd &b) {
    return a.x * b.y - a.y * b.x;
}

inline ld cross(const ptd &a, const ptd &b, const ptd &c) {
    return cross(b - a, c - a);
}

inline ld dot(const ptd &a, const ptd &b) {
    return a.x * b.x + a.y * b.y;
}

inline ld dist(const ptd &a, const ptd &b) {
    ld dx = a.x - b.x;
    ld dy = a.y - b.y;
    return sqrtl(dx * dx + dy * dy);
}

inline bool line_inter(const ptd &a, const ptd &b, const ptd &c, const ptd &d, ptd &out) {
    ld vx1 = b.x - a.x, vy1 = b.y - a.y;
    ld vx2 = d.x - c.x, vy2 = d.y - c.y;
    ld det = vx1 * (-vy2) - (-vx2) * vy1;
    if (eq(det, 0)) return 0;
    ld s = ((c.x - a.x) * (-vy2) + (c.y - a.y) * vx2) / det;
    out.x = a.x + vx1 * s;
    out.y = a.y + vy1 * s;
    return 1;
}
