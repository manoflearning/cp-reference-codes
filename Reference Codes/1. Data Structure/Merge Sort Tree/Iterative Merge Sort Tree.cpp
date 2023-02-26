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
    int query(int l, int r, int k) { // 1-indexed, query on interval [l, r]
        l += MAX, r += MAX;
        int ret = 0;
        while (l <= r) {
            if (l & 1) ret += t[l].end() - upper_bound(all(t[l]), k), l++;
            if (~r & 1) ret += t[r].end() - upper_bound(all(t[r]), k), r--;
            l >>= 1, r >>= 1;
        }
        return ret;
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