#include "../common/common.hpp"

// what: trie for lowercase strings.
// time: add/has O(|s|); memory: O(nodes*ALPHA)
// constraint: 'a'..'z'.
// usage: trie tr; tr.add(s); bool ok=tr.has(s);
struct trie {
    static constexpr int ALPHA = 26;
    vector<array<int, ALPHA>> nxt;
    vector<char> term;

    trie() { init(); }

    void init() {
        nxt.assign(1, {});
        nxt[0].fill(-1);
        term.assign(1, 0);
    }

    int add(const string &s) {
        int v = 0;
        for (char ch : s) {
            int c = ch - 'a';
            if (nxt[v][c] == -1) {
                nxt[v][c] = sz(nxt);
                nxt.push_back({});
                nxt.back().fill(-1);
                term.push_back(0);
            }
            v = nxt[v][c];
        }
        term[v] = 1;
        return v;
    }

    bool has(const string &s) const {
        int v = 0;
        for (char ch : s) {
            int c = ch - 'a';
            if (nxt[v][c] == -1) return false;
            v = nxt[v][c];
        }
        return term[v];
    }
};
