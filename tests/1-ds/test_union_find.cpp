#include "../../src/1-ds/union_find.cpp"

// what: tests for dsu.
// time: random + edge cases; memory: O(n)
// constraint: uses assert, fixed seed.
// usage: g++ -std=c++17 test_union_find.cpp && ./a.out

mt19937_64 rng(7);
ll rnd(ll l, ll r) {
    uniform_int_distribution<ll> dis(l, r);
    return dis(rng);
}

struct naive_dsu {
    vector<int> comp;
    vector<int> siz;

    void init(int n) {
        comp.resize(n);
        siz.assign(n, 1);
        for (int i = 0; i < n; i++) comp[i] = i;
    }
    void join(int a, int b) {
        int ca = comp[a], cb = comp[b];
        if (ca == cb) return;
        for (int i = 0; i < sz(comp); i++) {
            if (comp[i] == cb) comp[i] = ca;
        }
        int cnt = 0;
        for (int i = 0; i < sz(comp); i++)
            if (comp[i] == ca) cnt++;
        siz[ca] = cnt;
    }
    bool same(int a, int b) const { return comp[a] == comp[b]; }
    int size(int a) const {
        int ca = comp[a];
        int cnt = 0;
        for (int i = 0; i < sz(comp); i++)
            if (comp[i] == ca) cnt++;
        return cnt;
    }
};

void test_dsu_basic() {
    dsu d;
    naive_dsu nd;
    int n = 3;
    d.init(n);
    nd.init(n);

    d.join(0, 1);
    nd.join(0, 1);
    assert(d.size(0) == nd.size(0));
    assert(d.find(0) == d.find(1));

    d.join(1, 2);
    nd.join(1, 2);
    assert(d.size(2) == nd.size(2));
    assert(d.find(0) == d.find(2));

    d.join(2, 2);
    assert(d.size(2) == nd.size(2));
}

void test_dsu_random() {
    int n = 30;
    dsu d;
    naive_dsu nd;
    d.init(n);
    nd.init(n);

    for (int it = 0; it < 5000; it++) {
        int op = (int)rnd(0, 2);
        if (op == 0) {
            int a = (int)rnd(0, n - 1);
            int b = (int)rnd(0, n - 1);
            d.join(a, b);
            nd.join(a, b);
        } else {
            int a = (int)rnd(0, n - 1);
            int b = (int)rnd(0, n - 1);
            bool same = nd.same(a, b);
            assert((d.find(a) == d.find(b)) == same);
            assert(d.size(a) == nd.size(a));
        }
    }
}

int main() {
    test_dsu_basic();
    test_dsu_random();
    return 0;
}
