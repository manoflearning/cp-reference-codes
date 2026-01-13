#include "../0-common/common.hpp"

// what: persistent segment tree for point set with range sum queries, plus kth by prefix sum.
// time: init O(1), update/query/kth O(log n); memory: O(q log n)
// constraint: version 0 is all zeros; 1-indexed [1, n]; kth needs all values >= 0.
// usage: seg_pst st; st.init(n); st.set(p, v); st.query(l, r, ver); st.kth(k, ver);
struct seg_pst {
    struct node {
        int l, r;
        ll val;
    };
    int n;
    vector<node> t;
    vector<int> root;

    int newnd(const node &nd) {
        t.push_back(nd);
        return sz(t) - 1;
    }
    void init(int n_) {
        // goal: version 0 = all zeros (root = 0).
        n = n_;
        t.assign(1, {0, 0, 0});
        root.assign(1, 0);
    }
    int set(int p, ll val, int nl, int nr, int v) {
        // goal: update along path while sharing unchanged nodes.
        int u = newnd(t[v]);
        if (nl == nr) {
            t[u].val = val;
            return u;
        }
        int mid = (nl + nr) >> 1;
        if (p <= mid) t[u].l = set(p, val, nl, mid, t[v].l);
        else t[u].r = set(p, val, mid + 1, nr, t[v].r);
        t[u].val = t[t[u].l].val + t[t[u].r].val;
        return u;
    }
    void set(int p, ll val) {
        // goal: create new version from last with a[p] = val.
        root.push_back(set(p, val, 1, n, root.back()));
    }
    ll query(int l, int r, int v, int nl, int nr) const {
        // result: sum on [l, r] in a specific version.
        if (v == 0 || r < nl || nr < l) return 0;
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
