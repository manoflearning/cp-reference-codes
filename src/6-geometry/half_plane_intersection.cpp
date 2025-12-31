#include "geom_base.cpp"

// what: compute intersection polygon of multiple half-planes (directed lines).
// time: O(n log n); memory: O(n)
// constraint: add a bounding box if region can be unbounded.
// usage: vector<ptd> poly = hpi(lines);
struct hp_line {
    ptd s, t;
};

static bool eq(ld a, ld b) {
    return fabsl(a - b) < EPS;
}

static ptd dir(const hp_line &l) {
    return l.t - l.s;
}

static bool out(const hp_line &l, const ptd &p) {
    return cross(l.t - l.s, p - l.s) < -EPS;
}

static bool bad(const hp_line &a, const hp_line &b, const hp_line &c) {
    ptd p;
    if (!line_inter(a.s, a.t, b.s, b.t, p)) return 0;
    return out(c, p);
}

vector<ptd> hpi(vector<hp_line> ln) {
    // goal: intersect half-planes and return the convex polygon.
    auto half = [&](const ptd &v) {
        return (v.y > 0 || (eq(v.y, 0) && v.x >= 0));
    };
    sort(all(ln), [&](const hp_line &a, const hp_line &b) {
        ptd da = dir(a), db = dir(b);
        bool ha = half(da), hb = half(db);
        if (ha != hb) return ha > hb;
        ld cr = cross(da, db);
        if (!eq(cr, 0)) return cr > 0;
        return cross(da, b.s - a.s) > 0;
    });
    vector<hp_line> v;
    for (auto &l : ln) {
        if (v.empty()) {
            v.push_back(l);
            continue;
        }
        ptd da = dir(v.back()), db = dir(l);
        if (!eq(cross(da, db), 0)) {
            v.push_back(l);
            continue;
        }
        if (cross(da, l.s - v.back().s) > 0) v.back() = l;
    }
    deque<hp_line> dq;
    for (auto &l : v) {
        while (sz(dq) >= 2 && bad(dq[sz(dq) - 2], dq.back(), l)) dq.pop_back();
        while (sz(dq) >= 2 && bad(dq[0], dq[1], l)) dq.pop_front();
        dq.push_back(l);
    }
    while (sz(dq) >= 3 && bad(dq[sz(dq) - 2], dq.back(), dq[0])) dq.pop_back();
    while (sz(dq) >= 3 && bad(dq[0], dq[1], dq.back())) dq.pop_front();
    vector<ptd> poly;
    if (sz(dq) >= 3) {
        for (int i = 0; i < sz(dq); i++) {
            ptd p;
            if (line_inter(dq[i].s, dq[i].t, dq[(i + 1) % sz(dq)].s,
                           dq[(i + 1) % sz(dq)].t, p)) {
                poly.push_back(p);
            }
        }
    }
    return poly;
}
