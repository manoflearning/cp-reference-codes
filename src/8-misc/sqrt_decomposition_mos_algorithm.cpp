#include "../common/common.hpp"

// what: reorder offline range queries to minimize add/del operations (Mo's algorithm).
// time: O((n+q) * sqrt(n)); memory: O(q)
// constraint: 0-indexed, inclusive [l, r]; add/del by index.
// usage: mo solver(n); solver.add_query(l, r, idx); solver.run(add, del, out);
struct mo {
    struct qry {
        int l, r, idx;
    };

    int n, bs;
    vector<qry> q;

    mo(int n_ = 0) { init(n_); }
    void init(int n_) {
        // goal: set array size and reset queries.
        n = n_;
        bs = max(1, (int)sqrt(n));
        q.clear();
    }
    void add_query(int l, int r, int idx) { q.pb({l, r, idx}); }

    template <class Add, class Del, class Out>
    void run(Add add, Del del, Out out) {
        // goal: process queries in Mo order with callbacks.
        sort(all(q), [&](const qry &a, const qry &b) {
            int ba = a.l / bs, bb = b.l / bs;
            if (ba != bb) return ba < bb;
            return (ba & 1) ? a.r > b.r : a.r < b.r;
        });
        int l = 0, r = -1;
        for (const auto &qr : q) {
            while (l > qr.l) add(--l);
            while (r < qr.r) add(++r);
            while (l < qr.l) del(l++);
            while (r > qr.r) del(r--);
            out(qr.idx);
        }
    }
};
