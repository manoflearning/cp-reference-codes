#include "../common/common.hpp"

// what: segment tree (point set, range sum).
// time: build O(n), update/query O(log n); memory: O(n)
// constraint: 1-indexed [1, n]; a[0] unused.
// usage: segt st; st.build(a); st.set(p, v); st.query(l, r);
struct segt {
    int flag;
    vector<ll> t;
    void build(const vector<ll> &a) {
        int n = sz(a) - 1;
        flag = 1;
        while (flag < n) flag <<= 1;
        t.assign(2 * flag, 0);
        for (int i = 1; i <= n; i++) t[flag + i - 1] = a[i];
        for (int i = flag - 1; i >= 1; i--) t[i] = t[i << 1] + t[i << 1 | 1];
    }
    void set(int p, ll val) {
        for (t[p += flag - 1] = val; p > 1; p >>= 1) t[p >> 1] = t[p] + t[p ^ 1];
    }
    ll query(int l, int r) const { return query(l, r, 1, 1, flag); }
    ll query(int l, int r, int v, int nl, int nr) const {
        if (r < nl || nr < l) return 0;
        if (l <= nl && nr <= r) return t[v];
        int mid = (nl + nr) >> 1;
        return query(l, r, v << 1, nl, mid) + query(l, r, v << 1 | 1, mid + 1, nr);
    }
};

// what: iter segment tree (point set, range sum).
// time: build O(n), update/query O(log n); memory: O(n)
// constraint: 0-indexed [l, r).
// usage: segti st; st.build(a); st.set(p, v); st.query(l, r);
struct segti { // 0-indexed
    int n;
    vector<ll> t;
    void build(const vector<ll> &a) {
        n = sz(a);
        t.assign(2 * n, 0);
        for (int i = 0; i < n; i++) t[n + i] = a[i];
        for (int i = n - 1; i >= 1; i--) t[i] = t[i << 1] + t[i << 1 | 1];
    }
    void set(int p, ll val) {
        for (t[p += n] = val; p > 1; p >>= 1) t[p >> 1] = t[p] + t[p ^ 1];
    }
    ll query(int l, int r) const {
        ll ret = 0;
        for (l += n, r += n; l < r; l >>= 1, r >>= 1) {
            if (l & 1) ret += t[l++];
            if (r & 1) ret += t[--r];
        }
        return ret;
    }
};

// what: segment tree for kth on freq array.
// time: update/query O(log n); memory: O(n)
// constraint: 1-indexed [1, n], values >= 0.
// usage: segk st; st.init(n); st.add(p, v); st.kth(k);
struct segk {
    int flag;
    vector<ll> t;
    void init(int n) {
        flag = 1;
        while (flag < n) flag <<= 1;
        t.assign(flag << 1, 0);
    }
    void add(int p, ll val) {
        for (t[p += flag - 1] += val; p > 1; p >>= 1) t[p >> 1] = t[p] + t[p ^ 1];
    }
    ll kth(ll k, int v = 1) const {
        assert(t[v] >= k);
        if (v >= flag) return v - flag + 1;
        if (k <= t[v << 1]) return kth(k, v << 1);
        return kth(k - t[v << 1], v << 1 | 1);
    }
};

// what: segment tree with range add + range sum.
// time: update/query O(log n); memory: O(n)
// constraint: 1-indexed [1, n]; a[0] unused.
// usage: seglz st; st.build(a); st.add(l, r, v); st.query(l, r);
struct seglz {
    int flag;
    vector<ll> t, lz;
    void build(const vector<ll> &a) {
        int n = sz(a) - 1;
        flag = 1;
        while (flag < n) flag <<= 1;
        t.assign(2 * flag, 0);
        lz.assign(2 * flag, 0);
        for (int i = 1; i <= n; i++) t[flag + i - 1] = a[i];
        for (int i = flag - 1; i >= 1; i--) t[i] = t[i << 1] + t[i << 1 | 1];
    }
    void add(int l, int r, ll val) { add(l, r, val, 1, 1, flag); }
    ll query(int l, int r) { return query(l, r, 1, 1, flag); }
    void add(int l, int r, ll val, int v, int nl, int nr) {
        push(v, nl, nr);
        if (r < nl || nr < l) return;
        if (l <= nl && nr <= r) {
            lz[v] += val;
            push(v, nl, nr);
            return;
        }
        int mid = (nl + nr) >> 1;
        add(l, r, val, v << 1, nl, mid);
        add(l, r, val, v << 1 | 1, mid + 1, nr);
        t[v] = t[v << 1] + t[v << 1 | 1];
    }
    ll query(int l, int r, int v, int nl, int nr) {
        push(v, nl, nr);
        if (r < nl || nr < l) return 0;
        if (l <= nl && nr <= r) return t[v];
        int mid = (nl + nr) >> 1;
        return query(l, r, v << 1, nl, mid) + query(l, r, v << 1 | 1, mid + 1, nr);
    }
    void push(int v, int nl, int nr) {
        if (lz[v] == 0) return;
        if (v < flag) {
            lz[v << 1] += lz[v];
            lz[v << 1 | 1] += lz[v];
        }
        t[v] += lz[v] * (nr - nl + 1);
        lz[v] = 0;
    }
};

