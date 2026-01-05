#include "../../src/2-graph/sat_2sat.cpp"

// what: tests for two_sat.
// time: random + brute; memory: O(2^n)
// constraint: small n brute.
// usage: g++ -std=c++17 test_sat_2sat.cpp && ./a.out

mt19937_64 rng(4);
int rnd(int l, int r) {
    uniform_int_distribution<int> dis(l, r);
    return dis(rng);
}

bool sat_br(int n, const vector<pii> &cl, vector<int> &val) {
    int lim = 1 << n;
    for (int mask = 0; mask < lim; mask++) {
        bool ok = 1;
        for (auto [a, b] : cl) {
            bool va = (a > 0) ? ((mask >> (a - 1)) & 1) : !((mask >> (-a - 1)) & 1);
            bool vb = (b > 0) ? ((mask >> (b - 1)) & 1) : !((mask >> (-b - 1)) & 1);
            if (!(va || vb)) {
                ok = 0;
                break;
            }
        }
        if (!ok) continue;
        val.assign(n + 1, 0);
        for (int i = 1; i <= n; i++) val[i] = (mask >> (i - 1)) & 1;
        return 1;
    }
    return 0;
}

void t_sat() {
    for (int it = 0; it < 200; it++) {
        int n = rnd(1, 8);
        int m = rnd(0, 12);
        vector<pii> cl;
        for (int i = 0; i < m; i++) {
            int a = rnd(1, n), b = rnd(1, n);
            if (rnd(0, 1)) a = -a;
            if (rnd(0, 1)) b = -b;
            cl.push_back({a, b});
        }
        vector<int> val;
        bool ok2 = sat_br(n, cl, val);

        two_sat ts;
        ts.init(n);
        for (auto [a, b] : cl) ts.add(a, b);
        bool ok1 = ts.run();
        assert(ok1 == ok2);
        if (!ok1) continue;
        for (auto [a, b] : cl) {
            bool va = a > 0 ? ts.val[a] : !ts.val[-a];
            bool vb = b > 0 ? ts.val[b] : !ts.val[-b];
            assert(va || vb);
        }
    }
}

int main() {
    t_sat();
    return 0;
}
