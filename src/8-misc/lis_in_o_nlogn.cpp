#include "../0-common/common.hpp"

// what: compute LIS length and reconstruct one increasing subsequence.
// time: O(n log n); memory: O(n)
// constraint: use lower_bound for strict; use upper_bound for non-decreasing.
// usage: int len = lis_len(a); auto seq = lis_seq(a);

int lis_len(const vl &a) {
    // result: length of LIS.
    vl tail;
    for (ll x : a) {
        auto it = lower_bound(all(tail), x);
        if (it == tail.end()) tail.pb(x);
        else *it = x;
    }
    return sz(tail);
}

vl lis_seq(const vl &a) {
    // result: one LIS sequence.
    int n = sz(a);
    vl tail;
    vi tail_idx;
    vi pre(n, -1);
    for (int i = 0; i < n; i++) {
        ll x = a[i];
        int pos = lower_bound(all(tail), x) - tail.begin();
        if (pos == sz(tail)) {
            tail.pb(x);
            tail_idx.pb(i);
        } else {
            tail[pos] = x;
            tail_idx[pos] = i;
        }
        if (pos > 0) pre[i] = tail_idx[pos - 1];
    }
    vl ret;
    int cur = tail_idx.empty() ? -1 : tail_idx.back();
    while (cur != -1) {
        ret.pb(a[cur]);
        cur = pre[cur];
    }
    reverse(all(ret));
    return ret;
}
