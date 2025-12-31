#include "../common/common.hpp"

// what: collection of flow solvers (max flow, min-cost flow, matching, bounds).
// time: see each struct; memory: O(E)
// constraint: 0-based; cap >= 0; mcmf assumes no negative cycle reachable from s.
// usage: dinic mf(n); mf.add_edge(u,v,c); ll f=mf.max_flow(s,t);

// dinic max flow (0-based).
// what: compute maximum flow in a directed graph (Dinic).
// time: O(E V^2) worst; memory: O(E)
// constraint: cap >= 0
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
        edge a{v, (int)g[v].size(), cap};
        edge b{u, (int)g[u].size(), 0};
        g[u].push_back(a);
        g[v].push_back(b);
        return {u, (int)g[u].size() - 1};
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
        for (int &i = work[v]; i < (int)g[v].size(); i++) {
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

// hk bipartite matching (0-based).
// what: compute maximum bipartite matching (Hopcroft-Karp).
// time: O(E sqrt V); memory: O(E)
// constraint: left [0..n_l-1], right [0..n_r-1]
// usage: hk bm(n_l, n_r); bm.add_edge(l, r); int m = bm.max_matching();
struct hk {
    int n_l, n_r;
    vector<vector<int>> g;
    vector<int> dist, match_l, match_r;

    hk(int n_l_ = 0, int n_r_ = 0) { init(n_l_, n_r_); }

    void init(int n_l_, int n_r_) {
        n_l = n_l_;
        n_r = n_r_;
        g.assign(n_l, {});
        dist.assign(n_l, 0);
        match_l.assign(n_l, -1);
        match_r.assign(n_r, -1);
    }

    void add_edge(int l, int r) {
        // goal: add edge from left to right
        g[l].push_back(r);
    }

    bool bfs() {
        // goal: build layers for shortest augmenting paths
        queue<int> q;
        fill(dist.begin(), dist.end(), -1);
        for (int i = 0; i < n_l; i++) {
            if (match_l[i] == -1) {
                dist[i] = 0;
                q.push(i);
            }
        }
        bool found = false;
        while (!q.empty()) {
            int v = q.front();
            q.pop();
            for (int r : g[v]) {
                int u = match_r[r];
                if (u == -1) {
                    found = true;
                } else if (dist[u] == -1) {
                    dist[u] = dist[v] + 1;
                    q.push(u);
                }
            }
        }
        return found;
    }

    bool dfs(int v) {
        for (int r : g[v]) {
            int u = match_r[r];
            if (u == -1 || (dist[u] == dist[v] + 1 && dfs(u))) {
                match_l[v] = r;
                match_r[r] = v;
                return true;
            }
        }
        dist[v] = -1;
        return false;
    }

    int max_matching() {
        // goal: compute maximum matching size
        fill(match_l.begin(), match_l.end(), -1);
        fill(match_r.begin(), match_r.end(), -1);
        int match = 0;
        while (bfs()) {
            for (int i = 0; i < n_l; i++) {
                if (match_l[i] == -1 && dfs(i)) match++;
            }
        }
        return match;
    }
};

// mcmf min-cost max-flow (0-based).
// what: compute min-cost max-flow using potentials and Dijkstra.
// time: O(F E log V); memory: O(E)
// constraint: no negative cycle reachable from s
// usage: mcmf mf(n); mf.add_edge(u,v,c,co); pll r=mf.min_cost_mf(s,t);
// usage: init_pot = false if all costs >= 0 (faster)
struct mcmf {
    static constexpr ll INF = (1LL << 62);

    struct edge {
        int to, rev;
        ll cap, cost;
    };
    struct edge_ref {
        int u, idx;
    };

    int n;
    vector<vector<edge>> g;

    mcmf(int n = 0) { init(n); }

    void init(int n_) {
        n = n_;
        g.assign(n, {});
    }

    edge_ref add_edge(int u, int v, ll cap, ll cost) {
        // goal: add forward + reverse edge with costs
        edge a{v, (int)g[v].size(), cap, cost};
        edge b{u, (int)g[u].size(), 0, -cost};
        g[u].push_back(a);
        g[v].push_back(b);
        return {u, (int)g[u].size() - 1};
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

    pll min_cost_mf(int s, int t, ll max_f = INF, bool init_pot = true) {
        ll flow = 0, cost = 0;
        vector<ll> pot(n, 0), dist(n);
        vector<int> pv(n), pe(n);

        if (init_pot) {
            // goal: initial potentials for negative costs
            vector<ll> d(n, INF);
            vector<char> in_q(n, 0);
            queue<int> q;
            d[s] = 0;
            q.push(s);
            in_q[s] = 1;
            while (!q.empty()) {
                int v = q.front();
                q.pop();
                in_q[v] = 0;
                for (const auto &e : g[v]) {
                    if (e.cap == 0) continue;
                    if (d[v] + e.cost < d[e.to]) {
                        d[e.to] = d[v] + e.cost;
                        if (!in_q[e.to]) {
                            in_q[e.to] = 1;
                            q.push(e.to);
                        }
                    }
                }
            }
            for (int i = 0; i < n; i++)
                if (d[i] < INF) pot[i] = d[i];
        }

        while (flow < max_f) {
            // goal: shortest path in reduced costs
            fill(dist.begin(), dist.end(), INF);
            dist[s] = 0;
            priority_queue<pair<ll, int>, vector<pair<ll, int>>, greater<pair<ll, int>>> pq;
            pq.push({0, s});
            while (!pq.empty()) {
                auto [d, v] = pq.top();
                pq.pop();
                if (d != dist[v]) continue;
                for (int i = 0; i < (int)g[v].size(); i++) {
                    const auto &e = g[v][i];
                    if (e.cap == 0) continue;
                    ll nd = d + e.cost + pot[v] - pot[e.to];
                    if (nd < dist[e.to]) {
                        dist[e.to] = nd;
                        pv[e.to] = v;
                        pe[e.to] = i;
                        pq.push({nd, e.to});
                    }
                }
            }
            if (dist[t] == INF) break; // edge: no more augmenting paths
            for (int i = 0; i < n; i++)
                if (dist[i] < INF) pot[i] += dist[i];

            ll add = max_f - flow;
            for (int v = t; v != s; v = pv[v]) {
                const auto &e = g[pv[v]][pe[v]];
                add = min(add, e.cap);
            }
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

// lr_dinic (0-based).
// what: find feasible max flow with lower/upper bounds via transformation.
// time: dominated by dinic, memory: O(E)
// constraint: 0 <= lo <= hi, single-use (call init(n) to reuse)
// usage: lr_dinic f(n); int id = f.add_edge(u, v, lo, hi); auto [ok, v] = f.max_flow(s, t);
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
        return (int)edges.size() - 1;
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

// lr_mcmf (0-based).
// what: find min-cost flow with lower/upper bounds via transformation.
// time: dominated by mcmf, memory: O(E)
// constraint: 0 <= lo <= hi, no negative cycle, single-use (call init(n) to reuse)
// usage: lr_mcmf f(n); f.add_edge(u, v, lo, hi, cost); auto [ok, r] = f.max_flow(s, t);
struct lr_mcmf {
    static constexpr ll INF = mcmf::INF;

    struct edge_info {
        mcmf::edge_ref ref;
        ll lo;
    };

    int n;
    mcmf mf;
    vector<ll> demand;
    vector<edge_info> edges;
    ll base_cost;

    lr_mcmf(int n = 0) { init(n); }

    void init(int n_) {
        n = n_;
        mf.init(n + 2);
        demand.assign(n, 0);
        edges.clear();
        base_cost = 0;
    }

    int add_edge(int u, int v, ll lo, ll hi, ll cost) {
        // goal: store lower bounds via node demands
        demand[u] -= lo;
        demand[v] += lo;
        base_cost += lo * cost;
        edges.push_back({mf.add_edge(u, v, hi - lo, cost), lo});
        return (int)edges.size() - 1;
    }

    ll edge_flow(int id) const {
        // goal: actual flow with lower bound restored
        return edges[id].lo + mf.edge_flow(edges[id].ref);
    }

    ll add_demands(vector<mcmf::edge_ref> &aux) {
        // goal: connect ss/tt for feasible circulation
        ll total = 0;
        int ss = n, tt = n + 1;
        for (int i = 0; i < n; i++) {
            if (demand[i] > 0) {
                aux.push_back(mf.add_edge(ss, i, demand[i], 0));
                total += demand[i];
            } else if (demand[i] < 0) {
                aux.push_back(mf.add_edge(i, tt, -demand[i], 0));
            }
        }
        return total;
    }

    pair<bool, ll> feasible(bool init_pot = true) {
        vector<mcmf::edge_ref> aux;
        aux.reserve(n);
        ll total = add_demands(aux);
        int ss = n, tt = n + 1;
        pll res = mf.min_cost_mf(ss, tt, total, init_pot);
        for (auto ref : aux) mf.clear_edge(ref);
        if (res.fr != total) return {false, 0};
        return {true, res.sc + base_cost};
    }

    pair<bool, pll> max_flow(int s, int t, bool init_pot = true) {
        if (s == t) {
            auto r = feasible(init_pot);
            return {r.fr, {0, r.sc}};
        }
        vector<mcmf::edge_ref> aux;
        aux.reserve(n + 1);
        int ss = n, tt = n + 1;
        auto ts = mf.add_edge(t, s, INF, 0);
        ll total = add_demands(aux);
        pll res = mf.min_cost_mf(ss, tt, total, init_pot);
        if (res.fr != total) {
            mf.clear_edge(ts);
            for (auto ref : aux) mf.clear_edge(ref);
            return {false, {0, 0}};
        }
        ll base = mf.edge_flow(ts);
        ll cost = res.sc;
        mf.clear_edge(ts);
        for (auto ref : aux) mf.clear_edge(ref);
        pll extra = mf.min_cost_mf(s, t, INF, init_pot);
        return {true, {base + extra.fr, cost + extra.sc + base_cost}};
    }
};
