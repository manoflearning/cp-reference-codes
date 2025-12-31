#include "../../src/2-graph/shortest_path.cpp"

// what: tests for shortest paths.
// time: random + brute; memory: O(n^2)
// constraint: small n brute.
// usage: g++ -std=c++17 test_shortest_path.cpp && ./a.out

mt19937_64 rng(3);
int rnd(int l, int r) {
    uniform_int_distribution<int> dis(l, r);
    return dis(rng);
}

vector<vector<ll>> floy(int n, const vector<tuple<int, int, ll>> &ed) {
    const ll INF = (1LL << 60);
    vector<vector<ll>> d(n + 1, vector<ll>(n + 1, INF));
    for (int i = 1; i <= n; i++) d[i][i] = 0;
    for (auto [u, v, w] : ed) d[u][v] = min(d[u][v], w);
    for (int k = 1; k <= n; k++)
        for (int i = 1; i <= n; i++)
            if (d[i][k] < INF)
                for (int j = 1; j <= n; j++)
                    if (d[k][j] < INF)
                        d[i][j] = min(d[i][j], d[i][k] + d[k][j]);
    return d;
}

void t_dijk() {
    const ll INF = (1LL << 60);
    for (int it = 0; it < 200; it++) {
        int n = rnd(2, 7);
        int m = rnd(0, n * (n - 1));
        vector<tuple<int, int, ll>> ed;
        dijk dj;
        dj.init(n);
        for (int i = 0; i < m; i++) {
            int u = rnd(1, n), v = rnd(1, n);
            ll w = rnd(0, 9);
            ed.push_back({u, v, w});
            dj.add(u, v, w);
        }
        auto d = floy(n, ed);
        int s = rnd(1, n);
        auto dist = dj.run(s);
        for (int v = 1; v <= n; v++) {
            ll a = dist[v];
            ll b = d[s][v];
            if (b >= INF / 2) assert(a >= INF / 2);
            else assert(a == b);
        }
    }
}

void t_bell() {
    const ll INF = (1LL << 60);
    for (int it = 0; it < 200; it++) {
        int n = rnd(2, 6);
        int m = rnd(0, n * (n - 1));
        vector<tuple<int, int, ll>> ed;
        bell bl;
        bl.init(n);
        for (int i = 0; i < m; i++) {
            int u = rnd(1, n), v = rnd(1, n);
            ll w = rnd(-5, 9);
            ed.push_back({u, v, w});
            bl.add(u, v, w);
        }
        auto d = floy(n, ed);
        int s = rnd(1, n);
        bool neg = 0;
        for (int v = 1; v <= n; v++)
            if (d[s][v] < INF / 2 && d[v][v] < 0) neg = 1;
        vector<ll> dist;
        bool ok = bl.run(s, dist);
        if (neg) {
            assert(!ok);
            continue;
        }
        assert(ok);
        for (int v = 1; v <= n; v++) {
            ll a = dist[v];
            ll b = d[s][v];
            if (b >= INF / 2) assert(a >= INF / 2);
            else assert(a == b);
        }
    }
}

void t_floy() {
    const ll INF = (1LL << 60);
    for (int it = 0; it < 200; it++) {
        int n = rnd(2, 7);
        int m = rnd(0, n * (n - 1));
        vector<tuple<int, int, ll>> ed;
        floyd fl;
        fl.init(n);
        for (int i = 0; i < m; i++) {
            int u = rnd(1, n), v = rnd(1, n);
            ll w = rnd(-5, 9);
            ed.push_back({u, v, w});
            fl.add(u, v, w);
        }
        auto d = floy(n, ed);
        bool neg = 0;
        for (int v = 1; v <= n; v++)
            if (d[v][v] < 0) neg = 1;
        if (neg) continue;
        fl.run();
        for (int i = 1; i <= n; i++)
            for (int j = 1; j <= n; j++)
                if (d[i][j] >= INF / 2) assert(fl.d[i][j] >= INF / 2);
                else assert(fl.d[i][j] == d[i][j]);
    }
}

int main() {
    t_dijk();
    t_bell();
    t_floy();
    return 0;
}
