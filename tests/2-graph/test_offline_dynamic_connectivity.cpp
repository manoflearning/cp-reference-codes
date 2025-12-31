#include "../../src/2-graph/offline_dynamic_connectivity.cpp"

// what: tests for offline dynamic connectivity.
// time: random + brute; memory: O(n+q)
// constraint: ops consistent; small n brute.
// usage: g++ -std=c++17 test_offline_dynamic_connectivity.cpp && ./a.out

mt19937_64 rng(6);
int rnd(int l, int r) {
    uniform_int_distribution<int> dis(l, r);
    return dis(rng);
}

int conn(int n, const set<pii> &act, int s, int e) {
    if (s == e) return 1;
    vector<vector<int>> adj(n + 1);
    for (auto [u, v] : act) {
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    vector<int> vis(n + 1);
    queue<int> q;
    q.push(s);
    vis[s] = 1;
    while (!q.empty()) {
        int v = q.front();
        q.pop();
        for (int to : adj[v]) {
            if (!vis[to]) vis[to] = 1, q.push(to);
        }
    }
    return vis[e];
}

void t_fix() {
    int n = 4, q = 6;
    vector<int> op(q + 1), u(q + 1), v(q + 1), ans(q + 1);
    op[1] = 1, u[1] = 1, v[1] = 2;
    op[2] = 3, u[2] = 1, v[2] = 3;
    op[3] = 1, u[3] = 2, v[3] = 3;
    op[4] = 3, u[4] = 1, v[4] = 3;
    op[5] = 2, u[5] = 1, v[5] = 2;
    op[6] = 3, u[6] = 1, v[6] = 2;

    set<pii> act;
    for (int i = 1; i <= q; i++) {
        int a = u[i], b = v[i];
        if (a > b) swap(a, b);
        if (op[i] == 1) act.insert({a, b});
        else if (op[i] == 2) act.erase({a, b});
        else ans[i] = conn(n, act, a, b);
    }

    dyn_conn g;
    g.init(n, q);
    for (int i = 1; i <= q; i++) g.add_op(i, op[i], u[i], v[i]);
    g.build();
    g.run();
    for (int i = 1; i <= q; i++)
        if (op[i] == 3) assert(g.ans[i] == ans[i]);
}

void t_rnd() {
    for (int it = 0; it < 200; it++) {
        int n = rnd(2, 8);
        int q = rnd(1, 40);
        vector<int> op(q + 1), u(q + 1), v(q + 1), ans(q + 1);
        set<pii> act;
        for (int i = 1; i <= q; i++) {
            int t = rnd(0, 9);
            if (act.empty() || t < 4) {
                int a = 0, b = 0;
                for (int tr = 0; tr < 20; tr++) {
                    a = rnd(1, n), b = rnd(1, n);
                    if (a == b) continue;
                    if (a > b) swap(a, b);
                    if (!act.count({a, b})) break;
                }
                if (!a || !b || act.count({a, b})) {
                    op[i] = 3;
                    u[i] = rnd(1, n), v[i] = rnd(1, n);
                    ans[i] = conn(n, act, u[i], v[i]);
                } else {
                    op[i] = 1;
                    u[i] = a, v[i] = b;
                    act.insert({a, b});
                }
            } else if (t < 7) {
                int idx = rnd(0, sz(act) - 1);
                auto it2 = act.begin();
                advance(it2, idx);
                op[i] = 2;
                u[i] = it2->fr;
                v[i] = it2->sc;
                act.erase(it2);
            } else {
                op[i] = 3;
                u[i] = rnd(1, n), v[i] = rnd(1, n);
                ans[i] = conn(n, act, u[i], v[i]);
            }
        }

        dyn_conn g;
        g.init(n, q);
        for (int i = 1; i <= q; i++) g.add_op(i, op[i], u[i], v[i]);
        g.build();
        g.run();
        for (int i = 1; i <= q; i++)
            if (op[i] == 3) assert(g.ans[i] == ans[i]);
    }
}

int main() {
    t_fix();
    t_rnd();
    return 0;
}
