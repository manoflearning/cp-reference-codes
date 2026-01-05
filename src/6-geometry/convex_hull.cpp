#include "geom_base.cpp"

// what: compute the convex hull polygon of points in CCW order.
// time: O(n log n); memory: O(n)
// constraint: collinear points on edges are removed (use < instead of <= to keep).
// usage: vector<pt> hull = convex_hull(p);
vector<pt> convex_hull(vector<pt> p) {
    // result: hull without collinear edge points.
    sort(all(p));
    p.erase(unique(all(p)), p.end());
    int n = sz(p);
    if (n <= 1) return p;
    vector<pt> lo, hi;
    for (auto &v : p) {
        while (sz(lo) >= 2 && cross(lo[sz(lo) - 2], lo.back(), v) <= 0) lo.pop_back();
        lo.push_back(v);
    }
    for (int i = n - 1; i >= 0; i--) {
        auto v = p[i];
        while (sz(hi) >= 2 && cross(hi[sz(hi) - 2], hi.back(), v) <= 0) hi.pop_back();
        hi.push_back(v);
    }
    lo.pop_back();
    hi.pop_back();
    lo.insert(lo.end(), all(hi));
    return lo;
}
