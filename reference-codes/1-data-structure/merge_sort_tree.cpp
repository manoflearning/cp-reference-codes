// 1. Merge Sort Tree
// INPUT: Given a sequence A_1, A_2, ..., A_n of length n. Given a query (i, j, k).
// OUTPUT: For each query (i, j, k), output the number of elements greater than k among elements A_i, A_{i+1}, ..., A_j.
// TIME COMPLEXITY: O(nlogn) for initialize Merge Sort Tree, O(log^2n) for each query.
const int MAX_MST = 1 << 17;
struct MergeSortTree {
    vector<int> t[MAX_MST << 1];
    void build(const vector<int>& arr) {
        for (int i = 0; i < sz(arr); i++) 
            t[i + 1 + MAX_MST].push_back(arr[i]);
        for (int i = MAX_MST - 1; i >= 1; i--) {
            t[i].resize(sz(t[i << 1]) + sz(t[i << 1 | 1]));
            merge(all(t[i << 1]), all(t[i << 1 | 1]), t[i].begin());
        }
    }
    int query(int l, int r, int k, int n = 1, int nl = 0, int nr = MAX_MST - 1) { // 0-indexed, query on interval [l, r]
        if (nr < l || r < nl) return 0;
        if (l <= nl && nr <= r)
            return t[n].end() - upper_bound(all(t[n]), k);
        int mid = (nl + nr) >> 1;
        return query(l, r, k, n << 1, nl, mid) + query(l, r, k, n << 1 | 1, mid + 1, nr);
    }
}mstree;

// 2. Iterative Merge Sort Tree
// INPUT: Given a sequence A_1, A_2, ..., A_n of length n. Given a query (i, j, k).
// OUTPUT: For each query (i, j, k), output the number of elements greater than k among elements A_i, A_{i+1}, ..., A_j.
// TIME COMPLEXITY: O(nlogn) for initialize Merge Sort Tree, O(log^2n) for each query.
const int MAX_MST = 1 << 17;
struct MergeSortTree {
    vector<int> t[MAX_MST << 1];
    void build(const vector<int>& arr) {
        for (int i = 0; i < sz(arr); i++) 
            t[i + 1 + MAX_MST].push_back(arr[i]);
        for (int i = MAX_MST - 1; i >= 1; i--) {
            t[i].resize(sz(t[i << 1]) + sz(t[i << 1 | 1]));
            merge(all(t[i << 1]), all(t[i << 1 | 1]), t[i].begin());
        }
    }
    int query(int l, int r, int k) { // 1-indexed, query on interval [l, r]
        l += MAX_MST, r += MAX_MST;
        int ret = 0;
        while (l <= r) {
            if (l & 1) ret += t[l].end() - upper_bound(all(t[l]), k), l++;
            if (~r & 1) ret += t[r].end() - upper_bound(all(t[r]), k), r--;
            l >>= 1, r >>= 1;
        }
        return ret;
    }
}mstree;