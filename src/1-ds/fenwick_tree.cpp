#include "../common/common.hpp"

// what: fenwick tree (point add, prefix/range sum).
// time: build O(n), update/query O(log n); memory: O(n)
// constraint: 0-indexed; kth needs all values >= 0.
// usage: fenw fw; fw.build(a); fw.add(p, x); fw.sum(l, r); fw.kth(k);
struct fenw {
    int n;
    vector<ll> a, t;
    void init(int n_) {
        n = n_;
        a.assign(n, 0);
        t.assign(n, 0);
    }
    void build(const vector<ll> &v) {
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
        a[p] += val;
        for (int i = p; i < n; i |= i + 1) t[i] += val;
    }
    void set(int p, ll val) { add(p, val - a[p]); }
    ll sum(int x) const {
        ll ret = 0;
        for (int i = x; i >= 0; i = (i & (i + 1)) - 1) ret += t[i];
        return ret;
    }
    ll sum(int l, int r) const { return sum(r) - (l ? sum(l - 1) : 0); }
    int kth(ll k) const {
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

// what: fenwick tree (range add, point get).
// time: update/query O(log n); memory: O(n)
// constraint: 1-indexed; l <= r.
// usage: fenw_rp fw; fw.init(n); fw.add(l, r, x); ll v = fw.get(p);
struct fenw_rp { // 1-indexed
    int n;
    vector<ll> t;
    void init(int n_) {
        n = n_;
        t.assign(n + 1, 0);
    }
    void add(int l, int r, ll val) {
        for (; l <= n; l += l & -l) t[l] += val;
        for (r++; r <= n; r += r & -r) t[r] -= val;
    }
    ll get(int x) const {
        ll ret = 0;
        for (; x; x ^= x & -x) ret += t[x];
        return ret;
    }
};

// what: 2D fenwick tree (point add, rectangle sum).
// time: build O(n m), update/query O(log n log m); memory: O(n m)
// constraint: 0-indexed; no bounds check.
// usage: fenw2d fw; fw.build(a); fw.add(x, y, v); fw.sum(x1, y1, x2, y2);
struct fenw2d { // 0-indexed
    int n, m;
    vector<vector<ll>> a, t;
    void init(int n_, int m_) {
        n = n_, m = m_;
        a.assign(n, vector<ll>(m, 0));
        t.assign(n, vector<ll>(m, 0));
    }
    void build(const vector<vector<ll>> &v) {
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
        a[x][y] += val;
        for (int i = x; i < n; i |= i + 1)
            for (int j = y; j < m; j |= j + 1) t[i][j] += val;
    }
    void set(int x, int y, ll val) { add(x, y, val - a[x][y]); }
    ll sum(int x, int y) const {
        ll ret = 0;
        for (int i = x; i >= 0; i = (i & (i + 1)) - 1)
            for (int j = y; j >= 0; j = (j & (j + 1)) - 1) ret += t[i][j];
        return ret;
    }
    ll sum(int x1, int y1, int x2, int y2) const {
        ll ret = sum(x2, y2);
        if (x1) ret -= sum(x1 - 1, y2);
        if (y1) ret -= sum(x2, y1 - 1);
        if (x1 && y1) ret += sum(x1 - 1, y1 - 1);
        return ret;
    }
};
