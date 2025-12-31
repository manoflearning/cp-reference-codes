#include "geom_base.cpp"

// what: diameter (farthest pair) of a convex polygon via rotating calipers.
// time: O(n); memory: O(1)
// constraint: hull must be CCW, no duplicate last point; n>=1.
// usage: auto [a,b] = hull_diam(hull);
pair<pt, pt> hull_diam(const vector<pt> &h) {
    int n = sz(h);
    if (!n) return {{0, 0}, {0, 0}};
    if (n == 1) return {h[0], h[0]};
    int j = 1;
    ll best = 0;
    pair<pt, pt> res = {h[0], h[0]};
    for (int i = 0; i < n; i++) {
        int ni = (i + 1) % n;
        while (1) {
            int nj = (j + 1) % n;
            ll cur = llabs(cross(h[ni] - h[i], h[nj] - h[i]));
            ll prv = llabs(cross(h[ni] - h[i], h[j] - h[i]));
            if (cur > prv) j = nj;
            else break;
        }
        ll d1 = dist2(h[i], h[j]);
        if (d1 > best) best = d1, res = {h[i], h[j]};
        ll d2 = dist2(h[ni], h[j]);
        if (d2 > best) best = d2, res = {h[ni], h[j]};
    }
    return res;
}
