#include "../../src/5-string/aho_corasick.cpp"

// what: tests for aho_corasick (multi pattern match).
// time: random + naive; memory: O(1)
// constraint: lowercase strings.
// usage: g++ -std=c++17 test_aho_corasick.cpp && ./a.out

mt19937_64 rng(501);
int rnd(int l, int r) {
    uniform_int_distribution<int> dis(l, r);
    return dis(rng);
}
string rnd_s(int n) {
    string s;
    for (int i = 0; i < n; i++) s.push_back('a' + rnd(0, 2));
    return s;
}

ll na_cnt(const string &t, const vector<string> &ps) {
    ll res = 0;
    for (auto &p : ps)
        for (int i = 0; i + sz(p) <= sz(t); i++)
            if (!t.compare(i, sz(p), p)) res++;
    return res;
}

void t_fix() {
    aho_corasick ac;
    vector<string> ps = {"he", "she", "his", "hers"};
    for (auto &p : ps) ac.add(p);
    ac.build();
    string t = "ahishers";
    assert(ac.match_any(t));
    assert(ac.count(t) == 4);
}

void t_rnd() {
    for (int it = 0; it < 300; it++) {
        int n = rnd(0, 8);
        vector<string> ps;
        aho_corasick ac;
        for (int i = 0; i < n; i++) {
            string p = rnd_s(rnd(1, 6));
            ps.push_back(p);
            ac.add(p);
        }
        ac.build();
        string t = rnd_s(rnd(0, 50));
        ll exp = na_cnt(t, ps);
        assert(ac.match_any(t) == (exp > 0));
        assert(ac.count(t) == exp);
    }
}

int main() {
    t_fix();
    t_rnd();
    return 0;
}
