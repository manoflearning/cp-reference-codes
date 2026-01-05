#include "../../src/3-tree/tree_xchg.cpp"

// what: tests for tree_xchg (exchange-argument greedy; brute checked).
// time: random + brute; memory: O(n!)
// constraint: small n.
// usage: g++ -std=c++17 test_tree_exchange_argument.cpp && ./a.out

mt19937_64 rng(11);
int rnd(int l, int r) {
    uniform_int_distribution<int> dis(l, r);
    return dis(rng);
}

void add_edge(vector<vector<int>> &adj, int u, int v) {
    adj[u].push_back(v);
    adj[v].push_back(u);
}

vector<vector<int>> gen_tree(int n) {
    vector<vector<int>> adj(n + 1);
    for (int v = 2; v <= n; v++) add_edge(adj, v, rnd(1, v - 1));
    return adj;
}

vector<vector<int>> get_child(int n, const vector<vector<int>> &adj, int root) {
    vector<vector<int>> ch(n + 1);
    vector<int> par(n + 1, -1);
    queue<int> q;
    q.push(root);
    par[root] = 0;
    while (!q.empty()) {
        int v = q.front();
        q.pop();
        for (int to : adj[v]) {
            if (to == par[v]) continue;
            if (par[to] != -1) continue;
            par[to] = v;
            ch[v].push_back(to);
            q.push(to);
        }
    }
    for (int v = 1; v <= n; v++) assert(par[v] != -1);
    return ch;
}

ll brute_max(int n, const vector<vector<int>> &ch, const vector<ll> &w, const vector<ll> &t) {
    vector<int> indeg(n + 1, 0);
    for (int v = 1; v <= n; v++)
        for (int to : ch[v]) indeg[to]++;
    vector<int> avail;
    for (int v = 1; v <= n; v++)
        if (!indeg[v]) avail.push_back(v);

    ll best = -(1LL << 62);
    vector<int> ord;
    ord.reserve(n);
    function<void(vector<int> &, vector<int> &, ll, ll)> dfs = [&](vector<int> &id, vector<int> &av,
                                                                   ll tm, ll cost) {
        if (sz(ord) == n) {
            best = max(best, cost);
            return;
        }
        for (int i = 0; i < sz(av); i++) {
            int v = av[i];
            ord.push_back(v);
            vector<int> id2 = id;
            vector<int> av2 = av;
            av2.erase(av2.begin() + i);
            ll tm2 = tm + t[v];
            ll cost2 = cost + w[v] * tm2;
            for (int to : ch[v]) {
                id2[to]--;
                if (!id2[to]) av2.push_back(to);
            }
            dfs(id2, av2, tm2, cost2);
            ord.pop_back();
        }
    };
    dfs(indeg, avail, 0, 0);
    return best;
}

void check_one(const vector<vector<int>> &adj, int root, const vector<ll> &w, const vector<ll> &t) {
    int n = sz(adj) - 1;
    auto ch = get_child(n, adj, root);
    ll exp = brute_max(n, ch, w, t);

    tree_xchg tx;
    tx.init(n, root);
    for (int u = 1; u <= n; u++)
        for (int v : adj[u])
            if (u < v) tx.add(u, v);
    for (int i = 1; i <= n; i++) {
        tx.ds.w[i] = w[i];
        tx.ds.t[i] = t[i];
        tx.ds.cw[i] = w[i] * t[i];
    }
    ll got = tx.run();
    assert(got == exp);
}

void t_fix() {
    {
        int n = 3;
        vector<vector<int>> adj(n + 1);
        add_edge(adj, 1, 2);
        add_edge(adj, 1, 3);
        vector<ll> w = {0, 1, 2, 3};
        vector<ll> t = {0, 1, 1, 1};
        check_one(adj, 1, w, t);
    }
}

void t_rnd() {
    for (int it = 0; it < 200; it++) {
        int n = rnd(1, 9);
        auto adj = gen_tree(n);
        int root = rnd(1, n);
        vector<ll> w(n + 1), t(n + 1);
        for (int i = 1; i <= n; i++) {
            w[i] = rnd(0, 7);
            t[i] = rnd(1, 4);
        }
        check_one(adj, root, w, t);
    }
}

int main() {
    t_fix();
    t_rnd();
    return 0;
}
