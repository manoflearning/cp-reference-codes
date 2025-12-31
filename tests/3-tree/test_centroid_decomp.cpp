#include "../../src/3-tree/centroid_decomp.cpp"

// what: tests for cen_decomp.
// time: random + checks; memory: O(n)
// constraint: small n.
// usage: g++ -std=c++17 test_centroid_decomp.cpp && ./a.out

mt19937_64 rng(10);
int rnd(int l, int r) {
    uniform_int_distribution<int> dis(l, r);
    return dis(rng);
}

void t_rnd() {
    for (int it = 0; it < 200; it++) {
        int n = rnd(2, 50);
        vector<int> par(n + 1, 0);
        cen_decomp cd;
        cd.init(n);
        for (int v = 2; v <= n; v++) {
            par[v] = rnd(1, v - 1);
            cd.add(v, par[v]);
        }
        cd.build(1);
        int root = 0;
        for (int v = 1; v <= n; v++)
            if (!cd.par[v]) root = v;
        assert(root != 0);
        vector<int> vis(n + 1);
        int cnt = 0;
        queue<int> q;
        q.push(root);
        vis[root] = 1;
        while (!q.empty()) {
            int v = q.front();
            q.pop();
            cnt++;
            for (int to : cd.chd[v]) {
                assert(cd.par[to] == v);
                if (!vis[to]) vis[to] = 1, q.push(to);
            }
        }
        assert(cnt == n);
    }
}

int main() {
    t_rnd();
    return 0;
}
