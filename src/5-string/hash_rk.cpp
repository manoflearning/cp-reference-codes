#include "../0-common/common.hpp"

// what: probabilistic substring matching using double rolling hash.
// time: build O(n), get O(1), match O(n); memory: O(n)
// constraint: probabilistic (hash collision), returns 0-indexed match positions.
// usage: auto pos = rk_match(t, p); // p in t
struct rabin_karp {
    static constexpr ll MOD1 = 1000000007;
    static constexpr ll MOD2 = 1000000009;
    static constexpr ll BASE = 911382323;
    vector<ll> p1, p2, h1, h2;

    void build(const string &s) {
        // goal: precompute prefix hashes and powers.
        int n = sz(s);
        p1.assign(n + 1, 1);
        p2.assign(n + 1, 1);
        h1.assign(n + 1, 0);
        h2.assign(n + 1, 0);
        for (int i = 0; i < n; i++) {
            ll x = (unsigned char)s[i] + 1;
            p1[i + 1] = p1[i] * BASE % MOD1;
            p2[i + 1] = p2[i] * BASE % MOD2;
            h1[i + 1] = (h1[i] * BASE + x) % MOD1;
            h2[i + 1] = (h2[i] * BASE + x) % MOD2;
        }
    }
    pll get(int l, int r) const { // [l, r)
        // result: hash of s[l..r).
        ll x1 = (h1[r] - h1[l] * p1[r - l]) % MOD1;
        ll x2 = (h2[r] - h2[l] * p2[r - l]) % MOD2;
        if (x1 < 0) x1 += MOD1;
        if (x2 < 0) x2 += MOD2;
        return {x1, x2};
    }
};

vector<int> rk_match(const string &t, const string &p) {
    // result: all positions where p matches t (by hash).
    vector<int> res;
    int n = sz(t), m = sz(p);
    if (!m || n < m) return res;
    rabin_karp ht, hp;
    ht.build(t);
    hp.build(p);
    pll hp0 = hp.get(0, m);
    for (int i = 0; i + m <= n; i++)
        if (ht.get(i, i + m) == hp0) res.push_back(i);
    return res;
}
