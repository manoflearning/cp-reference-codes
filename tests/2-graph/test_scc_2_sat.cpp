#include "../../src/2-graph/scc_2_sat.cpp"

// what: tests for scc and 2-sat.
// time: random + brute; memory: O(n^2)
// constraint: small n brute.
// usage: g++ -std=c++17 test_scc_2_sat.cpp && ./a.out

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

bool sat_br(int n, const vector<pii> &cl, vector<int> &val) {
    int lim = 1 << n;
    for (int mask = 0; mask < lim; mask++) {
        bool ok = 1;
        for (auto [a, b] : cl) {
            bool va = (a > 0) ? ((mask >> (a - 1)) & 1) : !((mask >> (-a - 1)) & 1);
            bool vb = (b > 0) ? ((mask >> (b - 1)) & 1) : !((mask >> (-b - 1)) & 1);
            if (!(va || vb)) {
                ok = 0;
                break;
            }
        }
        if (!ok) continue;
        val.assign(n + 1, 0);
        for (int i = 1; i <= n; i++) val[i] = (mask >> (i - 1)) & 1;
        return 1;
    }
    return 0;
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

        scc_ko s1;
        s1.init(n);
        for (int u = 1; u <= n; u++)
            for (int v : g[u]) s1.add(u, v);
        s1.run();

        scc_ta s2;
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

void t_sat() {
    for (int it = 0; it < 200; it++) {
        int n = rnd(1, 8);
        int m = rnd(0, 12);
        vector<pii> cl;
        for (int i = 0; i < m; i++) {
            int a = rnd(1, n), b = rnd(1, n);
            if (rnd(0, 1)) a = -a;
            if (rnd(0, 1)) b = -b;
            cl.push_back({a, b});
        }
        vector<int> val;
        bool ok2 = sat_br(n, cl, val);

        two_sat ts;
        ts.init(n);
        for (auto [a, b] : cl) ts.add(a, b);
        bool ok1 = ts.run();
        assert(ok1 == ok2);
        if (!ok1) continue;
        for (auto [a, b] : cl) {
            bool va = a > 0 ? ts.val[a] : !ts.val[-a];
            bool vb = b > 0 ? ts.val[b] : !ts.val[-b];
            assert(va || vb);
        }
    }
}

int main() {
    t_scc();
    t_sat();
    return 0;
}
