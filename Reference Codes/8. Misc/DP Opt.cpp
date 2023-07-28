// Convex Hull Trick
// Recurrence: dp[i] = min(dp[j] + a[i] * b[j]) (j < i)
// Condition: b[i] >= b[i + 1]
// Naive Complexity: O(n^2)
// Optimized Complexity: O(nlogn) (if a[i] <= a[i + 1], it can also be done in O(n))

// BOJ 13263 AC Code
// https://www.acmicpc.net/problem/13263
#include <bits/stdc++.h>
using namespace std;
#define ll long long
struct Line { // f(x) = px + q, x >= s
    ll p, q; 
    double s;
    Line(): Line(1, 0) {}
    Line(ll sp, ll sq): p(sp), q(sq), s(0) {}
};
double cross(const Line& u, const Line& v) {
    return (double)(v.q - u.q) / (u.p - v.p);
}
int n;
ll a[101010], b[101010];
ll dp[101010];
Line ch[101010];
void input() {
    cin >> n;
    for (int i = 1; i <= n; i++) cin >> a[i];
    for (int i = 1; i <= n; i++) cin >> b[i];
}
void convexHullTrick() {
    int top = 1;
    for (int i = 2; i <= n; i++) {
        Line g(b[i - 1], dp[i - 1]);
        while (top > 1) {
            g.s = cross(ch[top - 1], g);
            if (ch[top - 1].s < g.s) break;
            --top;
        }
        ch[top++] = g;
        int l = 1, r = top - 1;
        while (l < r) {
            int mid = (l + r + 1) >> 1;
            if (a[i] < ch[mid].s) r = mid - 1;
            else l = mid;
        }
        int fpos = l;
        dp[i] = ch[fpos].p * a[i] + ch[fpos].q;
    }
}
int main() {
    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);
    input();
    convexHullTrick();
    cout << dp[n];
}

// Knuth Optimization
// Recurrence: DP[i][j] = min(DP[i][k] + DP[k + 1][j]) + C[i][j] (i <= k < j)
// Condition: C[i][j] is a monge array (satisfies C[a][c] + C[b][d] <= C[a][d] + C[b][c]),
//            and satisfies C[a][d] >= C[b][c] for a <= b <= c <= d
// Naive Complexity: O(n^3)
// Optimized Complexity: O(n^2)

// Let opt[i][j] be the value of k that minimizes DP[i][j]
// The following holds: opt[i][j - 1] <= opt[i][j] <= opt[i + 1][j]

// BOJ 13974 AC Code
// https://www.acmicpc.net/problem/13974
#include <bits/stdc++.h>
using namespace std;
#define ll long long
const ll INF = 1e18;
int n, opt[5050][5050];
ll a[5050], DP[5050][5050], psum[5050];
int main() {
    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);
    int tc; cin >> tc;
    while (tc--) {
        cin >> n;
        for (int i = 1; i <= n; i++) {
            cin >> a[i];
            psum[i] = a[i] + psum[i - 1];
        }
        for (int i = 1; i <= n; i++) {
            DP[i][i] = 0;
            opt[i][i] = i;
        }
        for (int i = n - 1; i >= 1; i--) {
            for (int j = i + 1; j <= n; j++) {
                ll mn = INF, mnk = -1;
                for (int k = opt[i][j - 1]; k <= opt[i + 1][j]; k++) {
                    ll res = DP[i][k] + DP[k + 1][j] + (psum[j] - psum[i - 1]);
                    if (res < mn) {
                        mn = res;
                        mnk = k;
                    }
                }
                DP[i][j] = mn;
                opt[i][j] = mnk;
            }
        }
        cout << DP[1][n] << '\n';
    }
}

// Divide and Conquer Optimization 
// Recurrence: dp[t][i] = min(dp[t - 1][j] + c[j][i]) (j < i)
// Condition: Let opt[t][i] be j with the smallest value of dp[t - 1][j] + c[j][i]. It must satisfy opt[t][i] <= opt[t][i + 1].
// Naive Complexity: O(m * n^2)
// Optimized Complexity: O(m * nlogn)

// BOJ 13261 AC Code
// https://www.acmicpc.net/problem/13261
#include <bits/stdc++.h>
using namespace std;
#define ll long long
const ll INF = 1e18;
int n, m;
ll a[8080], psum[8080];
ll dp[808][8080];
void f(int gr, int l, int r, int nl, int nr) {
    int mid = (l + r) >> 1, idx = -1;
    ll& res = dp[gr][mid];
    res = INF;
    for (int i = nl; i <= min(mid, nr); i++) {
        assert(i <= mid);
        ll val = dp[gr - 1][i] + (mid - i) * (psum[mid] - psum[i]);
        if (res > val) {
            res = val, idx = i;
        }
    }
    if (l < r) {
        f(gr, l, mid, nl, idx);
        f(gr, mid + 1, r, idx, nr);
    }
}
int main() {
    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);
    // input
    cin >> n >> m;
    for (int i = 1; i <= n; i++) cin >> a[i];
    // build prefix sum
    for (int i = 1; i <= n; i++) 
        psum[i] = a[i] + psum[i - 1];
    // dp (dnc opt)
    for (int i = 1; i <= n; i++)
        dp[1][i] = i * psum[i];
    for (int i = 2; i <= m; i++)
        f(i, 0, n, 0, n);
    // output
    cout << dp[m][n];
}