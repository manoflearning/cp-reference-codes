#include "../common/common.hpp"

// what: maintain dynamic connectivity with union-find and size queries.
// time: init O(n), join/find amortized a(n); memory: O(n)
// constraint: 1-indexed [1, n].
// usage: dsu d; d.init(n); d.join(a, b); int r = d.find(x); int s = d.size(x);
struct dsu {
    vi p;
    void init(int n) { p.assign(n + 1, -1); }                    // goal: reset to n singletons.
    int find(int x) { return p[x] < 0 ? x : p[x] = find(p[x]); } // result: root of x.
    int size(int x) { return -p[find(x)]; }
    void join(int a, int b) {
        // goal: merge the two components.
        a = find(a), b = find(b);
        if (a == b) return;
        if (p[a] > p[b]) swap(a, b); // a has larger size (more negative)
        p[a] += p[b];
        p[b] = a;
    }
};
