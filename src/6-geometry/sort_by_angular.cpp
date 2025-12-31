#include "geom_base.cpp"

// what: sort points by polar angle around origin (CCW, starting from +x).
// time: O(n log n); memory: O(1)
// constraint: ties by distance to origin; pass custom origin if needed.
// usage: sort_ang(p); // origin (0,0)
void sort_ang(vector<pt> &p, const pt &o) {
    auto half = [&](const pt &v) {
        return (v.y > 0 || (v.y == 0 && v.x >= 0));
    };
    sort(all(p), [&](const pt &a, const pt &b) {
        pt da = a - o, db = b - o;
        bool ha = half(da), hb = half(db);
        if (ha != hb) return ha > hb;
        ll cr = cross(da, db);
        if (cr) return cr > 0;
        return dist2(o, a) < dist2(o, b);
    });
}

void sort_ang(vector<pt> &p) {
    sort_ang(p, {0, 0});
}
