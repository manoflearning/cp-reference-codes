// INPUT: There is an initially empty multiset A. And given N queries. 
// Each query is of the form (1 B) or (2 B C).
// If the first number is 1, find the B-th smallest number in A.
// If the first number is 2, add the number B to A C times (C can be negative).
// OUTPUT: Given the query (1 B), output the B-th smallest number in A.
// TIME COMPLEXITY: O(logn) for initialize segment tree, O(logn) for each query.

// BOJ 2243 AC Code
// https://www.acmicpc.net/problem/2243

#include <bits/stdc++.h>
using namespace std;
#define ll long long

int flag;  // array size
struct Seg {
    vector<ll> t;
    void build(int n) {
        for (flag = 1; flag < n; flag <<= 1);
        t.resize(flag << 1);
    }
    void add(int p, ll value) {  // add value at position p
        for (t[p += flag - 1] += value; p > 1; p >>= 1) t[p >> 1] = t[p] + t[p ^ 1];
    }
    ll kth(ll k, int n = 1) { // find the kth smallest number (1-indexed)
        assert(t[n] >= k);
        if (flag <= n) return n - flag + 1;
        if (k <= t[n << 1]) return kth(k, n << 1);
        else return kth(k - t[n << 1], n << 1 | 1);
    }
}seg;

int main() {
    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    int n; cin >> n;
    seg.build(1000000);
    for (int i = 0; i < n; i++) {
        int op, x, y;
        cin >> op >> x;
        if (op == 1) {
            int res = seg.kth(x);
            cout << res << '\n';
            seg.add(res, -1);
        }
        if (op == 2) {
            cin >> y;
            seg.add(x, y);
        }
    }
}