#include "geom_base.cpp"

// what: enumerate point orderings under rotating direction for angle-sweep counting.
// time: O(n^2 log n); memory: O(n^2)
// constraint: orders correspond to direction angle in [0, pi); points processed in-place.
// usage: bulldozer(p, [&](const vector<pt> &cur) { /* use order */ });
struct bd_line {
    int u, v;
    ll dx, dy; // dx >= 0
    bool operator<(const bd_line &rhs) const {
        if (dy * rhs.dx != rhs.dy * dx) return dy * rhs.dx < rhs.dy * dx;
        return tie(u, v) < tie(rhs.u, rhs.v);
    }
    bool operator==(const bd_line &rhs) const {
        return dy * rhs.dx == rhs.dy * dx;
    }
};

template <class F>
void bulldozer(vector<pt> &p, F f) {
    // goal: visit each distinct angular order once.
    int n = sz(p);
    sort(all(p));
    vector<pt> base = p;
    vi pos(n);
    iota(all(pos), 0);
    vector<bd_line> ln;
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
            ln.pb({u, v, dx, dy});
        }
    }
    sort(all(ln));
    f(p);
    for (int i = 0, j = 0; i < sz(ln); i = j) {
        while (j < sz(ln) && ln[j] == ln[i]) j++;
        ll dx = ln[i].dx, dy = ln[i].dy;
        if (dx == 0) break;
        unordered_map<ll, vi> mp;
        mp.reserve((j - i) * 2 + 1);
        for (int k = i; k < j; k++) {
            int u = ln[k].u, v = ln[k].v;
            ll c = -dy * base[u].x + dx * base[u].y;
            mp[c].pb(u);
            mp[c].pb(v);
        }
        for (auto &it : mp) {
            auto &vec = it.sc;
            sort(all(vec));
            vec.erase(unique(all(vec)), vec.end());
            sort(all(vec), [&](int a, int b) { return pos[a] < pos[b]; });
            for (int l = 0, r = sz(vec) - 1; l < r; l++, r--) {
                int u = vec[l], v = vec[r];
                int pu = pos[u], pv = pos[v];
                if (pu == pv) continue;
                swap(p[pu], p[pv]);
                swap(pos[u], pos[v]);
            }
        }
        f(p);
    }
}

void bulldozer(vector<pt> &p) {
    bulldozer(p, [](const vector<pt> &) {});
}
