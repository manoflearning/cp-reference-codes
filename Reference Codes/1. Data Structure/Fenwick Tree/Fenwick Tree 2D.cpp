// INPUT: Given an 2D array of integers of size N * N.
// Given the query (0 x y c) or (1 sx sy ex ey)
// If the first number is 0, change the value of the (x, y)th element to c,
// If the first number is 1, find the sum of elements from (sx, sy) to (ex, ey)
// OUTPUT: Given the query (1 sx sy ex ey), output the sum of elements from the interval (sx, sy) to (ex, ey)
// TIME COMPLEXITY: O(N * N) for initialize fenwick tree, O(logN * logN) for each query.

// BOJ 11658 AC Code
// https://www.acmicpc.net/problem/11658

#include <bits/stdc++.h>
using namespace std;
#define ll long long

struct Fenwick2D { // 0-indexed
    int n, m, real_n, real_m;
    vector<vector<ll>> arr, t;
    void build(int N, int M) {
        real_n = N, real_m = M;

        n = m = 1;
        while (n < N) n <<= 1;
        while (m < M) m <<= 1;
        arr.resize(n, vector<ll>(m));
        t.resize(n, vector<ll>(m));

        for (int i = 0; i < real_n; i++) {
            for (int j = 0; j < real_m; j++) {
                cin >> arr[i][j];
            }
        }
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                t[i][j] += arr[i][j];

                int ni = i | (i + 1), nj = j | (j + 1);
                if (ni < n) t[ni][j] += t[i][j];
                if (nj < m) t[i][nj] += t[i][j];
                if (ni < n && nj < m) t[ni][nj] -= t[i][j];
            }
        }
    }
    void add(int x, int y, ll value) { // add value at position (x, y)
        assert(0 <= x && x < real_n && 0 <= y && y < real_m);
        arr[x][y] += value;
        for (int i = x; i < n; i |= i + 1) {
            for (int j = y; j < m; j |= j + 1) {
                t[i][j] += value;
            }
        }
    }
    void modify(int x, int y, ll value) { // set value at position (x, y)
        assert(0 <= x && x < real_n && 0 <= y && y < real_m);
        add(x, y, value - arr[x][y]);
    }
    ll query(ll x, ll y) {
        assert(0 <= x && x < real_n && 0 <= y && y < real_m);
        ll ret = 0;
        for (int i = x; i >= 0; i = (i & (i + 1)) - 1) {
            for (int j = y; j >= 0; j = (j & (j + 1)) - 1) {
                ret += t[i][j];
            }
        }
        return ret;
    }
    ll query(ll sx, ll sy, ll ex, ll ey) {
        assert(0 <= sx && sx <= ex && ex < real_n);
        assert(0 <= sy && sy <= ey && ey < real_m);
        ll ret = query(ex, ey);
        if (sx) ret -= query(sx - 1, ey);
        if (sy) ret -= query(ex, sy - 1);
        if (sx && sy) ret += query(sx - 1, sy - 1);
        return ret;
    }
}fw2d;

int main() {
    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    int n, m;
    cin >> n >> m;

    fw2d.build(n, n);

    for (int i = 0; i < m; i++) {
        int op; cin >> op;
        if (op == 0) {
            int x, y; ll w;
            cin >> x >> y >> w;
            fw2d.modify(x - 1, y - 1, w);
        }
        if (op == 1) {
            int sx, sy, ex, ey;
            cin >> sx >> sy >> ex >> ey;
            cout << fw2d.query(sx - 1, sy - 1, ex - 1, ey - 1) << '\n';
        }
    }
}