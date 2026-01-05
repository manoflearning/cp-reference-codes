#include "../0-common/common.hpp"

// what: maintain prefix sums with point updates and range sum queries.
// time: build O(n), update/query O(log n); memory: O(n)
// constraint: 0-indexed; kth needs all values >= 0.
// usage: fenwick fw; fw.build(a); fw.add(p, x); fw.sum(l, r); fw.kth(k);
struct fenwick {
    int n;
    vector<ll> a, t;
    void init(int n_) {
        // goal: allocate arrays for size n.
        n = n_;
        a.assign(n, 0);
        t.assign(n, 0);
    }
    void build(const vector<ll> &v) {
        // goal: build fenwick in O(n) from initial array.
        n = sz(v);
        a = v;
        t.assign(n, 0);
        for (int i = 0; i < n; i++) {
            t[i] += a[i];
            int j = i | (i + 1);
            if (j < n) t[j] += t[i];
        }
    }
    void add(int p, ll val) {
        // goal: a[p] += val.
        a[p] += val;
        for (int i = p; i < n; i |= i + 1) t[i] += val;
    }
    void set(int p, ll val) { add(p, val - a[p]); }
    ll sum(int x) const {
        // result: prefix sum on [0..x].
        ll ret = 0;
        for (int i = x; i >= 0; i = (i & (i + 1)) - 1) ret += t[i];
        return ret;
    }
    ll sum(int l, int r) const { return sum(r) - (l ? sum(l - 1) : 0); }
    int kth(ll k) const {
        // result: smallest idx with prefix sum >= k.
        assert(k > 0 && sum(n - 1) >= k);
        int idx = -1;
        int bit = 1;
        while (bit < n) bit <<= 1;
        for (; bit; bit >>= 1) {
            int nxt = idx + bit;
            if (nxt < n && t[nxt] < k) {
                idx = nxt;
                k -= t[nxt];
            }
        }
        return idx + 1;
    }
};

// what: support range add and point query via difference fenwick.
// time: update/query O(log n); memory: O(n)
// constraint: 1-indexed; l <= r.
// usage: fenw_range fw; fw.init(n); fw.add(l, r, x); ll v = fw.get(p);
struct fenw_range { // 1-indexed
    int n;
    vector<ll> t;
    void init(int n_) {
        // goal: allocate internal tree (1-indexed).
        n = n_;
        t.assign(n + 1, 0);
    }
    void add(int l, int r, ll val) {
        // goal: add val to all indices in [l, r].
        for (; l <= n; l += l & -l) t[l] += val;
        for (r++; r <= n; r += r & -r) t[r] -= val;
    }
    ll get(int x) const {
        // result: current value at index x.
        ll ret = 0;
        for (; x; x ^= x & -x) ret += t[x];
        return ret;
    }
};

// what: 2D point updates with axis-aligned rectangle sum queries.
// time: build O(n m), update/query O(log n log m); memory: O(n m)
// constraint: 0-indexed; no bounds check.
// usage: fenw_2d fw; fw.build(a); fw.add(x, y, v); fw.sum(x1, y1, x2, y2);
struct fenw_2d { // 0-indexed
    int n, m;
    vector<vector<ll>> a, t;
    void init(int n_, int m_) {
        // goal: allocate arrays for n x m.
        n = n_, m = m_;
        a.assign(n, vector<ll>(m, 0));
        t.assign(n, vector<ll>(m, 0));
    }
    void build(const vector<vector<ll>> &v) {
        // goal: build 2D fenwick in O(n*m).
        n = sz(v);
        m = n ? sz(v[0]) : 0;
        a = v;
        t.assign(n, vector<ll>(m, 0));
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                t[i][j] += a[i][j];
                int ni = i | (i + 1), nj = j | (j + 1);
                if (ni < n) t[ni][j] += t[i][j];
                if (nj < m) t[i][nj] += t[i][j];
                if (ni < n && nj < m) t[ni][nj] -= t[i][j];
            }
        }
    }
    void add(int x, int y, ll val) {
        // goal: a[x][y] += val.
        a[x][y] += val;
        for (int i = x; i < n; i |= i + 1)
            for (int j = y; j < m; j |= j + 1) t[i][j] += val;
    }
    void set(int x, int y, ll val) { add(x, y, val - a[x][y]); }
    ll sum(int x, int y) const {
        // result: sum over rectangle [0..x] x [0..y].
        ll ret = 0;
        for (int i = x; i >= 0; i = (i & (i + 1)) - 1)
            for (int j = y; j >= 0; j = (j & (j + 1)) - 1) ret += t[i][j];
        return ret;
    }
    ll sum(int x1, int y1, int x2, int y2) const {
        // result: sum over rectangle [x1..x2] x [y1..y2].
        ll ret = sum(x2, y2);
        if (x1) ret -= sum(x1 - 1, y2);
        if (y1) ret -= sum(x2, y1 - 1);
        if (x1 && y1) ret += sum(x1 - 1, y1 - 1);
        return ret;
    }
};
