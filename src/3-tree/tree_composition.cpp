#include "../common/common.hpp"

const int MAXN = 505050;
const int MAXD = 18;
int n, q;
int par[MAXN][MAXD + 1];
vector<int> chd[MAXN];
int in[MAXN], p, dep[MAXN];
ll dp[MAXN];
vector<int> cpchd[MAXN];
int cppar[MAXN];
void input() {
    cin >> n >> q;
    for (int i = 2; i <= n; i++) {
        cin >> par[i][0];
        chd[par[i][0]].push_back(i);
    }
}
void dfs(int v, int prv) {
    in[v] = ++p;
    dep[v] = 1 + dep[prv];
    for (auto &i : chd[v])
        if (i != prv) dfs(i, v);
}
void build_sparse_table() {
    for (int d = 0; d + 1 <= MAXD; d++)
        for (int v = 1; v <= n; v++)
            par[v][d + 1] = par[par[v][d]][d];
}
int lca(int u, int v) {
    if (dep[u] > dep[v]) swap(u, v);
    int diff = dep[v] - dep[u];
    for (int i = 0; i <= MAXD; i++) {
        if (diff & (1 << i)) {
            v = par[v][i];
        }
    }
    if (u == v) return u;
    for (int i = MAXD; i >= 0; i--) {
        if (par[u][i] ^ par[v][i]) {
            u = par[u][i];
            v = par[v][i];
        }
    }
    return par[u][0];
}
int main() {
    input();
    dfs(1, 0);
    build_sparse_table();
    while (q--) {
        int k;
        cin >> k;
        vector<int> vs(k);
        for (auto &i : vs) cin >> i;
        for (auto &i : vs) dp[i] = 1;
        sort(all(vs), [&](int p1, int p2) {
            return in[p1] < in[p2];
        });
        for (int i = 0; i + 1 < k; i++) {
            vs.push_back(lca(vs[i], vs[i + 1]));
        }
        sort(all(vs), [&](int p1, int p2) {
            return in[p1] < in[p2];
        });
        vs.erase(unique(all(vs)), vs.end());
        for (int i = 0; i + 1 < sz(vs); i++) {
            int u = vs[i], v = vs[i + 1];
            int l = lca(u, v);
            cpchd[l].push_back(v);
        }
        ll ans = 0;
        for (int i = sz(vs) - 1; i >= 0; i--) {
            int p = vs[i];
            for (auto &v : cpchd[p]) {
                ans += dp[p] * dp[v] * (dep[p] - 1);
                dp[p] += dp[v];
            }
        }
        for (auto &i : vs) {
            dp[i] = 0;
            cpchd[i].clear();
        }
        cout << ans << '\n';
    }
}