#include "../0-common/common.hpp"

// what: maintain max of lines on a fixed x-range with online add + point query.
// time: add/query O(log X); memory: O(n)
// constraint: x in [xl, xr]; line is y = ax + b.
// usage: li_chao lc; lc.init(xl, xr); lc.add({a, b}); ll v = lc.query(x);
struct lc_line {
    ll m, b;
};
constexpr ll NEG_INF = -(1LL << 60);
constexpr lc_line LINE_E = {0, NEG_INF};

struct li_chao {
    struct node {
        ll xl, xr;
        int l, r;
        lc_line ln;
    };
    vector<node> t;

    ll eval(const lc_line &ln, ll x) const { return ln.m * x + ln.b; }
    void init(ll xl, ll xr) {
        // goal: set x-range and clear tree.
        t.clear();
        t.pb({xl, xr, -1, -1, LINE_E});
    }
    void add(lc_line nw, int v = 0) {
        // goal: insert a new line into the segment.
        ll xl = t[v].xl, xr = t[v].xr;
        ll mid = (xl + xr) >> 1;

        lc_line lo = t[v].ln, hi = nw;
        if (eval(lo, xl) >= eval(hi, xl)) swap(lo, hi);

        if (eval(lo, xr) <= eval(hi, xr)) {
            t[v].ln = hi;
            return;
        }
        if (eval(lo, mid) < eval(hi, mid)) {
            t[v].ln = hi;
            if (t[v].r == -1) {
                t[v].r = sz(t);
                t.pb({mid + 1, xr, -1, -1, LINE_E});
            }
            add(lo, t[v].r);
        } else {
            t[v].ln = lo;
            if (t[v].l == -1) {
                t[v].l = sz(t);
                t.pb({xl, mid, -1, -1, LINE_E});
            }
            add(hi, t[v].l);
        }
    }
    ll query(ll x, int v = 0) const {
        // result: max y-value among all lines at x.
        if (v == -1) return NEG_INF;
        ll xl = t[v].xl, xr = t[v].xr;
        ll mid = (xl + xr) >> 1;

        ll ret = eval(t[v].ln, x);
        if (x <= mid) ret = max(ret, query(x, t[v].l));
        else ret = max(ret, query(x, t[v].r));
        return ret;
    }
};
