// BOJ 13263 AC Code
// https://www.acmicpc.net/problem/13263
#include <bits/stdc++.h>
using namespace std;
#define ll long long

struct lf { // f(x) = px + q, x >= s
    ll p, q; 
    double s;
    lf(): lf(1, 0) {}
    lf(ll sp, ll sq): p(sp), q(sq), s(0) {}
};

double cross(const lf& u, const lf& v) {
    return (double)(v.q - u.q) / (u.p - v.p);
}

int n;
ll a[101010], b[101010];
ll dp[101010];
lf ch[101010];

void input() {
    cin >> n;
    for (int i = 1; i <= n; i++) cin >> a[i];
    for (int i = 1; i <= n; i++) cin >> b[i];
}

void convexHullTrick() {
    int top = 1;
    for (int i = 2; i <= n; i++) {
        lf g(b[i - 1], dp[i - 1]);
        while (top > 1) {
            g.s = cross(ch[top - 1], g);
            if (ch[top - 1].s < g.s) break;
            --top;
        }
        ch[top++] = g;

        ll x = a[i];
        int fpos = top - 1;
        if (x < ch[top - 1].s) {
            int l = 0, r = top - 1;
            while (l < r) {
                int mid = (l + r + 1) >> 1;
                if (x < ch[mid].s) r = mid - 1;
                else l = mid;
            }
            fpos = l;
        }
        dp[i] = ch[fpos].p * x + ch[fpos].q;
    }
}

int main() {
    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    input();

    convexHullTrick();

    cout << dp[n];

    return 0;
}