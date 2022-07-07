// BOJ 13537 AC Code
// https://www.acmicpc.net/problem/13537
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
#define sz(x) (int)(x).size()
#define all(c) (c).begin(), (c).end()

const int MAX = 1 << 17;

struct MergeSortTree {
    vector<int> tree[MAX << 1];

    void build(const vector<int>& arr) {
        for (int i = 0; i < sz(arr); i++) 
            tree[i + 1 + MAX].push_back(arr[i]);

        for (int i = MAX - 1; i >= 1; i--) {
            tree[i].resize(sz(tree[i << 1]) + sz(tree[i << 1 | 1]));
            merge(all(tree[i << 1]), all(tree[i << 1 | 1]), tree[i].begin());
        }
    }

    int query(int l, int r, int k, int n = 1, int nl = 0, int nr = MAX - 1) { // 0-indexed, query on interval [l, r]
        if (nr < l || r < nl) return 0;
        if (l <= nl && nr <= r)
            return tree[n].end() - upper_bound(all(tree[n]), k);

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