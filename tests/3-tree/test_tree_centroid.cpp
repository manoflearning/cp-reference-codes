#include "../../src/3-tree/tree_centroid.cpp"

// what: tests for cen_decomp.
// time: random + brute; memory: O(n^2)
// constraint: small n (for brute checks).
// usage: g++ -std=c++17 test_centroid_decomp.cpp && ./a.out

mt19937_64 rng(10);
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

int get_root(int n, const vector<int> &par) {
    int root = 0;
    for (int v = 1; v <= n; v++)
        if (!par[v]) {
            assert(!root);
            root = v;
        }
    assert(root);
    return root;
}

void get_sub(int v, const vector<vector<int>> &chd, vector<int> &sub) {
    sub[v] = 1;
    for (int to : chd[v]) {
        get_sub(to, chd, sub);
        sub[v] += sub[to];
    }
}

vector<int> get_nodes(int v, const vector<vector<int>> &chd) {
    vector<int> res;
    vector<int> st = {v};
    while (!st.empty()) {
        int x = st.back();
        st.pop_back();
        res.push_back(x);
        for (int to : chd[x]) st.push_back(to);
    }
    return res;
}

void check_one(const vector<vector<int>> &adj) {
    int n = sz(adj) - 1;
    cen_decomp cd;
    cd.init(n);
    for (int u = 1; u <= n; u++)
        for (int v : adj[u])
            if (u < v) cd.add_edge(u, v);
    cd.build(1);

    int root = get_root(n, cd.par);

    // check: centroid tree is a rooted tree on [1..n].
    vector<int> vis(n + 1);
    queue<int> q;
    q.push(root);
    vis[root] = 1;
    int cnt = 0, edges = 0;
    while (!q.empty()) {
        int v = q.front();
        q.pop();
        cnt++;
        for (int to : cd.chd[v]) {
            edges++;
            assert(cd.par[to] == v);
            assert(!vis[to]);
            vis[to] = 1;
            q.push(to);
        }
    }
    assert(cnt == n);
    assert(edges == n - 1);

    vector<int> sub(n + 1);
    get_sub(root, cd.chd, sub);

    // check: centroid property (each child component size <= half).
    for (int v = 1; v <= n; v++)
        for (int to : cd.chd[v]) assert(sub[to] * 2 <= sub[v]);

    // check: each centroid child subtree stays in one original component after removing centroid.
    for (int c = 1; c <= n; c++) {
        auto nodes_c = get_nodes(c, cd.chd);
        vector<char> in_c(n + 1, 0);
        for (int v : nodes_c) in_c[v] = 1;

        vector<int> first(n + 1, 0);
        queue<int> qq;
        for (int nb : adj[c]) {
            if (!in_c[nb]) continue;
            first[nb] = nb;
            qq.push(nb);
        }
        while (!qq.empty()) {
            int v = qq.front();
            qq.pop();
            for (int to : adj[v]) {
                if (to == c || !in_c[to] || first[to]) continue;
                first[to] = first[v];
                qq.push(to);
            }
        }
        for (int v : nodes_c)
            if (v != c) assert(first[v]);

        vector<int> labs;
        for (int x : cd.chd[c]) {
            int lab = first[x];
            assert(lab);
            labs.push_back(lab);
            auto nodes_x = get_nodes(x, cd.chd);
            for (int v : nodes_x) assert(first[v] == lab);
        }
        sort(all(labs));
        labs.erase(unique(all(labs)), labs.end());
        assert(sz(labs) == sz(cd.chd[c]));
    }
}

void t_fix() {
    {
        int n = 1;
        vector<vector<int>> adj(n + 1);
        check_one(adj);
    }
    {
        int n = 2;
        vector<vector<int>> adj(n + 1);
        add_edge(adj, 1, 2);
        check_one(adj);
    }
    {
        int n = 7;
        vector<vector<int>> adj(n + 1);
        for (int i = 1; i < n; i++) add_edge(adj, i, i + 1);
        check_one(adj);
    }
    {
        int n = 9;
        vector<vector<int>> adj(n + 1);
        for (int i = 2; i <= n; i++) add_edge(adj, 1, i);
        check_one(adj);
    }
}

void t_rnd() {
    for (int it = 0; it < 200; it++) check_one(gen_tree(rnd(1, 70)));
}

int main() {
    t_fix();
    t_rnd();
    return 0;
}
