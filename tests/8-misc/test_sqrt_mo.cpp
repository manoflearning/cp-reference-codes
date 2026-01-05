#include "../../src/8-misc/sqrt_mo.cpp"

// what: tests for mo's algorithm runner (distinct count).
// time: random + naive; memory: O(n)
// constraint: fixed seed, small values.
// usage: g++ -std=c++17 test_sqrt_mo.cpp && ./a.out

mt19937_64 rng(2);
int rnd_int(int l, int r) {
    uniform_int_distribution<int> dis(l, r);
    return dis(rng);
}

void test_distinct() {
    int n = 200, qn = 200;
    vector<int> a(n + 1, 0);
    for (int i = 1; i <= n; i++) a[i] = rnd_int(0, 30);

    vector<pii> qs(qn);
    for (int i = 0; i < qn; i++) {
        int l = rnd_int(1, n);
        int r = rnd_int(l, n);
        qs[i] = {l, r};
    }

    vector<int> naive(qn, 0), ans(qn, 0);
    for (int i = 0; i < qn; i++) {
        vector<int> cnt(31, 0);
        int cur = 0;
        for (int j = qs[i].fr; j <= qs[i].sc; j++) {
            if (cnt[a[j]]++ == 0) cur++;
        }
        naive[i] = cur;
    }

    mo solver(n);
    for (int i = 0; i < qn; i++) solver.add_query(qs[i].fr, qs[i].sc, i);

    vector<int> cnt(31, 0);
    int cur = 0;
    auto add = [&](int idx) {
        if (cnt[a[idx]]++ == 0) cur++;
    };
    auto del = [&](int idx) {
        if (--cnt[a[idx]] == 0) cur--;
    };
    auto out = [&](int idx) { ans[idx] = cur; };
    solver.run(add, del, out);

    assert(ans == naive);
}

int main() {
    test_distinct();
    return 0;
}
