#include "../../src/4-optimizations/flow.cpp"

// what: tests for flow templates (dinic/mcmf/matching/lower bounds).
// time: random + brute; memory: O(1)
// constraint: small n, small caps.
// usage: g++ -std=c++17 test_flow.cpp && ./a.out

mt19937_64 rng(401);
int rnd(int l, int r) {
    uniform_int_distribution<int> dis(l, r);
    return dis(rng);
}

struct ek_flow {
    struct edge {
        int to, rev;
        ll cap;
    };
    int n;
    vector<vector<edge>> g;
    void init(int n_) {
        n = n_;
        g.assign(n, {});
    }
    void add_edge(int u, int v, ll cap) {
        edge a{v, sz(g[v]), cap};
        edge b{u, sz(g[u]), 0};
        g[u].push_back(a);
        g[v].push_back(b);
    }
    ll max_flow(int s, int t) {
        if (s == t) return 0;
        ll flow = 0;
        while (1) {
            vector<int> pv(n, -1), pe(n, -1);
            queue<int> q;
            q.push(s);
            pv[s] = s;
            while (!q.empty() && pv[t] == -1) {
                int v = q.front();
                q.pop();
                for (int i = 0; i < sz(g[v]); i++) {
                    auto &e = g[v][i];
                    if (!e.cap || pv[e.to] != -1) continue;
                    pv[e.to] = v;
                    pe[e.to] = i;
                    q.push(e.to);
                    if (e.to == t) break;
                }
            }
            if (pv[t] == -1) break;
            ll add = (1LL << 62);
            for (int v = t; v != s; v = pv[v]) add = min(add, g[pv[v]][pe[v]].cap);
            for (int v = t; v != s; v = pv[v]) {
                auto &e = g[pv[v]][pe[v]];
                e.cap -= add;
                g[v][e.rev].cap += add;
            }
            flow += add;
        }
        return flow;
    }
};

int brute_match(int n_l, int n_r, const vector<vector<int>> &g) {
    vector<vector<int>> dp(n_l + 1, vector<int>(1 << n_r, -1));
    function<int(int, int)> go = [&](int i, int mask) {
        if (i == n_l) return 0;
        int &ret = dp[i][mask];
        if (ret != -1) return ret;
        ret = go(i + 1, mask);
        for (int r : g[i])
            if (!(mask & (1 << r))) ret = max(ret, 1 + go(i + 1, mask | (1 << r)));
        return ret;
    };
    return go(0, 0);
}

struct mcmf_spfa {
    struct edge {
        int to, rev;
        ll cap, cost;
    };
    int n;
    vector<vector<edge>> g;
    void init(int n_) {
        n = n_;
        g.assign(n, {});
    }
    void add_edge(int u, int v, ll cap, ll cost) {
        edge a{v, sz(g[v]), cap, cost};
        edge b{u, sz(g[u]), 0, -cost};
        g[u].push_back(a);
        g[v].push_back(b);
    }
    pll min_cost_mf(int s, int t, ll max_f) {
        const ll INF = (1LL << 62);
        ll flow = 0, cost = 0;
        while (flow < max_f) {
            vector<ll> dist(n, INF);
            vector<int> pv(n, -1), pe(n, -1);
            queue<int> q;
            vector<char> in_q(n, 0);
            dist[s] = 0;
            q.push(s);
            in_q[s] = 1;
            while (!q.empty()) {
                int v = q.front();
                q.pop();
                in_q[v] = 0;
                for (int i = 0; i < sz(g[v]); i++) {
                    auto &e = g[v][i];
                    if (!e.cap) continue;
                    ll nd = dist[v] + e.cost;
                    if (nd < dist[e.to]) {
                        dist[e.to] = nd;
                        pv[e.to] = v;
                        pe[e.to] = i;
                        if (!in_q[e.to]) {
                            in_q[e.to] = 1;
                            q.push(e.to);
                        }
                    }
                }
            }
            if (dist[t] == INF) break;
            ll add = max_f - flow;
            for (int v = t; v != s; v = pv[v]) add = min(add, g[pv[v]][pe[v]].cap);
            for (int v = t; v != s; v = pv[v]) {
                auto &e = g[pv[v]][pe[v]];
                e.cap -= add;
                g[v][e.rev].cap += add;
                cost += add * e.cost;
            }
            flow += add;
        }
        return {flow, cost};
    }
};

struct lr_res {
    bool ok;
    ll flow, cost;
};

lr_res brute_lr(int n, int s, int t, const vector<tuple<int, int, int, int, int>> &es) {
    int m = sz(es);
    vector<int> f(m, 0);
    ll best_f = -(1LL << 62), best_c = (1LL << 62);
    function<void(int)> dfs = [&](int i) {
        if (i == m) {
            vector<int> bal(n, 0);
            ll cost = 0;
            for (int k = 0; k < m; k++) {
                auto [u, v, lo, hi, c] = es[k];
                bal[u] += f[k];
                bal[v] -= f[k];
                cost += 1LL * f[k] * c;
            }
            for (int v = 0; v < n; v++)
                if (v != s && v != t && bal[v]) return;
            if (bal[t] != -bal[s]) return;
            ll flow = bal[s];
            if (flow < 0) return;
            if (flow > best_f) best_f = flow, best_c = cost;
            else if (flow == best_f) best_c = min(best_c, cost);
            return;
        }
        auto [u, v, lo, hi, c] = es[i];
        for (int x = lo; x <= hi; x++) {
            f[i] = x;
            dfs(i + 1);
        }
    };
    dfs(0);
    if (best_f == -(1LL << 62)) return {false, 0, 0};
    return {true, best_f, best_c};
}

