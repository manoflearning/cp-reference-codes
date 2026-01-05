#include "../0-common/common.hpp"
constexpr int MAX_MST = 1 << 17;

// what: static range count queries by storing sorted lists on a segment tree.
// time: build O(n log n), query O(log^2 n); memory: O(n log n)
// constraint: MAX_MST >= n; values fit in int; 0-indexed [l, r]; build once.
// usage: merge_seg st; st.build(a); st.query(l, r, k);
struct merge_seg {
    vector<int> t[MAX_MST << 1];
    void build(const vector<int> &a) {
        // goal: build sorted lists for each node.
        for (int i = 0; i < sz(a); i++)
            t[i + MAX_MST].push_back(a[i]);
        for (int i = MAX_MST - 1; i >= 1; i--) {
            t[i].resize(sz(t[i << 1]) + sz(t[i << 1 | 1]));
            merge(all(t[i << 1]), all(t[i << 1 | 1]), t[i].begin());
        }
    }
    int query(int l, int r, int k, int v = 1, int nl = 0, int nr = MAX_MST - 1) const {
        // result: count of elements > k in [l, r].
        if (nr < l || r < nl) return 0;
        if (l <= nl && nr <= r)
            return int(t[v].end() - upper_bound(all(t[v]), k));
        int mid = (nl + nr) >> 1;
        return query(l, r, k, v << 1, nl, mid) + query(l, r, k, v << 1 | 1, mid + 1, nr);
    }
};

// what: iterative merge sort tree for static range count queries.
// time: build O(n log n), query O(log^2 n); memory: O(n log n)
// constraint: MAX_MST >= n; values fit in int; 0-indexed [l, r]; build once.
// usage: merge_seg_it st; st.build(a); st.query(l, r, k);
struct merge_seg_it {
    vector<int> t[MAX_MST << 1];
    void build(const vector<int> &a) {
        // goal: build sorted lists for each node.
        for (int i = 0; i < sz(a); i++)
            t[i + MAX_MST].push_back(a[i]);
        for (int i = MAX_MST - 1; i >= 1; i--) {
            t[i].resize(sz(t[i << 1]) + sz(t[i << 1 | 1]));
            merge(all(t[i << 1]), all(t[i << 1 | 1]), t[i].begin());
        }
    }
    int query(int l, int r, int k) const {
        // result: count of elements > k in [l, r].
        l += MAX_MST, r += MAX_MST;
        int ret = 0;
        while (l <= r) {
            if (l & 1) ret += int(t[l].end() - upper_bound(all(t[l]), k)), l++;
            if (~r & 1) ret += int(t[r].end() - upper_bound(all(t[r]), k)), r--;
            l >>= 1, r >>= 1;
        }
        return ret;
    }
};
