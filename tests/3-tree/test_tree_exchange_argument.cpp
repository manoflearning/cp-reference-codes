#include "../../src/3-tree/tree_exchange_argument.cpp"

// what: tests for tree_xchg (basic invariants).
// time: random; memory: O(n)
// constraint: small n, default weights.
// usage: g++ -std=c++17 test_tree_xchg.cpp && ./a.out

mt19937_64 rng(11);
int rnd(int l, int r) {
    uniform_int_distribution<int> dis(l, r);
    return dis(rng);
}

void t_rnd() {
    for (int it = 0; it < 100; it++) {
        int n = rnd(2, 30);
        int root = rnd(1, n);
        tree_xchg tx;
        tx.init(n, root);
        for (int v = 2; v <= n; v++) tx.add(v, rnd(1, v - 1));
        ll ans = tx.run();
        assert(ans >= 0);
    }
}

int main() {
    t_rnd();
    return 0;
}
