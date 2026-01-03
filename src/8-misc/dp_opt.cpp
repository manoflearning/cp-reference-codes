#include "../common/common.hpp"

// what: collection of DP optimizations (CHT, Knuth, DnC, slope trick).
// time: see each component; memory: see each component.
// constraint: see each component.
// usage: include and use each struct/function below.

// Monotone Convex Hull Trick (min query).
// what: maintain lower hull for monotone slopes and query min at any x.
// time: add O(1) amortized, query O(log n); memory: O(n)
// constraint: slopes added in decreasing order for min; uses long double intersections.
// usage: cht_mono ch; ch.add_line(m, b); ll v = ch.get(x);
struct cht_mono {
    struct line {
        ll m, b;
        ld x;
    };
    vector<line> st;
    static constexpr ld NEG_INF = -1e30L;

    ld isect(const line &a, const line &b) const {
        return (ld)(b.b - a.b) / (a.m - b.m);
    }
    void add_line(ll m, ll b) {
        // goal: maintain lower hull with decreasing slopes
        if (!st.empty() && st.back().m == m) {
            if (st.back().b <= b) return; // new line is worse
            st.pop_back();
        }
        line cur{m, b, NEG_INF};
        while (!st.empty()) {
            cur.x = isect(st.back(), cur);
            if (cur.x > st.back().x) break;
            st.pop_back();
        }
        if (st.empty()) cur.x = NEG_INF;
        st.pb(cur);
    }
    ll get(ll x) const {
        // invariant: st is sorted by x; pick last with x_i <= x
        int l = 0, r = sz(st) - 1;
        ld xd = (ld)x;
        while (l < r) {
            int mid = (l + r + 1) >> 1;
            if (st[mid].x <= xd) l = mid;
            else r = mid - 1;
        }
        return st[l].m * x + st[l].b;
    }
};

// Knuth Optimization.
// what: optimize interval DP with quadrangle inequality (Knuth).
// time: O(n^2); memory: O(n^2)
// constraint: cost must satisfy quadrangle inequality (Monge) + monotone opt.
// usage: knuth_opt ko; ko.build(n, [&](int i,int j){ return cost(i,j); });
struct knuth_opt {
    static constexpr ll INF = (1LL << 62);
    int n;
    vvl dp;
    vvi opt;

    template <class F>
    void build(int n_, F cost) {
        // goal: fill dp/opt for 0..n-1
        n = n_;
        dp.assign(n, vl(n, 0));
        opt.assign(n, vi(n, 0));
        for (int i = 0; i < n; i++) opt[i][i] = i;
        for (int len = 2; len <= n; len++) {
            for (int i = 0; i + len - 1 < n; i++) {
                int j = i + len - 1;
                ll best = INF;
                int best_k = -1;
                int l = opt[i][j - 1];
                int r = opt[i + 1][j];
                l = max(l, i);
                r = min(r, j - 1);
                for (int k = l; k <= r; k++) {
                    ll val = dp[i][k] + dp[k + 1][j] + cost(i, j);
                    if (val < best) best = val, best_k = k;
                }
                dp[i][j] = best;
                opt[i][j] = best_k;
            }
        }
    }
};

// Divide and Conquer Optimization.
// what: optimize layered DP with monotone opt (divide and conquer).
// time: O(k n log n); memory: O(n)
// constraint: opt[g][i] <= opt[g][i+1] (Monge cost).
// usage: dnc_opt dc; dc.run(k, n, base, cost); auto ans = dc.dp();
struct dnc_opt {
    static constexpr ll INF = (1LL << 62);
    vl prv, cur;

    template <class F>
    void run(int k, int n, const vl &base, F cost) {
        // goal: compute dp for k layers, starting from base
        prv = base;
        cur.assign(n, INF);
        for (int g = 1; g <= k; g++) {
            fill(all(cur), INF);
            solve(0, n - 1, 0, n - 1, cost);
            prv.swap(cur);
        }
    }
    const vl &dp() const { return prv; }

    template <class F>
    void solve(int l, int r, int opt_l, int opt_r, F cost) {
        int mid = (l + r) >> 1;
        ll best = INF;
        int best_k = -1;
        int end = min(mid, opt_r);
        for (int j = opt_l; j <= end; j++) {
            ll val = prv[j] + cost(j, mid);
            if (val < best) best = val, best_k = j;
        }
        cur[mid] = best;
        if (l == r) return;
        solve(l, mid, opt_l, best_k, cost);
        solve(mid + 1, r, best_k, opt_r, cost);
    }
};

// Slope Trick for making array strictly increasing.
// what: adjust array to strictly increasing with minimum L1 cost (slope trick).
// time: O(n log n); memory: O(n)
// constraint: values fit in ll.
// usage: ll ops = slope_trick(a);
ll slope_trick(vl a) {
    ll ret = 0;
    priority_queue<ll> pq;
    for (int i = 0; i < sz(a); i++) {
        a[i] -= i; // goal: convert to nondecreasing
        pq.push(a[i]);
        if (pq.top() > a[i]) {
            ret += pq.top() - a[i];
            pq.pop();
            pq.push(a[i]);
        }
    }
    return ret;
}
