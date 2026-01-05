#include "../../src/3-tree/tree_vtree.cpp"

// what: tests for tree_comp (virtual tree builder).
// time: random + brute; memory: O(n^2)
// constraint: small n.
// usage: g++ -std=c++17 test_tree_composition.cpp && ./a.out

mt19937_64 rng(9);
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

void root_tree(int n, const vector<vector<int>> &adj, int root, vector<int> &par, vector<int> &dep) {
    par.assign(n + 1, -1);
    dep.assign(n + 1, 0);
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
            dep[to] = dep[v] + 1;
            q.push(to);
        }
    }
    for (int v = 1; v <= n; v++) assert(par[v] != -1);
}

int lca_na(int a, int b, const vector<int> &par, const vector<int> &dep) {
    while (dep[a] > dep[b]) a = par[a];
    while (dep[b] > dep[a]) b = par[b];
    while (a != b) a = par[a], b = par[b];
    return a;
}

vector<int> lca_closure(vector<int> vs, const vector<int> &par, const vector<int> &dep) {
    int n = sz(par) - 1;
    sort(all(vs));
    vs.erase(unique(all(vs)), vs.end());
    vector<char> in_set(n + 1, 0);
    for (int v : vs) in_set[v] = 1;
    bool chg = 1;
    while (chg) {
        chg = 0;
        int m = sz(vs);
        for (int i = 0; i < m; i++)
            for (int j = i + 1; j < m; j++) {
                int c = lca_na(vs[i], vs[j], par, dep);
                if (!in_set[c]) {
                    in_set[c] = 1;
                    vs.push_back(c);
                    chg = 1;
                }
            }
        if (chg) {
            sort(all(vs));
            vs.erase(unique(all(vs)), vs.end());
        }
    }
    return vs;
}

void check_one(const vector<vector<int>> &adj, const vector<int> &vs) {
    int n = sz(adj) - 1;
    vector<int> par, dep;
    root_tree(n, adj, 1, par, dep);

    tree_comp tc;
    tc.init(n);
    for (int u = 1; u <= n; u++)
        for (int v : adj[u])
            if (u < v) tc.add_edge(u, v);
    tc.build(1);

    if (vs.empty()) {
        assert(tc.make(vs).empty());
        return;
    }

    auto exp_nodes = lca_closure(vs, par, dep);
    auto nodes = tc.make(vs);
    auto nodes_sorted = nodes;
    sort(all(nodes_sorted));
    assert(nodes_sorted == exp_nodes);

    vector<char> in_set(n + 1, 0);
    for (int v : exp_nodes) in_set[v] = 1;

    vector<int> in_cnt(n + 1, 0), par_vt(n + 1, 0);
    int edges = 0;
    for (int v : exp_nodes)
        for (int to : tc.vt_adj[v]) {
            assert(in_set[to]);
            edges++;
            in_cnt[to]++;
            par_vt[to] = v;
        }
    assert(edges == sz(exp_nodes) - 1);

    int root = 0;
    for (int v : exp_nodes)
        if (!in_cnt[v]) {
            assert(!root);
            root = v;
        }
    assert(root);

    for (int v : exp_nodes) {
        int p = par[v];
        while (p && !in_set[p]) p = par[p];
        if (!p)
            assert(v == root);
        else {
            assert(in_cnt[v] == 1);
            assert(par_vt[v] == p);
        }
    }

    vector<int> vis(n + 1);
    vector<int> st = {root};
    vis[root] = 1;
    while (!st.empty()) {
        int v = st.back();
        st.pop_back();
        for (int to : tc.vt_adj[v]) {
            vis[to] = 1;
            st.push_back(to);
        }
    }
    for (int v : exp_nodes) assert(vis[v]);
}

void t_fix() {
    {
        int n = 1;
        vector<vector<int>> adj(n + 1);
        check_one(adj, {});
        check_one(adj, {1});
    }
    {
        int n = 5;
        vector<vector<int>> adj(n + 1);
        for (int i = 1; i < n; i++) add_edge(adj, i, i + 1);
        check_one(adj, {3});
        check_one(adj, {2, 4});
        check_one(adj, {2, 3, 4});
        check_one(adj, {2, 2, 4, 4});
    }
}

void t_rnd() {
    for (int it = 0; it < 200; it++) {
        int n = rnd(2, 30);
        auto adj = gen_tree(n);
        int k = rnd(0, n);
        vector<int> vs;
        for (int i = 0; i < k; i++) vs.push_back(rnd(1, n));
        check_one(adj, vs);
    }
}

int main() {
    t_fix();
    t_rnd();
    return 0;
}
