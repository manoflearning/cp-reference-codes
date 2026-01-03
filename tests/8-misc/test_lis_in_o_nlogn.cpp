#include "../../src/8-misc/lis_in_o_nlogn.cpp"

// what: tests for LIS length + sequence.
// time: random + naive; memory: O(n^2)
// constraint: fixed seed, small n.
// usage: g++ -std=c++17 test_lis_in_o_nlogn.cpp && ./a.out

mt19937_64 rng(2);
ll rnd(ll l, ll r) {
    uniform_int_distribution<ll> dis(l, r);
    return dis(rng);
}

int lis_naive(const vl &a) {
    int n = sz(a);
    vi dp(n, 1);
    int best = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < i; j++) {
            if (a[j] < a[i]) dp[i] = max(dp[i], dp[j] + 1);
        }
        best = max(best, dp[i]);
    }
    return best;
}

bool is_subseq(const vl &a, const vl &b) {
    int i = 0, j = 0;
    while (i < sz(a) && j < sz(b)) {
        if (a[i] == b[j]) j++;
        i++;
    }
    return j == sz(b);
}

bool is_strict_inc(const vl &a) {
    for (int i = 1; i < sz(a); i++)
        if (a[i - 1] >= a[i]) return false;
    return true;
}

void test_random() {
    for (int it = 0; it < 200; it++) {
        int n = (int)rnd(1, 60);
        vl a(n);
        for (int i = 0; i < n; i++) a[i] = rnd(-10, 10);
        int exp = lis_naive(a);
        assert(lis_len(a) == exp);
        vl seq = lis_seq(a);
        assert(sz(seq) == exp);
        assert(is_subseq(a, seq));
        assert(is_strict_inc(seq));
    }
}

int main() {
    test_random();
    return 0;
}
