#include "../0-common/common.hpp"

// what: build an Eulerian circuit in an undirected multigraph (adjacency matrix).
// time: O(n^2+m); memory: O(n^2)
// constraint: 1-indexed; all nonzero-degree nodes connected.
// usage: euler_cir g; g.init(n); g.add(u,v); if (g.can()) auto path=g.run(1);
struct euler_cir {
    int n;
    vector<vector<int>> adj;
    vector<int> nxt, path;

    void init(int n_) {
        // goal: allocate adjacency matrix and reset state.
        n = n_;
        adj.assign(n + 1, vector<int>(n + 1));
        nxt.assign(n + 1, 1);
        path.clear();
    }
    void add(int u, int v, int c = 1) {
        // goal: add c parallel edges between u and v.
        if (u == v) adj[u][u] += 2 * c;
        else adj[u][v] += c, adj[v][u] += c;
    }
    bool can() {
        // result: whether an Euler circuit exists.
        vector<int> deg(n + 1);
        for (int i = 1; i <= n; i++)
            for (int j = 1; j <= n; j++) deg[i] += adj[i][j];
        for (int i = 1; i <= n; i++)
            if (deg[i] & 1) return 0;
        int s = 0;
        for (int i = 1; i <= n; i++)
            if (deg[i]) {
                s = i;
                break;
            }
        if (!s) return 1;
        vector<int> vis(n + 1);
        queue<int> q;
        q.push(s);
        vis[s] = 1;
        while (!q.empty()) {
            int v = q.front();
            q.pop();
            for (int i = 1; i <= n; i++)
                if (adj[v][i] && !vis[i]) vis[i] = 1, q.push(i);
        }
        for (int i = 1; i <= n; i++)
            if (deg[i] && !vis[i]) return 0;
        return 1;
    }
    void dfs(int v) {
        // goal: Hierholzer DFS to build circuit.
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
        // result: Euler circuit starting from s (if exists).
        for (int i = 1; i <= n; i++) nxt[i] = 1;
        path.clear();
        dfs(s);
        reverse(all(path));
        return path;
    }
};
