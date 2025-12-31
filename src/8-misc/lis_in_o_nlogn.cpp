#include "../common/common.hpp"

// what: LIS length and one sequence (strictly increasing).
// time: O(n log n); memory: O(n)
// constraint: use lower_bound for strict; use upper_bound for non-decreasing.
// usage: int len = lis_len(a); auto seq = lis_seq(a);

int lis_len(const vector<ll> &a) {
    vector<ll> tail;
    for (ll x : a) {
        auto it = lower_bound(tail.begin(), tail.end(), x);
        if (it == tail.end()) tail.push_back(x);
        else *it = x;
    }
    return sz(tail);
}

vector<ll> lis_seq(const vector<ll> &a) {
    int n = sz(a);
    vector<ll> tail;
    vector<int> tail_idx;
    vector<int> pre(n, -1);
    for (int i = 0; i < n; i++) {
        ll x = a[i];
        int pos = lower_bound(tail.begin(), tail.end(), x) - tail.begin();
        if (pos == sz(tail)) {
            tail.push_back(x);
            tail_idx.push_back(i);
        } else {
            tail[pos] = x;
            tail_idx[pos] = i;
        }
        if (pos > 0) pre[i] = tail_idx[pos - 1];
    }
    vector<ll> ret;
    int cur = tail_idx.empty() ? -1 : tail_idx.back();
    while (cur != -1) {
        ret.push_back(a[cur]);
        cur = pre[cur];
    }
    reverse(all(ret));
    return ret;
}
