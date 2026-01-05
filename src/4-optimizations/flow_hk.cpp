#include "../0-common/common.hpp"

// what: maximum bipartite matching (Hopcroft-Karp).
// time: O(E sqrt V); memory: O(E)
// constraint: 0-based; left [0..n_l-1], right [0..n_r-1]
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
        fill(all(dist), -1);
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
        fill(all(match_l), -1);
        fill(all(match_r), -1);
        int match = 0;
        while (bfs()) {
            for (int i = 0; i < n_l; i++) {
                if (match_l[i] == -1 && dfs(i)) match++;
            }
        }
        return match;
    }
};
