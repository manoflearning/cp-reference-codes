#include "../common/common.hpp"

// what: suffix array (doubling + counting sort) and LCP (kasai).
// time: build_sa O(n log n), build_lcp O(n); memory: O(n)
// constraint: s is 0-indexed string, sa is 0-indexed positions.
// usage: suffix_array sa; sa.build(s); // sa.sa, sa.lcp (lcp[i]=lcp(sa[i], sa[i-1]))
vector<int> build_sa(const string &s) {
    int n = sz(s);
    if (!n) return {};
    int m = max(256, n) + 1;
    vector<int> sa(n), r(2 * n), nr(2 * n), cnt(m), idx(n);
    for (int i = 0; i < n; i++) sa[i] = i, r[i] = (unsigned char)s[i];
    for (int d = 1; d < n; d <<= 1) {
        auto cmp = [&](int i, int j) {
            if (r[i] != r[j]) return r[i] < r[j];
            return r[i + d] < r[j + d];
        };
        fill(all(cnt), 0);
        for (int i = 0; i < n; i++) cnt[r[i + d]]++;
        for (int i = 1; i < m; i++) cnt[i] += cnt[i - 1];
        for (int i = n - 1; i >= 0; i--) idx[--cnt[r[i + d]]] = i;
        fill(all(cnt), 0);
        for (int i = 0; i < n; i++) cnt[r[i]]++;
        for (int i = 1; i < m; i++) cnt[i] += cnt[i - 1];
        for (int i = n - 1; i >= 0; i--) sa[--cnt[r[idx[i]]]] = idx[i];
        nr[sa[0]] = 1;
        for (int i = 1; i < n; i++) nr[sa[i]] = nr[sa[i - 1]] + cmp(sa[i - 1], sa[i]);
        for (int i = 0; i < n; i++) r[i] = nr[i];
        if (r[sa[n - 1]] == n) break;
    }
    return sa;
}

vector<int> build_lcp(const string &s, const vector<int> &sa) {
    int n = sz(s);
    vector<int> lcp(n), rk(n);
    for (int i = 0; i < n; i++) rk[sa[i]] = i;
    for (int i = 0, k = 0; i < n; i++) {
        int r = rk[i];
        if (!r) continue;
        int j = sa[r - 1];
        while (i + k < n && j + k < n && s[i + k] == s[j + k]) k++;
        lcp[r] = k;
        if (k) k--;
    }
    return lcp;
}

struct suffix_array {
    vector<int> sa, lcp;
    void build(const string &s) {
        sa = build_sa(s);
        lcp = build_lcp(s, sa);
    }
};
