#include "../0-common/common.hpp"

// what: compute single-source shortest paths with non-negative edges (Dijkstra).
// time: O((n+m)log n); memory: O(n+m)
// constraint: directed; 1-indexed; w >= 0.
// usage: dijkstra g; g.init(n); g.add_edge(u,v,w); auto dist=g.run(s);
struct dijkstra {
    static const ll INF = (1LL << 62);
    int n;
    vector<vector<pll>> adj;

    void init(int n_) {
        // goal: initialize empty graph.
        n = n_;
        adj.assign(n + 1, {});
    }
    void add_edge(int u, int v, ll w) { adj[u].push_back({w, v}); }
    vector<ll> run(int s) {
        // result: dist[i] = shortest distance from s to i.
        vector<ll> dist(n + 1, INF);
        priority_queue<pll, vector<pll>, greater<pll>> pq;
        dist[s] = 0;
        pq.push({0, s});
        while (!pq.empty()) {
            auto [d, v] = pq.top();
            pq.pop();
            if (d != dist[v]) continue;
            for (auto [w, to] : adj[v]) {
                if (dist[to] > d + w) {
                    dist[to] = d + w;
                    pq.push({dist[to], to});
                }
            }
        }
        return dist;
    }
};

// what: compute single-source shortest paths with possible negative edges.
// time: O(nm); memory: O(n+m)
// constraint: directed; 1-indexed; detects negative cycle reachable from s.
// usage: bell_ford g; g.init(n); g.add_edge(u,v,w); bool ok=g.run(s, dist);
struct bell_ford {
    static const ll INF = (1LL << 62);
    int n;
    vector<tuple<int, int, ll>> ed;

    void init(int n_) {
        // goal: reset edge list.
        n = n_;
        ed.clear();
    }
    void add_edge(int u, int v, ll w) { ed.push_back({u, v, w}); }
    bool run(int s, vector<ll> &dist) {
        // result: false if a negative cycle is reachable.
        dist.assign(n + 1, INF);
        dist[s] = 0;
        bool upd = 0;
        for (int i = 1; i <= n; i++) {
            upd = 0;
            for (auto [u, v, w] : ed) {
                if (dist[u] == INF) continue;
                if (dist[v] > dist[u] + w) {
                    dist[v] = dist[u] + w;
                    upd = 1;
                }
            }
            if (!upd) break;
        }
        return !upd;
    }
};

// what: compute all-pairs shortest paths with dynamic programming.
// time: O(n^3); memory: O(n^2)
// constraint: directed; 1-indexed; watch overflow on INF.
// usage: floyd g; g.init(n); g.add_edge(u,v,w); g.run(); auto &d=g.d;
struct floyd {
    static const ll INF = (1LL << 62);
    int n;
    vector<vector<ll>> d;

    void init(int n_) {
        // goal: initialize distance matrix.
        n = n_;
        d.assign(n + 1, vector<ll>(n + 1, INF));
        for (int i = 1; i <= n; i++) d[i][i] = 0;
    }
    void add_edge(int u, int v, ll w) { d[u][v] = min(d[u][v], w); }
    void run() {
        // goal: relax all pairs via intermediate nodes.
        for (int k = 1; k <= n; k++) {
            for (int i = 1; i <= n; i++) {
                if (d[i][k] == INF) continue;
                for (int j = 1; j <= n; j++) {
                    if (d[k][j] == INF) continue;
                    d[i][j] = min(d[i][j], d[i][k] + d[k][j]);
                }
            }
        }
    }
};
