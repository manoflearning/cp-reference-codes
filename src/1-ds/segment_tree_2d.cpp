#include "../common/common.hpp"
// 1. 2D Segment Tree
struct Seg2D { // 0-indexed
    int n;
    vector<vector<ll>> t;
    Seg2D(int n) : n(n), t(2 * n, vector<ll>(2 * n)) {}
    // You must pass an n x n 2D vector as the argument
    void build(vector<vector<ll>> &val) {
        t.resize(2 * n, vector<ll>(2 * n));
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                t[i + n][j + n] = val[i][j];
        // Handle segments that are leaf nodes of the outer segment tree
        for (int i = n; i < 2 * n; i++)
            for (int j = n - 1; j > 0; j--)
                t[i][j] = t[i][j << 1] + t[i][j << 1 | 1];
        // Handle segments that are non-leaf nodes of the outer segment tree
        for (int i = n - 1; i > 0; i--)
            for (int j = 1; j < 2 * n; j++)
                t[i][j] = t[i << 1][j] + t[i << 1 | 1][j];
    }
    // Change the value at (x, y) to val
    void modify(int x, int y, ll val) {
        t[x + n][y + n] = val;
        // Handle a leaf of the outer segment tree
        for (int i = y + n; i > 1; i >>= 1)
            t[x + n][i >> 1] = t[x + n][i] + t[x + n][i ^ 1];
        // Handle segments that are non-leaf nodes of the outer segment tree
        for (x = x + n; x > 1; x >>= 1)
            for (int i = y + n; i >= 1; i >>= 1)
                t[x >> 1][i] = t[x][i] + t[x ^ 1][i];
    }
    ll query1D(int x, int y1, int y2) {
        ll ret = 0;
        for (y1 += n, y2 += n + 1; y1 < y2; y1 >>= 1, y2 >>= 1) {
            if (y1 & 1) ret += t[x][y1++];
            if (y2 & 1) ret += t[x][--y2];
        }
        return ret;
    }
    // sum on rectangle [x1, x2] × [y1, y2] (0-indexed, inclusive)
    ll query(int x1, int x2, int y1, int y2) {
        ll ret = 0;
        for (x1 += n, x2 += n + 1; x1 < x2; x1 >>= 1, x2 >>= 1) {
            if (x1 & 1) ret += query1D(x1++, y1, y2);
            if (x2 & 1) ret += query1D(--x2, y1, y2);
        }
        return ret;
    }
};
// 2. 2D Segment Tree with Coordinate Compression
// You must perform all fake_* calls first, then call prepare(), and only after that call modify and query
struct Seg2DComp { // 0-indexed
    int n;
    vector<vector<ll>> a;
    vector<vector<int>> used;
    Seg2DComp(int n) : n(n), a(2 * n), used(2 * n) {}
    void fake_modify(int x, int y) {
        for (x += n; x >= 1; x >>= 1)
            used[x].push_back(y);
    }
    void fake_query(int x1, int x2, int y1, int y2) {
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
    void prepare() {
        for (int i = 0; i < 2 * n; i++) {
            if (!used[i].empty()) {
                sort(used[i].begin(), used[i].end());
                used[i].erase(unique(all(used[i])), used[i].end());
            }
            used[i].shrink_to_fit();
            a[i].resize(sz(used[i]) << 1);
        }
    }
    void modify(int x, int y, ll val) {
        for (x += n; x >= 1; x >>= 1) {
            int i = lower_bound(all(used[x]), y) - used[x].begin() + sz(used[x]);
            for (a[x][i] = val; i > 1; i >>= 1) {
                a[x][i >> 1] = a[x][i] + a[x][i ^ 1];
            }
        }
    }
    ll query1D(int x, int y1, int y2) {
        ll ret = 0;
        y1 = lower_bound(all(used[x]), y1) - used[x].begin();
        y2 = lower_bound(all(used[x]), y2) - used[x].begin();
        for (y1 += sz(used[x]), y2 += sz(used[x]) + 1; y1 < y2; y1 >>= 1, y2 >>= 1) {
            if (y1 & 1) ret += a[x][y1++];
            if (y2 & 1) ret += a[x][--y2];
        }
        return ret;
    }
    // sum on rectangle [x1, x2] × [y1, y2] (0-indexed, inclusive)
    ll query(int x1, int x2, int y1, int y2) {
        ll ret = 0;
        for (x1 += n, x2 += n + 1; x1 < x2; x1 >>= 1, x2 >>= 1) {
            if (x1 & 1) ret += query1D(x1++, y1, y2);
            if (x2 & 1) ret += query1D(--x2, y1, y2);
        }
        return ret;
    }
};