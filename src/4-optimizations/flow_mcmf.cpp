#include "../0-common/common.hpp"

// what: compute min-cost max-flow using potentials and Dijkstra.
// time: O(F E log V); memory: O(E)
// constraint: 1-indexed [1..n]; cap >= 0; no negative cycle reachable from s.
// usage: mcmf mf(n); mf.add_edge(u, v, cap, cost); pll r = mf.min_cost_mf(s, t);
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
        g.assign(n + 1, {});
    }
    edge_ref add_edge(int u, int v, ll cap, ll cost) {
        // goal: add forward + reverse edge with costs
        edge a{v, sz(g[v]), cap, cost};
        edge b{u, sz(g[u]), 0, -cost};
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

    pll min_cost_mf(int s, int t, ll max_f = INF, bool init_pot = true) {
        ll flow = 0, cost = 0;
        vector<ll> pot(n + 1, 0), dist(n + 1);
        vector<int> pv(n + 1), pe(n + 1);

        if (init_pot) {
            // goal: initial potentials for negative costs
            vector<ll> d(n + 1, INF);
            vector<char> in_q(n + 1, 0);
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
            for (int i = 1; i <= n; i++)
                if (d[i] < INF) pot[i] = d[i];
        }
        while (flow < max_f) {
            // goal: shortest path in reduced costs
            fill(all(dist), INF);
            dist[s] = 0;
            priority_queue<pair<ll, int>, vector<pair<ll, int>>, greater<pair<ll, int>>> pq;
            pq.push({0, s});
            while (!pq.empty()) {
                auto [d, v] = pq.top();
                pq.pop();
                if (d != dist[v]) continue;
                for (int i = 0; i < sz(g[v]); i++) {
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
            for (int i = 1; i <= n; i++)
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

// what: find min-cost flow with lower/upper bounds via transformation.
// time: dominated by mcmf; memory: O(E)
// constraint: 1-indexed [1..n]; 0 <= lo <= hi; no negative cycle; single-use (call init(n) to reuse).
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
        demand.assign(n + 1, 0);
        edges.clear();
        base_cost = 0;
    }
    int add_edge(int u, int v, ll lo, ll hi, ll cost) {
        // goal: store lower bounds via node demands
        demand[u] -= lo;
        demand[v] += lo;
        base_cost += lo * cost;
        edges.push_back({mf.add_edge(u, v, hi - lo, cost), lo});
        return sz(edges) - 1;
    }
    ll edge_flow(int id) const {
        // goal: actual flow with lower bound restored
        return edges[id].lo + mf.edge_flow(edges[id].ref);
    }
    ll add_demands(vector<mcmf::edge_ref> &aux) {
        // goal: connect ss/tt for feasible circulation
        ll total = 0;
        int ss = n + 1, tt = n + 2;
        for (int i = 1; i <= n; i++) {
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
        int ss = n + 1, tt = n + 2;
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
        int ss = n + 1, tt = n + 2;
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