void t_dinic() {
    {
        dinic mf(2);
        mf.add_edge(0, 1, 3);
        assert(mf.max_flow(0, 1) == 3);
    }
    for (int it = 0; it < 200; it++) {
        int n = rnd(2, 10);
        int m = rnd(1, min(25, n * (n - 1)));
        int s = rnd(0, n - 1), t = rnd(0, n - 1);
        dinic mf(n);
        ek_flow na;
        na.init(n);
        for (int i = 0; i < m; i++) {
            int u = rnd(0, n - 1), v = rnd(0, n - 1);
            if (u == v) continue;
            ll cap = rnd(0, 7);
            mf.add_edge(u, v, cap);
            na.add_edge(u, v, cap);
        }
        ll exp = na.max_flow(s, t);
        ll lim = rnd(0, 10);
        assert(mf.max_flow(s, t, lim) == min(exp, lim));
    }
}

void t_hk() {
    for (int it = 0; it < 300; it++) {
        int n_l = rnd(0, 10), n_r = rnd(0, 10);
        hk bm(n_l, n_r);
        vector<vector<int>> g(n_l);
        for (int l = 0; l < n_l; l++)
            for (int r = 0; r < n_r; r++)
                if (rnd(0, 1)) bm.add_edge(l, r), g[l].push_back(r);
        assert(bm.max_matching() == brute_match(n_l, n_r, g));
    }
}

void t_mcmf() {
    for (int it = 0; it < 200; it++) {
        int n = rnd(2, 8);
        int s = 0, t = n - 1;
        int m = rnd(1, min(18, n * (n - 1) / 2));
        vector<tuple<int, int, ll, ll>> es;
        es.reserve(m);
        bool nonneg = true;
        for (int i = 0; i < m; i++) {
            int u = rnd(0, n - 2);
            int v = rnd(u + 1, n - 1);
            ll cap = rnd(0, 3);
            ll cost = rnd(-5, 5);
            nonneg &= (cost >= 0);
            es.push_back({u, v, cap, cost});
        }
        mcmf mf1(n), mf2(n);
        mcmf_spfa na;
        na.init(n);
        for (auto [u, v, cap, cost] : es) {
            mf1.add_edge(u, v, cap, cost);
            mf2.add_edge(u, v, cap, cost);
            na.add_edge(u, v, cap, cost);
        }
        ll max_f = rnd(0, 8);
        auto exp = na.min_cost_mf(s, t, max_f);
        assert(mf1.min_cost_mf(s, t, max_f, true) == exp);
        if (nonneg) assert(mf2.min_cost_mf(s, t, max_f, false) == exp);
    }
}

void t_lr_dinic() {
    for (int it = 0; it < 200; it++) {
        int n = rnd(2, 6);
        int s = rnd(0, n - 1), t = rnd(0, n - 1);
        while (t == s) t = rnd(0, n - 1);
        int m = rnd(1, 8);
        vector<tuple<int, int, int, int, int>> es;
        es.reserve(m);
        lr_dinic f(n);
        for (int i = 0; i < m; i++) {
            int u = rnd(0, n - 1), v = rnd(0, n - 1);
            if (u == v) continue;
            int lo = rnd(0, 2);
            int hi = lo + rnd(0, 2);
            es.push_back({u, v, lo, hi, 0});
            f.add_edge(u, v, lo, hi);
        }
        auto exp = brute_lr(n, s, t, es);
        auto got = f.max_flow(s, t);
        assert(got.fr == exp.ok);
        if (exp.ok) assert(got.sc == exp.flow);
    }
}

void t_lr_mcmf() {
    for (int it = 0; it < 150; it++) {
        int n = rnd(2, 6);
        int s = rnd(0, n - 1), t = rnd(0, n - 1);
        while (t == s) t = rnd(0, n - 1);
        int m = rnd(1, 8);
        vector<tuple<int, int, int, int, int>> es;
        es.reserve(m);
        lr_mcmf f(n);
        for (int i = 0; i < m; i++) {
            int u = rnd(0, n - 1), v = rnd(0, n - 1);
            if (u == v) continue;
            int lo = rnd(0, 2);
            int hi = lo + rnd(0, 2);
            int c = rnd(0, 5);
            es.push_back({u, v, lo, hi, c});
            f.add_edge(u, v, lo, hi, c);
        }
        auto exp = brute_lr(n, s, t, es);
        auto got = f.max_flow(s, t, true);
        assert(got.fr == exp.ok);
        if (exp.ok) assert(got.sc.fr == exp.flow), assert(got.sc.sc == exp.cost);
    }
}

int main() {
    t_dinic();
    t_hk();
    t_mcmf();
    t_lr_dinic();
    t_lr_mcmf();
    return 0;
}
