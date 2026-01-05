#include "../../src/2-graph/cc_scc.cpp"

// what: tests for scc (kosaraju/tarjan).
// time: random + brute; memory: O(n^2)
// constraint: small n brute.
// usage: g++ -std=c++17 test_cc_scc.cpp && ./a.out

mt19937_64 rng(4);
int rnd(int l, int r) {
    uniform_int_distribution<int> dis(l, r);
    return dis(rng);
}

vector<vector<int>> rch(int n, const vector<vector<int>> &g) {
    vector<vector<int>> r(n + 1, vector<int>(n + 1));
    for (int s = 1; s <= n; s++) {
        queue<int> q;
        q.push(s);
        r[s][s] = 1;
        while (!q.empty()) {
            int v = q.front();
            q.pop();
            for (int to : g[v]) {
                if (!r[s][to]) r[s][to] = 1, q.push(to);
            }
        }
    }
    return r;
}

vector<int> cmp_na(int n, const vector<vector<int>> &g) {
    auto r = rch(n, g);
    vector<int> cmp(n + 1, -1);
    int cid = 0;
    for (int i = 1; i <= n; i++) {
        if (cmp[i] != -1) continue;
        for (int j = 1; j <= n; j++)
            if (r[i][j] && r[j][i]) cmp[j] = cid;
        cid++;
    }
    return cmp;
}

void t_scc() {
    for (int it = 0; it < 200; it++) {
        int n = rnd(1, 7);
        int m = rnd(0, n * (n - 1));
        vector<vector<int>> g(n + 1);
        for (int i = 0; i < m; i++) {
            int u = rnd(1, n), v = rnd(1, n);
            g[u].push_back(v);
        }
        auto cmp = cmp_na(n, g);

        scc_kosa s1;
        s1.init(n);
        for (int u = 1; u <= n; u++)
            for (int v : g[u]) s1.add(u, v);
        s1.run();

        scc_tarjan s2;
        s2.init(n);
        for (int u = 1; u <= n; u++)
            for (int v : g[u]) s2.add(u, v);
        s2.run();

        for (int i = 1; i <= n; i++)
            for (int j = 1; j <= n; j++) {
                bool a = (cmp[i] == cmp[j]);
                bool b = (s1.comp[i] == s1.comp[j]);
                bool c = (s2.comp[i] == s2.comp[j]);
                assert(a == b);
                assert(a == c);
            }
    }
}

int main() {
    t_scc();
    return 0;
}
