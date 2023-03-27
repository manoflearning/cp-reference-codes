// INPUT: Given an array of integers of size N.
// Given the query (1 i v) or (2 k i j)
// If the first number is 1, change the value of the ith element to v.
// If the first number is 2, find the sum of the elements in the interval [i, j], when applied up to the kth query (1 i v).
// OUTPUT: Given the query (2 k i j), output the sum of the elements in the interval [i, j], when applied up to the kth query (1 i v).
// TIME COMPLEXITY: O(n) for initialize PST, O(logn) for each query.
// SPACE COMPLEXITY: O(nlogm).

// BOJ 16978 AC Code
// https://www.acmicpc.net/problem/16978

#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define sz(x) (int)(x).size()

vector<ll> a;

struct PST { // 1-indexed
    int flag; // array size
    struct Node { int l, r; ll val; };
    vector<Node> t;
    vector<int> root;

    void addNode() { t.push_back({ -1, -1, 0 }); }
    void build(int l, int r, int n)  {
        assert(0 <= n && n < sz(t));
        if (l == r) { t[n].val = a[l]; return; }
        addNode();
        t[n].l = sz(t) - 1;
        addNode();
        t[n].r = sz(t) - 1;

        int mid = (l + r) >> 1;
        build(l, mid, t[n].l);
        build(mid + 1, r, t[n].r);
        t[n].val = t[t[n].l].val + t[t[n].r].val;
    }
    void build(int Flag) {
        addNode();
        root.push_back(sz(t) - 1);
        flag = Flag;
        build(1, flag, root[0]);
    }
    void modify(int p, ll val, int l, int r, int n1, int n2) {
        assert(0 <= n1 && n1 < sz(t));
        assert(0 <= n2 && n2 < sz(t));
        if (p < l || r < p) { t[n2] = t[n1]; return; }
        if (l == r) { t[n2].val = val; return; }

        int mid = (l + r) >> 1;
        if (p <= mid) {
            t[n2].r = t[n1].r;
            addNode();
            t[n2].l = sz(t) - 1;
            modify(p, val, l, mid, t[n1].l, t[n2].l);
        }
        else {
            t[n2].l = t[n1].l;
            addNode();
            t[n2].r = sz(t) - 1;
            modify(p, val, mid + 1, r, t[n1].r, t[n2].r);
        }
        t[n2].val = t[t[n2].l].val + t[t[n2].r].val;
    }
    void modify(int p, ll val) {
        addNode();
        root.push_back(sz(t) - 1);
        modify(p, val, 1, flag, root[sz(root) - 2], root[sz(root) - 1]);
    }
    ll query(int l, int r, int n, int nl, int nr) {
        assert(0 <= n && n < sz(t));
        if (r < nl || nr < l) return 0;
        if (l <= nl && nr <= r) return t[n].val;
        int mid = (nl + nr) >> 1;
        return query(l, r, t[n].l, nl, mid) + query(l, r, t[n].r, mid + 1, nr);
    }
    ll query(int l, int r, int n) {
        assert(n < sz(root));
        return query(l, r, root[n], 1, flag);
    }
}pst;

int n;

int main() {
    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    cin >> n;
    a.resize(n + 1);
    for (int i = 1; i <= n; i++) cin >> a[i];

    pst.build(n);

    int m; cin >> m;
    while (m--) {
        int op, x, y, z;
        cin >> op >> x >> y;
        if (op == 1) pst.modify(x, y);
        if (op == 2) {
            cin >> z;
            cout << pst.query(y, z, x) << '\n';
        }
    }
}