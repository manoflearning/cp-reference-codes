#include "../../src/5-string/rabin_karp_algorithm.cpp"

// what: tests for rk_match (rolling hash).
// time: random + naive; memory: O(1)
// constraint: small n.
// usage: g++ -std=c++17 test_rabin_karp_algorithm.cpp && ./a.out

mt19937_64 rng(504);
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

void t_rnd() {
    for (int it = 0; it < 300; it++) {
        string t = rnd_s(rnd(0, 80));
        string p = rnd_s(rnd(0, 20));
        auto got = rk_match(t, p);
        for (int i : got) assert(!t.compare(i, sz(p), p));
        assert(got == na_match(t, p));
    }
}

int main() {
    t_rnd();
    return 0;
}
