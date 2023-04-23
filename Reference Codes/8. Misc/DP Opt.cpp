// Convex Hull Trick
// Recurrence: dp[i] = min(dp[j] + a[i] * b[j]) (j < i)
// Condition: b[i - 1] >= b[i]
// Naive Complexity: O(n^2)
// Optimized Complexity: O(nlogn) (if a[i] <= a[i + 1], it can also be done in O(n))

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
    return 0;
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
    return 0;
}

// Divide and Conquer Optimization 
// Recurrence: DP[t][i] = min(DP[t - 1][j] + C[j][i]) (1 <= j < n)
// Condition: Let opt[t][i] be j with the smallest value of DP[t - 1][j] + C[j][i]. It must satisfy opt[t][i] <= opt[t][i + 1].
// BOJ 12766 AC Code
// https://www.acmicpc.net/problem/12766
#include <bits/stdc++.h>
using namespace std;
#define ll long long
const ll INF = 1e18;
const int MAX = 5050;
int n, b, s, r;
ll w[MAX], dp[MAX][MAX], psum[MAX];
struct wv {
    ll w; int v;
    bool operator<(const wv& rhs) const {
        return w > rhs.w;
    }
};
vector<wv> adj[MAX], radj[MAX];
void input() {
    cin >> n >> b >> s >> r;
    for (int i = 0; i < r; i++) {
        int u, v, d;
        cin >> u >> v >> d;
        adj[u].push_back({ d, v });
        radj[v].push_back({ d, u });
    }
}
vector<ll> dist(MAX, INF), rdist(MAX, INF);
void dijkstra() {
    priority_queue<wv> pq;
    pq.push({ 0, b + 1 });
    dist[b + 1] = 0;
    while (!pq.empty()) {
        int v = pq.top().v;
        ll w = pq.top().w;
        pq.pop();
        if (w > dist[v]) continue;
        for (auto& i : adj[v]) {
            if (dist[i.v] > w + i.w) {
                dist[i.v] = w + i.w;
                pq.push({ w + i.w, i.v });
            }
        }
    }
    pq.push({ 0, b + 1 });
    rdist[b + 1] = 0;
    while (!pq.empty()) {
        int v = pq.top().v;
        ll w = pq.top().w;
        pq.pop();
        if (w > rdist[v]) continue;
        for (auto& i : radj[v]) {
            if (rdist[i.v] > w + i.w) {
                rdist[i.v] = w + i.w;
                pq.push({ w + i.w, i.v });
            }
        }
    }
}
void f(int gr, int l, int r, int nl, int nr) {
    int mid = (l + r) >> 1, idx = -1;
    ll& res = dp[gr][mid];
    res = INF;
    for (int i = nl; i <= min(mid, nr); i++) {
        ll val = dp[gr - 1][i] + (mid - i - 1) * (psum[mid] - psum[i]);
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
    input();
    dijkstra();
    for (int i = 1; i <= b; i++) {
        w[i] = dist[i] + rdist[i];
    }
    sort(w + 1, w + 1 + b);
    for (int i = 1; i <= b; i++) {
        psum[i] = w[i] + psum[i - 1];
    }
    for (int i = 1; i <= b; i++) {
        dp[1][i] = (i - 1) * psum[i];
    }
    for (int i = 2; i <= s; i++) {
        f(i, i, b, 0, b);
    }
    cout << dp[s][b];
    return 0;
}