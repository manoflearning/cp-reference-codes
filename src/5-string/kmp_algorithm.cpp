#include "../common/common.hpp"

// what: KMP (prefix function) for exact pattern matching.
// time: O(|t|+|p|); memory: O(|p|)
// constraint: returns 0-indexed match positions.
// usage: auto pos = kmp_match(t, p); // p in t
vector<int> kmp_pi(const string &p) {
    vector<int> pi(sz(p));
    for (int i = 1, j = 0; i < sz(p); i++) {
        while (j && p[i] != p[j]) j = pi[j - 1];
        if (p[i] == p[j]) pi[i] = ++j;
    }
    return pi;
}

vector<int> kmp_match(const string &t, const string &p) {
    vector<int> res;
    if (p.empty()) return res;
    auto pi = kmp_pi(p);
    for (int i = 0, j = 0; i < sz(t); i++) {
        while (j && t[i] != p[j]) j = pi[j - 1];
        if (t[i] != p[j]) continue;
        if (j == sz(p) - 1) {
            res.push_back(i - (sz(p) - 1));
            j = pi[j];
        } else {
            j++;
        }
    }
    return res;
}
