#include "../../src/6-geometry/bulldozer_trick.cpp"

// what: tests for bulldozer (enumerates angular orders).
// time: random + brute by sampling directions; memory: O(n^2)
// constraint: fixed seed; uses long double directions in [0, pi).
// usage: g++ -std=c++17 test_bulldozer_trick.cpp && ./a.out

mt19937_64 rng(7);
ll rnd(ll l, ll r) {
    uniform_int_distribution<ll> dis(l, r);
    return dis(rng);
}

vector<ld> uniq_ang(vector<ld> v) {
    sort(all(v));
    vector<ld> u;
    for (auto &x : v) {
        if (u.empty() || fabsl(u.back() - x) > 1e-12) u.pb(x);
    }
    return u;
}

vector<int> perm(const vector<pt> &p, map<pll, int> &id) {
    vector<int> res;
    res.reserve(sz(p));
    for (auto &v : p) res.pb(id[{v.x, v.y}]);
    return res;
}

vector<int> proj_ord(const vector<pt> &p, map<pll, int> &id, ld ang) {
    ld cs = cosl(ang), sn = sinl(ang);
    vector<pair<ld, int>> arr;
    arr.reserve(sz(p));
    for (auto &v : p) {
        ld pr = (ld)v.x * cs + (ld)v.y * sn;
        arr.pb({pr, id[{v.x, v.y}]});
    }
    sort(all(arr), [&](auto &a, auto &b) {
        if (fabsl(a.fr - b.fr) > 1e-18) return a.fr < b.fr;
        return a.sc < b.sc;
    });
    vector<int> ord;
    ord.reserve(sz(p));
    for (auto &x : arr) ord.pb(x.sc);
    return ord;
}

void test_bulldozer_small() {
    const ld PI = acosl(-1.0L);
    for (int tc = 0; tc < 300; tc++) {
        int n = (int)rnd(2, 7);
        vector<pt> pts;
        map<pll, int> id;
        while (sz(pts) < n) {
            pt v{rnd(-10, 10), rnd(-10, 10)};
            if (id.count({v.x, v.y})) continue;
            id[{v.x, v.y}] = sz(pts);
            pts.pb(v);
        }

        vector<vector<int>> got;
        vector<pt> cur = pts;
        bulldozer(cur, [&](const vector<pt> &p) { got.pb(perm(p, id)); });

        vector<ld> th;
        for (int i = 0; i < n; i++) {
            for (int j = i + 1; j < n; j++) {
                ll dx = pts[j].x - pts[i].x;
                ll dy = pts[j].y - pts[i].y;
                if (dx < 0 || (dx == 0 && dy < 0)) dx = -dx, dy = -dy;
                ld a = atan2l((ld)dy, (ld)dx);
                ld t = a + PI / 2;
                t = fmodl(t, PI);
                if (t < 0) t += PI;
                th.pb(t);
            }
        }
        th = uniq_ang(th);

        vector<ld> bnd;
        bnd.pb(0);
        for (auto &t : th) {
            if (t > 1e-12 && t < PI - 1e-12) bnd.pb(t);
        }
        bnd.pb(PI);
        bnd = uniq_ang(bnd);

        vector<vector<int>> exp;
        vector<pt> st = pts;
        sort(all(st));
        for (int i = 0; i + 1 < sz(bnd); i++) {
            ld mid = (bnd[i] + bnd[i + 1]) / 2;
            exp.pb(proj_ord(st, id, mid));
        }
        assert(got == exp);
    }
}

int main() {
    test_bulldozer_small();
    return 0;
}
