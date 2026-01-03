#include "../0-common/common.hpp"

// what: store a set of lowercase strings for fast prefix traversal and lookup.
// time: add/has O(|s|); memory: O(nodes*ALPHA)
// constraint: 'a'..'z'.
// usage: trie tr; tr.add(s); bool ok=tr.has(s);
struct trie {
    static constexpr int ALPHA = 26;
    vector<array<int, ALPHA>> nxt;
    vector<char> term;

    trie() { init(); }
    void init() {
        // goal: reset to empty trie.
        nxt.assign(1, {});
        nxt[0].fill(-1);
        term.assign(1, 0);
    }
    int add(const string &s) {
        // goal: insert a string and mark its terminal node.
        int v = 0;
        for (char ch : s) {
            int c = ch - 'a';
            if (nxt[v][c] == -1) {
                nxt[v][c] = sz(nxt);
                nxt.pb({});
                nxt.back().fill(-1);
                term.pb(0);
            }
            v = nxt[v][c];
        }
        term[v] = 1;
        return v;
    }
    bool has(const string &s) const {
        // result: true if s exists as a full word.
        int v = 0;
        for (char ch : s) {
            int c = ch - 'a';
            if (nxt[v][c] == -1) return false;
            v = nxt[v][c];
        }
        return term[v];
    }
};
