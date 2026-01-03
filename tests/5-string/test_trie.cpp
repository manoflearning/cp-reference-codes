#include "../../src/5-string/trie.cpp"

// what: tests for trie (add/has).
// time: random + naive; memory: O(1)
// constraint: lowercase strings.
// usage: g++ -std=c++17 test_trie.cpp && ./a.out

mt19937_64 rng(506);
int rnd(int l, int r) {
    uniform_int_distribution<int> dis(l, r);
    return dis(rng);
}
string rnd_s(int n) {
    string s;
    for (int i = 0; i < n; i++) s.pb('a' + rnd(0, 2));
    return s;
}

void t_rnd() {
    trie tr;
    set<string> st;
    for (int it = 0; it < 300; it++) {
        if (rnd(0, 1)) {
            string s = rnd_s(rnd(0, 10));
            tr.add(s);
            st.insert(s);
        } else {
            string s = rnd_s(rnd(0, 10));
            assert(tr.has(s) == st.count(s));
        }
    }
}

int main() {
    t_rnd();
    return 0;
}
