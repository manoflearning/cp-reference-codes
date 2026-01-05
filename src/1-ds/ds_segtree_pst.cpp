#include "../0-common/common.hpp"

// what: persistent segment tree for point set with range sum queries, plus kth by prefix sum.
// time: build O(n), update/query O(log n); memory: O(n log n)
// constraint: 1-indexed [1, n]; a[0] unused; kth needs all values >= 0.
// usage: seg_pst st; st.build(n, a); st.set(p, v); st.query(l, r, ver); st.kth(k, ver);
struct seg_pst {
    struct node {
        int l, r;
        ll val;
    };
    int n;
    vector<node> t;
    vector<int> root;

    void newnd() { t.push_back({-1, -1, 0}); }
    void build(int n_, const vector<ll> &a) {
        // goal: build initial version.
        n = n_;
        t.clear();
        root.clear();
        newnd();
        root.push_back(0);
        build(1, n, root[0], a);
    }
    void build(int l, int r, int v, const vector<ll> &a) {
        // goal: build node v for range [l, r].
        if (l == r) {
            t[v].val = a[l];
            return;
        }
        newnd();
        t[v].l = sz(t) - 1;
        newnd();
        t[v].r = sz(t) - 1;
        int mid = (l + r) >> 1;
        build(l, mid, t[v].l, a);
        build(mid + 1, r, t[v].r, a);
        t[v].val = t[t[v].l].val + t[t[v].r].val;
    }
    void set(int p, ll val) {
        // goal: create new version with a[p] = val.
        newnd();
        root.push_back(sz(t) - 1);
        set(p, val, 1, n, root[sz(root) - 2], root.back());
    }
    void set(int p, ll val, int l, int r, int v1, int v2) {
        // goal: update along path while sharing unchanged nodes.
        if (p < l || r < p) {
            t[v2] = t[v1];
            return;
        }
        if (l == r) {
            t[v2].val = val;
            return;
        }
        int mid = (l + r) >> 1;
        if (p <= mid) {
            t[v2].r = t[v1].r;
            newnd();
            t[v2].l = sz(t) - 1;
            set(p, val, l, mid, t[v1].l, t[v2].l);
        } else {
            t[v2].l = t[v1].l;
            newnd();
            t[v2].r = sz(t) - 1;
            set(p, val, mid + 1, r, t[v1].r, t[v2].r);
        }
        t[v2].val = t[t[v2].l].val + t[t[v2].r].val;
    }
    ll query(int l, int r, int v, int nl, int nr) const {
        // result: sum on [l, r] in a specific version.
        if (r < nl || nr < l) return 0;
        if (l <= nl && nr <= r) return t[v].val;
        int mid = (nl + nr) >> 1;
        return query(l, r, t[v].l, nl, mid) + query(l, r, t[v].r, mid + 1, nr);
    }
    ll query(int l, int r, int ver) const { return query(l, r, root[ver], 1, n); }
    int kth(ll k, int v, int nl, int nr) const {
        // result: smallest idx with prefix sum >= k (in this subtree).
        assert(k > 0 && t[v].val >= k);
        if (nl == nr) return nl;
        int mid = (nl + nr) >> 1;
        ll lv = t[t[v].l].val;
        if (k <= lv) return kth(k, t[v].l, nl, mid);
        return kth(k - lv, t[v].r, mid + 1, nr);
    }
    int kth(ll k, int ver) const { return kth(k, root[ver], 1, n); }
};
