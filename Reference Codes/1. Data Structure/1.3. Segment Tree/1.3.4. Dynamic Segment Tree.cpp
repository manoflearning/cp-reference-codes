// INPUT: Given an array of integers of size N.
// Given the query (a b c)
// If a = 1, change the value of the bth element to c,
// If a = 2, find the sum of the elements in the interval [b, c].
// OUTPUT: Given the query (2 b c), output the sum of elements in the interval [b, c].
// TIME COMPLEXITY: O(n) for initialize segment tree, O(logn) for each query.

// BOJ 2042 AC Code
// https://www.acmicpc.net/problem/2042

#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define sz(x) (int)(x).size()

const int MAXL = 1, MAXR = 1000000;

struct Node {
    ll x; int l, r;
};

struct Dyseg {
    vector<Node> t = { { 0, -1, -1 }, { 0, -1, -1 } };
    void modify(int p, ll x, int n = 1, int nl = MAXL, int nr = MAXR) {
        if (p < nl || nr < p) return;
        t[n].x += x;
        if (nl < nr) {
            int mid = (nl + nr) >> 1;
            if (p <= mid) {
                if (t[n].l == -1) {
                    t[n].l = sz(t);
                    t.push_back({ 0, -1, -1 });
                }
                modify(p, x, t[n].l, nl, mid);
            }
            else {
                if (t[n].r == -1) {
                    t[n].r = sz(t);
                    t.push_back({ 0, -1, -1 });
                }
                modify(p, x, t[n].r, mid + 1, nr);
            }
        }
    }
    ll query(int l, int r, int n = 1, int nl = MAXL, int nr = MAXR) {
        if (r < nl || nr < l) return 0;
        if (l <= nl && nr <= r) return t[n].x;
        int mid = (nl + nr) >> 1;
        ll ret = 0;
        if (l <= mid) {
            if (t[n].l == -1) {
                t[n].l = sz(t);
                t.push_back({ 0, -1, -1 });
            }
            ret += query(l, r, t[n].l, nl, mid);
        }
        if (mid + 1 <= r) {
            if (t[n].r == -1) {
                t[n].r = sz(t);
                t.push_back({ 0, -1, -1 });
            }
            ret += query(l, r, t[n].r, mid + 1, nr);
        }
        return ret;
    }
}dyseg;

ll a[1010101];

int main() {
    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    int n, m, k;
    cin >> n >> m >> k;

    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        dyseg.modify(i, a[i]);
    }

    for (int i = 0; i < m + k; i++) {
        int op; ll x, y;
        cin >> op >> x >> y;
        if (op == 1) {
            dyseg.modify(x, y - a[x]);
            a[x] = y;
        }
        if (op == 2) cout << dyseg.query(x, y) << '\n';
    }
 
    return 0;
}