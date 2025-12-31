#include "../common/common.hpp"

// what: Euler circuit via Hierholzer (undirected multigraph, matrix).
// time: O(n^2+m); memory: O(n^2)
// constraint: 1-indexed; dense/multi-edge; loops supported via add().
// usage: ecir g; g.init(n); g.add(u,v); if (g.can()) auto path=g.run(1);
struct ecir {
    int n;
    vector<vector<int>> adj;
    vector<int> nxt, path;

    void init(int n_) {
        n = n_;
        adj.assign(n + 1, vector<int>(n + 1));
        nxt.assign(n + 1, 1);
        path.clear();
    }
    void add(int u, int v, int c = 1) {
        if (u == v) adj[u][u] += 2 * c; // goal: keep degree correct for loops.
        else adj[u][v] += c, adj[v][u] += c;
    }
    bool can() {
        for (int i = 1; i <= n; i++) {
            int deg = 0;
            for (int j = 1; j <= n; j++) deg += adj[i][j];
            if (deg & 1) return 0;
        }
        return 1;
    }
    void dfs(int v) {
        for (int &i = nxt[v]; i <= n; i++) {
            while (i <= n && adj[v][i]) {
                adj[v][i]--;
                adj[i][v]--;
                dfs(i);
            }
        }
        path.push_back(v);
    }
    vector<int> run(int s = 1) {
        for (int i = 1; i <= n; i++) nxt[i] = 1;
        path.clear();
        dfs(s);
        reverse(all(path));
        return path;
    }
};
