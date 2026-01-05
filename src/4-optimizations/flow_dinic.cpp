#include "../0-common/common.hpp"

// what: compute maximum flow in a directed graph (Dinic).
// time: O(E V^2) worst; memory: O(E)
// constraint: 0-based; cap >= 0.
// usage: dinic mf(n); mf.add_edge(u, v, cap); ll f = mf.max_flow(s, t);
struct dinic {
    static constexpr ll INF = (1LL << 62);

    struct edge {
        int to, rev;
        ll cap;
    };
    struct edge_ref {
        int u, idx;
    };

    int n;
    vector<vector<edge>> g;
    vector<int> level, work;

    dinic(int n = 0) { init(n); }
    void init(int n_) {
        n = n_;
        g.assign(n, {});
    }
    edge_ref add_edge(int u, int v, ll cap) {
        // goal: add forward + reverse edge
        edge a{v, sz(g[v]), cap};
        edge b{u, sz(g[u]), 0};
        g[u].push_back(a);
        g[v].push_back(b);
        return {u, sz(g[u]) - 1};
    }
    ll edge_flow(edge_ref e) const {
        // goal: current flow on original edge
        const edge &ed = g[e.u][e.idx];
        return g[ed.to][ed.rev].cap;
    }
    void clear_edge(edge_ref e) {
        // goal: remove edge from residual graph
        edge &ed = g[e.u][e.idx];
        edge &rev = g[ed.to][ed.rev];
        ed.cap = 0;
        rev.cap = 0;
    }

    bool bfs(int s, int t) {
        // goal: build level graph
        level.assign(n, -1);
        queue<int> q;
        level[s] = 0;
        q.push(s);
        while (!q.empty()) {
            int v = q.front();
            q.pop();
            for (const auto &e : g[v]) {
                if (e.cap == 0 || level[e.to] != -1) continue;
                level[e.to] = level[v] + 1;
                q.push(e.to);
            }
        }
        return level[t] != -1;
    }
    ll dfs(int v, int t, ll f) {
        if (v == t || f == 0) return f;
        for (int &i = work[v]; i < sz(g[v]); i++) {
            edge &e = g[v][i];
            if (e.cap == 0 || level[e.to] != level[v] + 1) continue;
            // invariant: level strictly increases along augmenting path
            ll pushed = dfs(e.to, t, min(f, e.cap));
            if (pushed == 0) continue;
            e.cap -= pushed;
            g[e.to][e.rev].cap += pushed;
            return pushed;
        }
        return 0;
    }
    ll max_flow(int s, int t, ll limit = INF) {
        if (s == t) return 0; // edge: no flow needed
        ll flow = 0;
        while (flow < limit && bfs(s, t)) {
            work.assign(n, 0);
            while (flow < limit) {
                ll pushed = dfs(s, t, limit - flow);
                if (pushed == 0) break;
                flow += pushed;
            }
        }
        return flow;
    }
};

// what: find feasible max flow with lower/upper bounds via transformation.
// time: dominated by dinic; memory: O(E)
// constraint: 0-based; 0 <= lo <= hi; single-use (call init(n) to reuse).
// usage: lr_dinic f(n); f.add_edge(u, v, lo, hi); auto [ok, fl] = f.max_flow(s, t);
struct lr_dinic {
    static constexpr ll INF = dinic::INF;

    struct edge_info {
        dinic::edge_ref ref;
        ll lo;
    };

    int n;
    dinic mf;
    vector<ll> demand;
    vector<edge_info> edges;

    lr_dinic(int n = 0) { init(n); }
    void init(int n_) {
        n = n_;
        mf.init(n + 2);
        demand.assign(n, 0);
        edges.clear();
    }
    int add_edge(int u, int v, ll lo, ll hi) {
        // goal: store lower bounds via node demands
        demand[u] -= lo;
        demand[v] += lo;
        edges.push_back({mf.add_edge(u, v, hi - lo), lo});
        return sz(edges) - 1;
    }
    ll edge_flow(int id) const {
        // goal: actual flow with lower bound restored
        return edges[id].lo + mf.edge_flow(edges[id].ref);
    }
    ll add_demands(vector<dinic::edge_ref> &aux) {
        // goal: connect ss/tt for feasible circulation
        ll total = 0;
        int ss = n, tt = n + 1;
        for (int i = 0; i < n; i++) {
            if (demand[i] > 0) {
                aux.push_back(mf.add_edge(ss, i, demand[i]));
                total += demand[i];
            } else if (demand[i] < 0) {
                aux.push_back(mf.add_edge(i, tt, -demand[i]));
            }
        }
        return total;
    }

    bool feasible() {
        vector<dinic::edge_ref> aux;
        aux.reserve(n);
        ll total = add_demands(aux);
        int ss = n, tt = n + 1;
        ll flow = mf.max_flow(ss, tt);
        for (auto ref : aux) mf.clear_edge(ref);
        return flow == total;
    }
    pair<bool, ll> max_flow(int s, int t) {
        if (s == t) return {feasible(), 0}; // edge: trivial s == t
        vector<dinic::edge_ref> aux;
        aux.reserve(n + 1);
        int ss = n, tt = n + 1;
        auto ts = mf.add_edge(t, s, INF);
        ll total = add_demands(aux);
        ll flow = mf.max_flow(ss, tt);
        if (flow != total) {
            mf.clear_edge(ts);
            for (auto ref : aux) mf.clear_edge(ref);
            return {false, 0};
        }
        ll base = mf.edge_flow(ts);
        mf.clear_edge(ts);
        for (auto ref : aux) mf.clear_edge(ref);
        ll extra = mf.max_flow(s, t);
        return {true, base + extra};
    }
};
