#include "../common/common.hpp"

// what: disjoint set union (union by size + path comp).
// time: init O(n), join/find amortized a(n); memory: O(n)
// constraint: 1-indexed [1, n].
// usage: dsu d; d.init(n); d.join(a, b); int r = d.find(x); int s = d.size(x);
struct dsu {
    vector<int> p;
    void init(int n) { p.assign(n + 1, -1); }
    int find(int x) { return p[x] < 0 ? x : p[x] = find(p[x]); }
    int size(int x) { return -p[find(x)]; }
    void join(int a, int b) {
        a = find(a), b = find(b);
        if (a == b) return;
        if (p[a] > p[b]) swap(a, b); // a has larger size (more negative)
        p[a] += p[b];
        p[b] = a;
    }
};
