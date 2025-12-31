#include "geom_base.cpp"

// what: iterate all angular orders of points by rotating a line (bulldozer trick).
// time: O(n^2 log n); memory: O(n^2)
// constraint: points are processed in-place in p; edit the marked loop to use each order.
// usage: bulldozer(p); // inside, use current order of p
struct line {
    int u, v;
    ll dx, dy; // dx >= 0
    bool operator<(const line &rhs) const {
        if (dy * rhs.dx != rhs.dy * dx) return dy * rhs.dx < rhs.dy * dx;
        return tie(u, v) < tie(rhs.u, rhs.v);
    }
    bool operator==(const line &rhs) const {
        return dy * rhs.dx == rhs.dy * dx;
    }
};

void bulldozer(vector<pt> &p) {
    int n = sz(p);
    sort(all(p));
    vector<int> pos(n);
    iota(all(pos), 0);
    vector<line> ln;
    ln.reserve(1LL * n * (n - 1) / 2);
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            int u = i, v = j;
            ll dx = p[v].x - p[u].x;
            ll dy = p[v].y - p[u].y;
            if (dx < 0 || (dx == 0 && dy < 0)) {
                dx = -dx, dy = -dy;
                swap(u, v);
            }
            ln.push_back({u, v, dx, dy});
        }
    }
    sort(all(ln));
    for (int i = 0, j = 0; i < sz(ln); i = j) {
        while (j < sz(ln) && ln[j] == ln[i]) j++;
        for (int k = i; k < j; k++) {
            int u = ln[k].u, v = ln[k].v;
            swap(p[pos[u]], p[pos[v]]);
            swap(pos[u], pos[v]);
        }
        // usage: handle current order of p here.
    }
}
