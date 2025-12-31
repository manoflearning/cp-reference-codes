#include "../common/common.hpp"

// what: aho-corasick automaton for multiple pattern matching (lowercase).
// time: add O(|p|), build O(nodes*ALPHA), query O(|t|); memory: O(nodes*ALPHA)
// constraint: patterns/text are 'a'..'z', call build() after add().
// usage: aho_corasick ac; ac.add(p); ac.build(); bool any=ac.match_any(t); ll cnt=ac.count(t);
struct aho_corasick {
    static constexpr int ALPHA = 26;
    vector<array<int, ALPHA>> nxt;
    vector<int> fail, out;

    aho_corasick() { init(); }

    void init() {
        nxt.assign(1, {});
        nxt[0].fill(-1);
        fail.assign(1, 0);
        out.assign(1, 0);
    }

    int add(const string &s) {
        int v = 0;
        for (char ch : s) {
            int c = ch - 'a';
            if (nxt[v][c] == -1) {
                nxt[v][c] = sz(nxt);
                nxt.push_back({});
                nxt.back().fill(-1);
                fail.push_back(0);
                out.push_back(0);
            }
            v = nxt[v][c];
        }
        out[v]++;
        return v;
    }

    void build() {
        queue<int> q;
        for (int c = 0; c < ALPHA; c++) {
            int v = nxt[0][c];
            if (v != -1) {
                fail[v] = 0;
                q.push(v);
            } else {
                nxt[0][c] = 0;
            }
        }
        while (!q.empty()) {
            int v = q.front();
            q.pop();
            out[v] += out[fail[v]];
            for (int c = 0; c < ALPHA; c++) {
                int to = nxt[v][c];
                if (to != -1) {
                    fail[to] = nxt[fail[v]][c];
                    q.push(to);
                } else {
                    nxt[v][c] = nxt[fail[v]][c];
                }
            }
        }
    }

    int step(int v, char ch) const { return nxt[v][ch - 'a']; }

    bool match_any(const string &t) const {
        int v = 0;
        for (char ch : t) {
            v = step(v, ch);
            if (out[v]) return true;
        }
        return false;
    }

    ll count(const string &t) const {
        ll res = 0;
        int v = 0;
        for (char ch : t) {
            v = step(v, ch);
            res += out[v];
        }
        return res;
    }
};