// what: persistent segment tree (point set, range sum).
// time: build O(n), update/query O(log n); memory: O(n log n)
// constraint: 1-indexed [1, n]; a[0] unused.
// usage: pst st; st.build(n, a); st.set(p, v); st.query(l, r, ver);
struct pst {
    struct node {
        int l, r;
        ll val;
    };
    int n;
    vector<node> t;
    vector<int> root;

    void newnd() { t.push_back({-1, -1, 0}); }
    void build(int n_, const vector<ll> &a) {
        n = n_;
        t.clear();
        root.clear();
        newnd();
        root.push_back(0);
        build(1, n, root[0], a);
    }
    void build(int l, int r, int v, const vector<ll> &a) {
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
        newnd();
        root.push_back(sz(t) - 1);
        set(p, val, 1, n, root[sz(root) - 2], root.back());
    }
    void set(int p, ll val, int l, int r, int v1, int v2) {
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
        if (r < nl || nr < l) return 0;
        if (l <= nl && nr <= r) return t[v].val;
        int mid = (nl + nr) >> 1;
        return query(l, r, t[v].l, nl, mid) + query(l, r, t[v].r, mid + 1, nr);
    }
    ll query(int l, int r, int ver) const { return query(l, r, root[ver], 1, n); }
};

// what: dynamic seg tree (sparse, point add, range sum).
// time: update/query O(log R); memory: O(k log R)
// constraint: range [MAXL, MAXR], missing child => 0.
// usage: dyseg st; st.add(p, v); st.query(l, r);
constexpr int MAXL = 1, MAXR = 1000000;
struct dnode {
    ll x;
    int l, r;
};
struct dyseg {
    vector<dnode> t = {{0, -1, -1}, {0, -1, -1}};
    void add(int p, ll x, int v = 1, int nl = MAXL, int nr = MAXR) {
        if (p < nl || nr < p) return;
        t[v].x += x;
        if (nl == nr) return;
        int mid = (nl + nr) >> 1;
        if (p <= mid) {
            if (t[v].l == -1) {
                t[v].l = sz(t);
                t.push_back({0, -1, -1});
            }
            add(p, x, t[v].l, nl, mid);
        } else {
            if (t[v].r == -1) {
                t[v].r = sz(t);
                t.push_back({0, -1, -1});
            }
            add(p, x, t[v].r, mid + 1, nr);
        }
    }
    ll query(int l, int r, int v = 1, int nl = MAXL, int nr = MAXR) const {
        if (v == -1 || r < nl || nr < l) return 0;
        if (l <= nl && nr <= r) return t[v].x;
        int mid = (nl + nr) >> 1;
        ll ret = 0;
        if (l <= mid && t[v].l != -1) ret += query(l, r, t[v].l, nl, mid);
        if (mid + 1 <= r && t[v].r != -1) ret += query(l, r, t[v].r, mid + 1, nr);
        return ret;
    }
};

