#include "../common/common.hpp"

int flag;
struct Seg {
    vector<vector<pii>> t;
    void build(int n) {
        for (flag = 1; flag < n; flag <<= 1);
        t.resize(flag << 1);
    }
    void modify(int l, int r, pii val, int n = 1, int nl = 1, int nr = flag) {
        if (r < nl || nr < l) return;
        if (l <= nl && nr <= r) {
            t[n].push_back(val);
            return;
        }
        int mid = (nl + nr) >> 1;
        modify(l, r, val, n << 1, nl, mid);
        modify(l, r, val, n << 1 | 1, mid + 1, nr);
    }
} seg;
struct UF {
    vector<int> par, siz, stk;
    void build(int n) {
        par.resize(n + 1);
        iota(all(par), 0);
        siz.resize(n + 1, 1);
    }
    int find(int x) {
        if (par[x] == x) return x;
        return find(par[x]);
    }
    void merge(int u, int v) {
        u = find(u), v = find(v);
        if (siz[u] < siz[v]) swap(u, v);
        par[v] = u;
        siz[u] += siz[v];
        stk.push_back(v);
    }
    void restore() {
        assert(!stk.empty());
        int v = stk.back();
        stk.pop_back();
        siz[par[v]] -= siz[v];
        par[v] = v;
    }
} uf;
int n, m;
map<pii, int> mp;
pii qu[101010];
int ans[101010];
void input() {
    cin >> n >> m;
    uf.build(n);
    seg.build(m);
    for (int i = 1; i <= m; i++) {
        int op, u, v;
        cin >> op >> u >> v;
        if (u > v) swap(u, v);

        if (op == 1) mp[{u, v}] = i;
        if (op == 2) seg.modify(mp[{u, v}], i - 1, {u, v}), mp.erase({u, v});
        if (op == 3) qu[i] = {u, v};
    }
    for (auto &[val, l] : mp) seg.modify(l, m, val);
}
void odc(int n = 1, int nl = 1, int nr = flag) {
    int cnt = 0;
    for (auto [u, v] : seg.t[n])
        if (uf.find(u) != uf.find(v)) uf.merge(u, v), cnt++;
    if (nl == nr) {
        if (nl <= m && qu[nl].fr)
            ans[nl] = (uf.find(qu[nl].fr) == uf.find(qu[nl].sc));
        while (cnt--) uf.restore();
        return;
    }
    int mid = (nl + nr) >> 1;
    odc(n << 1, nl, mid);
    odc(n << 1 | 1, mid + 1, nr);
    while (cnt--) uf.restore();
}
int main() {
    input();
    odc();
    for (int i = 1; i <= m; i++)
        if (qu[i].fr) cout << ans[i] << '\n';
}