#include "../../src/4-optimizations/flow_dinic.cpp"

// what: tests for dinic and lr_dinic.
// time: random + brute; memory: O(1)
// constraint: small n, small caps.
// usage: g++ -std=c++17 test_flow_dinic.cpp && ./a.out

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
        mf.add_edge(1, 2, 3);
        assert(mf.max_flow(1, 2) == 3);
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
            mf.add_edge(u + 1, v + 1, cap);
            na.add_edge(u, v, cap);
        }
        ll exp = na.max_flow(s, t);
        ll lim = rnd(0, 10);
        assert(mf.max_flow(s + 1, t + 1, lim) == min(exp, lim));
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
            f.add_edge(u + 1, v + 1, lo, hi);
        }
        auto exp = brute_lr(n, s, t, es);
        auto got = f.max_flow(s + 1, t + 1);
        assert(got.fr == exp.ok);
        if (exp.ok) assert(got.sc == exp.flow);
    }
}

int main() {
    t_dinic();
    t_lr_dinic();
    return 0;
}
