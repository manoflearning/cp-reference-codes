#include "../../src/5-string/kmp_algorithm.cpp"

// what: tests for kmp_match.
// time: random + naive; memory: O(1)
// constraint: none.
// usage: g++ -std=c++17 test_kmp_algorithm.cpp && ./a.out

mt19937_64 rng(502);
int rnd(int l, int r) {
    uniform_int_distribution<int> dis(l, r);
    return dis(rng);
}
string rnd_s(int n) {
    string s;
    for (int i = 0; i < n; i++) s.pb('a' + rnd(0, 2));
    return s;
}

vector<int> na_match(const string &t, const string &p) {
    vector<int> res;
    if (p.empty()) return res;
    for (int i = 0; i + sz(p) <= sz(t); i++)
        if (!t.compare(i, sz(p), p)) res.pb(i);
    return res;
}

void t_fix() {
    assert((kmp_match("ababa", "aba") == vector<int>{0, 2}));
    assert((kmp_match("aaaaa", "aa") == vector<int>{0, 1, 2, 3}));
}

void t_rnd() {
    for (int it = 0; it < 300; it++) {
        string t = rnd_s(rnd(0, 60));
        string p = rnd_s(rnd(0, 20));
        assert(kmp_match(t, p) == na_match(t, p));
    }
}

int main() {
    t_fix();
    t_rnd();
    return 0;
}