// what: 2D segment tree (point set, rect sum).
// time: build O(n^2), update/query O(log^2 n); memory: O(n^2)
// constraint: 0-indexed square n x n.
// usage: seg2d st; st.build(a); st.set(x, y, v); st.query(x1, x2, y1, y2);
struct seg2d { // 0-indexed
    int n;
    vector<vector<ll>> t;
    void build(const vector<vector<ll>> &a) {
        n = sz(a);
        t.assign(2 * n, vector<ll>(2 * n, 0));
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                t[i + n][j + n] = a[i][j];
        for (int i = n; i < 2 * n; i++)
            for (int j = n - 1; j > 0; j--)
                t[i][j] = t[i][j << 1] + t[i][j << 1 | 1];
        for (int i = n - 1; i > 0; i--)
            for (int j = 1; j < 2 * n; j++)
                t[i][j] = t[i << 1][j] + t[i << 1 | 1][j];
    }
    void set(int x, int y, ll val) {
        t[x + n][y + n] = val;
        for (int j = y + n; j > 1; j >>= 1)
            t[x + n][j >> 1] = t[x + n][j] + t[x + n][j ^ 1];
        for (x += n; x > 1; x >>= 1)
            for (int j = y + n; j >= 1; j >>= 1)
                t[x >> 1][j] = t[x][j] + t[x ^ 1][j];
    }
    ll qry1d(int x, int y1, int y2) const {
        ll ret = 0;
        for (y1 += n, y2 += n + 1; y1 < y2; y1 >>= 1, y2 >>= 1) {
            if (y1 & 1) ret += t[x][y1++];
            if (y2 & 1) ret += t[x][--y2];
        }
        return ret;
    }
    ll query(int x1, int x2, int y1, int y2) const {
        ll ret = 0;
        for (x1 += n, x2 += n + 1; x1 < x2; x1 >>= 1, x2 >>= 1) {
            if (x1 & 1) ret += qry1d(x1++, y1, y2);
            if (x2 & 1) ret += qry1d(--x2, y1, y2);
        }
        return ret;
    }
};

// what: 2D seg tree with coord comp (offline).
// time: prep O(q log q), update/query O(log^2 n); memory: O(q log q)
// constraint: call fmod/fqry first, then prep, then set/query.
// usage: seg2dc st(n); st.fmod(x, y); st.fqry(x1, x2, y1, y2); st.prep(); st.set(x, y, v); st.query(x1, x2, y1, y2);
struct seg2dc { // 0-indexed
    int n;
    vector<vector<ll>> a;
    vector<vector<int>> used;
    unordered_map<ll, ll> mp;
    seg2dc(int n) : n(n), a(2 * n), used(2 * n) {}
    void fmod(int x, int y) {
        for (x += n; x >= 1; x >>= 1) used[x].push_back(y);
    }
    void fqry(int x1, int x2, int y1, int y2) {
        for (x1 += n, x2 += n + 1; x1 < x2; x1 >>= 1, x2 >>= 1) {
            if (x1 & 1) {
                used[x1].push_back(y1);
                used[x1++].push_back(y2);
            }
            if (x2 & 1) {
                used[--x2].push_back(y1);
                used[x2].push_back(y2);
            }
        }
    }
    void prep() {
        for (int i = 0; i < 2 * n; i++) {
            if (!used[i].empty()) {
                sort(all(used[i]));
                used[i].erase(unique(all(used[i])), used[i].end());
            }
            used[i].shrink_to_fit();
            a[i].assign(sz(used[i]) << 1, 0);
        }
    }
    void set(int x, int y, ll v) {
        ll k = (ll)x << 32 | (unsigned)y;
        ll d = v - mp[k];
        mp[k] = v;
        for (x += n; x >= 1; x >>= 1) {
            int i = lower_bound(all(used[x]), y) - used[x].begin() + sz(used[x]);
            for (a[x][i] += d; i > 1; i >>= 1)
                a[x][i >> 1] = a[x][i] + a[x][i ^ 1];
        }
    }
    ll qry1d(int x, int y1, int y2) const {
        ll ret = 0;
        y1 = lower_bound(all(used[x]), y1) - used[x].begin();
        y2 = lower_bound(all(used[x]), y2) - used[x].begin();
        for (y1 += sz(used[x]), y2 += sz(used[x]) + 1; y1 < y2; y1 >>= 1, y2 >>= 1) {
            if (y1 & 1) ret += a[x][y1++];
            if (y2 & 1) ret += a[x][--y2];
        }
        return ret;
    }
    ll query(int x1, int x2, int y1, int y2) const {
        ll ret = 0;
        for (x1 += n, x2 += n + 1; x1 < x2; x1 >>= 1, x2 >>= 1) {
            if (x1 & 1) ret += qry1d(x1++, y1, y2);
            if (x2 & 1) ret += qry1d(--x2, y1, y2);
        }
        return ret;
    }
};
