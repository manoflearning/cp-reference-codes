// INPUT: Given a sequence A_1, A_2, ..., A_n of length n. Given a query (i, j, k).
// OUTPUT: For each query (i, j, k), output the number of elements greater than k among elements A_i, A_{i+1}, ..., A_j.
// TIME COMPLEXITY: O(nlogn) for initialize Merge Sort Tree, O(log^2n) for each query.

// BOJ 13537 AC Code
// https://www.acmicpc.net/problem/13537

#include <bits/stdc++.h>
using namespace std;
#define sz(x) (int)(x).size()
#define all(c) (c).begin(), (c).end()

const int MAX = 1 << 17;

struct MergeSortTree {
    vector<int> t[MAX << 1];
    void build(const vector<int>& arr) {
        for (int i = 0; i < sz(arr); i++) 
            t[i + 1 + MAX].push_back(arr[i]);
        for (int i = MAX - 1; i >= 1; i--) {
            t[i].resize(sz(t[i << 1]) + sz(t[i << 1 | 1]));
            merge(all(t[i << 1]), all(t[i << 1 | 1]), t[i].begin());
        }
    }
    int query(int l, int r, int k, int n = 1, int nl = 0, int nr = MAX - 1) { // 0-indexed, query on interval [l, r]
        if (nr < l || r < nl) return 0;
        if (l <= nl && nr <= r)
            return t[n].end() - upper_bound(all(t[n]), k);
        int mid = (nl + nr) >> 1;
        return query(l, r, k, n << 1, nl, mid) + query(l, r, k, n << 1 | 1, mid + 1, nr);
    }
}mstree;

int n;
vector<int> arr;

int main() {
    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    cin >> n;
    arr.resize(n);
    for (auto& i : arr) cin >> i;

    mstree.build(arr);

    int q; cin >> q;
    while (q--) {
        int a, b, c;
        cin >> a >> b >> c;
        int ans = mstree.query(a, b, c);
        cout << ans << '\n';
    }
 
    return 0;
}