#include "../../src/4-optimizations/flow_mcmf.cpp"

// what: tests for mcmf and lr_mcmf.
// time: random + brute; memory: O(1)
// constraint: small n, small caps.
// usage: g++ -std=c++17 test_flow_mcmf.cpp && ./a.out

mt19937_64 rng(401);
int rnd(int l, int r) {
    uniform_int_distribution<int> dis(l, r);
    return dis(rng);
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
            mf1.add_edge(u + 1, v + 1, cap, cost);
            mf2.add_edge(u + 1, v + 1, cap, cost);
            na.add_edge(u, v, cap, cost);
        }
        ll max_f = rnd(0, 8);
        auto exp = na.min_cost_mf(s, t, max_f);
        assert(mf1.min_cost_mf(s + 1, t + 1, max_f, true) == exp);
        if (nonneg) assert(mf2.min_cost_mf(s + 1, t + 1, max_f, false) == exp);
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
            f.add_edge(u + 1, v + 1, lo, hi, c);
        }
        auto exp = brute_lr(n, s, t, es);
        auto got = f.max_flow(s + 1, t + 1, true);
        assert(got.fr == exp.ok);
        if (exp.ok) assert(got.sc.fr == exp.flow), assert(got.sc.sc == exp.cost);
    }
}

int main() {
    t_mcmf();
    t_lr_mcmf();
    return 0;
}
