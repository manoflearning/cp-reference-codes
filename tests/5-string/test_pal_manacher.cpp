#include "../../src/5-string/pal_manacher.cpp"

// what: tests for manacher (pal radii).
// time: random + naive; memory: O(1)
// constraint: small n.
// usage: g++ -std=c++17 test_pal_manacher.cpp && ./a.out

mt19937_64 rng(503);
int rnd(int l, int r) {
    uniform_int_distribution<int> dis(l, r);
    return dis(rng);
}
string rnd_s(int n) {
    string s;
    for (int i = 0; i < n; i++) s.push_back('a' + rnd(0, 2));
    return s;
}

int na_best(const string &s) {
    int n = sz(s);
    int best = 0;
    for (int c = 0; c < n; c++) {
        for (int l = c, r = c; l >= 0 && r < n && s[l] == s[r]; l--, r++)
            best = max(best, r - l + 1);
        for (int l = c, r = c + 1; l >= 0 && r < n && s[l] == s[r]; l--, r++)
            best = max(best, r - l + 1);
    }
    return best;
}

void check_one(const string &s) {
    auto [d1, d2] = manacher(s);
    assert(sz(d1) == sz(s));
    assert(sz(d2) == sz(s));
    int got = 0;
    for (int i = 0; i < sz(s); i++) {
        got = max(got, 2 * d1[i] - 1);
        got = max(got, 2 * d2[i]);
    }
    assert(got == na_best(s));
}

void t_fix() {
    check_one("");
    check_one("a");
    check_one("aa");
    check_one("abacaba");
    check_one("abba");
}

void t_rnd() {
    for (int it = 0; it < 300; it++) check_one(rnd_s(rnd(0, 50)));
}

int main() {
    t_fix();
    t_rnd();
    return 0;
}
