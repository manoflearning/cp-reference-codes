#include "../../src/2-graph/euler_circ.cpp"

// what: tests for Euler circuit.
// time: random + edge cases; memory: O(n^2)
// constraint: small n brute.
// usage: g++ -std=c++17 test_euler_circ.cpp && ./a.out

mt19937_64 rng(2);
int rnd(int l, int r) {
    uniform_int_distribution<int> dis(l, r);
    return dis(rng);
}

int ecnt(int n, const vector<vector<int>> &cnt) {
    int m = 0;
    for (int i = 1; i <= n; i++) m += cnt[i][i];
    for (int i = 1; i <= n; i++)
        for (int j = i + 1; j <= n; j++) m += cnt[i][j];
    return m;
}

bool can_na(int n, const vector<vector<int>> &cnt) {
    vector<int> deg(n + 1);
    for (int i = 1; i <= n; i++) {
        deg[i] += 2 * cnt[i][i];
        for (int j = 1; j <= n; j++)
            if (i != j) deg[i] += cnt[i][j];
    }
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
        for (int i = 1; i <= n; i++) {
            if (i == v || cnt[v][i] == 0 || vis[i]) continue;
            vis[i] = 1;
            q.push(i);
        }
    }
    for (int i = 1; i <= n; i++)
        if (deg[i] && !vis[i]) return 0;
    return 1;
}

void add_ed(euler_cir &g, vector<vector<int>> &cnt, int u, int v) {
    g.add(u, v);
    if (u == v) cnt[u][u]++;
    else cnt[u][v]++, cnt[v][u]++;
}

void chk_run(int n, const vector<vector<int>> &cnt, const vector<int> &path) {
    int m = ecnt(n, cnt);
    if (m == 0) {
        assert(sz(path) == 1);
        return;
    }
    assert(path.front() == path.back());
    assert(sz(path) == m + 1);
    auto rem = cnt;
    for (int i = 0; i + 1 < sz(path); i++) {
        int a = path[i], b = path[i + 1];
        if (a == b) {
            assert(rem[a][a] > 0);
            rem[a][a]--;
        } else {
            assert(rem[a][b] > 0);
            rem[a][b]--;
            rem[b][a]--;
        }
    }
    assert(ecnt(n, rem) == 0);
}

void t_fix() {
    int n = 3;
    euler_cir g;
    g.init(n);
    vector<vector<int>> cnt(n + 1, vector<int>(n + 1));
    add_ed(g, cnt, 1, 2);
    add_ed(g, cnt, 2, 3);
    add_ed(g, cnt, 3, 1);
    assert(g.can());
    auto path = g.run(1);
    chk_run(n, cnt, path);

    g.init(n);
    cnt.assign(n + 1, vector<int>(n + 1));
    add_ed(g, cnt, 1, 2);
    add_ed(g, cnt, 2, 3);
    assert(!g.can());
}

void t_rnd() {
    for (int it = 0; it < 200; it++) {
        int n = rnd(1, 6);
        int m = rnd(0, 8);
        euler_cir g;
        g.init(n);
        vector<vector<int>> cnt(n + 1, vector<int>(n + 1));
        for (int i = 0; i < m; i++) {
            int u = rnd(1, n), v = rnd(1, n);
            add_ed(g, cnt, u, v);
        }
        bool ok1 = g.can();
        bool ok2 = can_na(n, cnt);
        assert(ok1 == ok2);
        if (ok1) {
            int s = 1;
            vector<int> deg(n + 1);
            for (int i = 1; i <= n; i++) {
                deg[i] += 2 * cnt[i][i];
                for (int j = 1; j <= n; j++)
                    if (i != j) deg[i] += cnt[i][j];
            }
            for (int i = 1; i <= n; i++)
                if (deg[i]) {
                    s = i;
                    break;
                }
            auto path = g.run(s);
            chk_run(n, cnt, path);
        }
    }
}

int main() {
    t_fix();
    t_rnd();
    return 0;
}
