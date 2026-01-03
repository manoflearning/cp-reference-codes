#include "../../src/2-graph/bcc.cpp"

// what: tests for bcc_graph.
// time: random + brute checks; memory: O(n+m)
// constraint: small n brute.
// usage: g++ -std=c++17 test_bcc.cpp && ./a.out

mt19937_64 rng(1);
int rnd(int l, int r) {
    uniform_int_distribution<int> dis(l, r);
    return dis(rng);
}

int ccnt(int n, const vector<pii> &ed, int sv, int se) {
    vector<vector<int>> adj(n + 1);
    for (int i = 0; i < sz(ed); i++) {
        if (i == se) continue;
        int u = ed[i].fr, v = ed[i].sc;
        if (u == sv || v == sv) continue;
        adj[u].pb(v);
        adj[v].pb(u);
    }
    vector<int> vis(n + 1);
    int cnt = 0;
    for (int v = 1; v <= n; v++) {
        if (v == sv || vis[v]) continue;
        cnt++;
        queue<int> q;
        q.push(v);
        vis[v] = 1;
        while (!q.empty()) {
            int x = q.front();
            q.pop();
            for (int to : adj[x]) {
                if (!vis[to]) vis[to] = 1, q.push(to);
            }
        }
    }
    return cnt;
}

vector<int> ap_na(int n, const vector<pii> &ed) {
    int base = ccnt(n, ed, 0, -1);
    vector<int> ap;
    for (int v = 1; v <= n; v++)
        if (ccnt(n, ed, v, -1) > base) ap.pb(v);
    return ap;
}

vector<pii> ae_na(int n, const vector<pii> &ed) {
    int base = ccnt(n, ed, 0, -1);
    vector<pii> ae;
    for (int i = 0; i < sz(ed); i++) {
        if (ccnt(n, ed, 0, i) > base) {
            int u = ed[i].fr, v = ed[i].sc;
            if (u > v) swap(u, v);
            ae.pb({u, v});
        }
    }
    sort(all(ae));
    ae.erase(unique(all(ae)), ae.end());
    return ae;
}

void chk_bcc(int n, const vector<pii> &ed, bcc_graph &g) {
    map<pii, int> cnt, got;
    for (auto [u, v] : ed) {
        if (u > v) swap(u, v);
        cnt[{u, v}]++;
    }
    for (auto &comp : g.bccs) {
        for (auto [u, v] : comp) {
            if (u > v) swap(u, v);
            got[{u, v}]++;
        }
    }
    assert(cnt == got);

    for (auto &comp : g.bccs) {
        if (sz(comp) <= 1) continue;
        vector<vector<pii>> adj(n + 1);
        for (int i = 0; i < sz(comp); i++) {
            int u = comp[i].fr, v = comp[i].sc;
            adj[u].pb({v, i});
            adj[v].pb({u, i});
        }
        for (int i = 0; i < sz(comp); i++) {
            int u = comp[i].fr, v = comp[i].sc;
            vector<int> vis(n + 1);
            queue<int> q;
            q.push(u);
            vis[u] = 1;
            while (!q.empty()) {
                int x = q.front();
                q.pop();
                for (auto [to, id] : adj[x]) {
                    if (id == i || vis[to]) continue;
                    vis[to] = 1;
                    q.push(to);
                }
            }
            assert(vis[v]);
        }
    }
}

void t_fix() {
    int n = 3;
    vector<pii> ed = {{1, 2}, {2, 3}};
    bcc_graph g;
    g.init(n);
    for (auto [u, v] : ed) g.add(u, v);
    g.run();
    auto ap = g.ap;
    auto ae = g.ae;
    sort(all(ap));
    sort(all(ae));
    assert(ap == vector<int>({2}));
    assert(ae == vector<pii>({{1, 2}, {2, 3}}));
    chk_bcc(n, ed, g);
}

void t_rnd() {
    for (int it = 0; it < 200; it++) {
        int n = rnd(2, 7);
        int m = rnd(0, 10);
        vector<pii> ed;
        for (int i = 0; i < m; i++) {
            int u = rnd(1, n), v = rnd(1, n);
            if (u == v) {
                i--;
                continue;
            }
            ed.pb({u, v});
        }
        bcc_graph g;
        g.init(n);
        for (auto [u, v] : ed) g.add(u, v);
        g.run();
        auto ap = g.ap;
        auto ae = g.ae;
        sort(all(ap));
        ap.erase(unique(all(ap)), ap.end());
        sort(all(ae));
        ae.erase(unique(all(ae)), ae.end());
        auto ap2 = ap_na(n, ed);
        auto ae2 = ae_na(n, ed);
        assert(ap == ap2);
        assert(ae == ae2);
        chk_bcc(n, ed, g);
    }
}

int main() {
    t_fix();
    t_rnd();
    return 0;
}
