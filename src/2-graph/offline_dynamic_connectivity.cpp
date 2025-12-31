#include "../common/common.hpp"

// what: offline dynamic connectivity with segment tree + rollback dsu.
// time: O((n+q)log q); memory: O(n+q)
// constraint: 1-indexed time; ops: 1 add, 2 del, 3 query.
// usage: odc g; g.init(n,q); g.add_op(i,op,u,v); g.build(); g.run();
struct odc {
    struct seg {
        int flg;
        vector<vector<pii>> t;
        void init(int n) {
            for (flg = 1; flg < n; flg <<= 1) {}
            t.assign(flg << 1, {});
        }
        void add(int l, int r, pii e, int n = 1, int nl = 1, int nr = -1) {
            if (nr == -1) nr = flg;
            if (r < nl || nr < l) return;
            if (l <= nl && nr <= r) {
                t[n].push_back(e);
                return;
            }
            int mid = (nl + nr) >> 1;
            add(l, r, e, n << 1, nl, mid);
            add(l, r, e, n << 1 | 1, mid + 1, nr);
        }
    } sg;

    struct dsu {
        vector<int> par, siz, st;
        void init(int n) {
            par.resize(n + 1);
            iota(all(par), 0);
            siz.assign(n + 1, 1);
            st.clear();
        }
        int find(int x) {
            while (par[x] != x) x = par[x];
            return x;
        }
        bool join(int a, int b) {
            a = find(a), b = find(b);
            if (a == b) return 0;
            if (siz[a] < siz[b]) swap(a, b);
            par[b] = a;
            siz[a] += siz[b];
            st.push_back(b);
            return 1;
        }
        void undo() {
            int b = st.back();
            st.pop_back();
            int a = par[b];
            siz[a] -= siz[b];
            par[b] = b;
        }
    } uf;

    int n, q;
    map<pii, int> mp;
    vector<pii> qry;
    vector<int> ans;

    void init(int n_, int q_) {
        n = n_;
        q = q_;
        mp.clear();
        sg.init(q);
        uf.init(n);
        qry.assign(q + 1, {0, 0});
        ans.assign(q + 1, 0);
    }
    void add_op(int i, int op, int u, int v) {
        if (u > v) swap(u, v);
        if (op == 1) {
            mp[{u, v}] = i;
        } else if (op == 2) {
            sg.add(mp[{u, v}], i - 1, {u, v});
            mp.erase({u, v});
        } else if (op == 3) {
            qry[i] = {u, v};
        }
    }
    void build() {
        for (auto &[e, l] : mp) sg.add(l, q, e);
    }
    void dfs(int n = 1, int nl = 1, int nr = -1) {
        if (nr == -1) nr = sg.flg;
        int cnt = 0;
        for (auto [u, v] : sg.t[n])
            if (uf.join(u, v)) cnt++;
        if (nl == nr) {
            if (nl <= q && qry[nl].fr)
                ans[nl] = (uf.find(qry[nl].fr) == uf.find(qry[nl].sc));
            while (cnt--) uf.undo();
            return;
        }
        int mid = (nl + nr) >> 1;
        dfs(n << 1, nl, mid);
        dfs(n << 1 | 1, mid + 1, nr);
        while (cnt--) uf.undo();
    }
    void run() { dfs(); }
};
