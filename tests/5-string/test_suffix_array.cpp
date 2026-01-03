#include "../../src/5-string/suffix_array.cpp"

// what: tests for suffix_array (sa+lcp).
// time: random + naive; memory: O(1)
// constraint: small n.
// usage: g++ -std=c++17 test_suffix_array.cpp && ./a.out

mt19937_64 rng(505);
int rnd(int l, int r) {
    uniform_int_distribution<int> dis(l, r);
    return dis(rng);
}
string rnd_s(int n) {
    string s;
    for (int i = 0; i < n; i++) s.pb('a' + rnd(0, 2));
    return s;
}

bool suf_lt(const string &s, int i, int j) {
    int n = sz(s);
    while (i < n && j < n && s[i] == s[j]) i++, j++;
    if (j == n) return false;
    if (i == n) return true;
    return s[i] < s[j];
}

int lcp2(const string &s, int i, int j) {
    int n = sz(s), k = 0;
    while (i + k < n && j + k < n && s[i + k] == s[j + k]) k++;
    return k;
}

void check_one(const string &s) {
    suffix_array sa;
    sa.build(s);
    int n = sz(s);
    if (!n) {
        assert(sa.sa.empty());
        assert(sa.lcp.empty());
        return;
    }
    vector<int> exp(n);
    iota(all(exp), 0);
    sort(all(exp), [&](int i, int j) { return suf_lt(s, i, j); });
    assert(sa.sa == exp);
    vector<int> exp_lcp(n, 0);
    for (int i = 1; i < n; i++) exp_lcp[i] = lcp2(s, exp[i], exp[i - 1]);
    assert(sa.lcp == exp_lcp);
}

void t_rnd() {
    for (int it = 0; it < 200; it++) check_one(rnd_s(rnd(0, 25)));
}

int main() {
    t_rnd();
    return 0;
}
