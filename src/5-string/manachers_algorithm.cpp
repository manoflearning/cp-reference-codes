#include "../0-common/common.hpp"

// what: compute longest palindrome radius at every center (odd/even).
// time: O(n); memory: O(n)
// constraint: 0-indexed; d1[i]=odd radius, d2[i]=even radius.
// usage: auto [d1,d2]=manacher(s); // max len = max(2*d1[i]-1,2*d2[i])
pair<vi, vi> manacher(const string &s) {
    // result: d1/d2 radii for odd/even palindromes centered at i.
    int n = sz(s);
    vi d1(n), d2(n);
    for (int i = 0, l = 0, r = -1; i < n; i++) {
        int k = (i > r) ? 1 : min(d1[l + r - i], r - i + 1);
        while (i - k >= 0 && i + k < n && s[i - k] == s[i + k]) k++;
        d1[i] = k--;
        if (i + k > r) l = i - k, r = i + k;
    }
    for (int i = 0, l = 0, r = -1; i < n; i++) {
        int k = (i > r) ? 0 : min(d2[l + r - i + 1], r - i + 1);
        while (i - k - 1 >= 0 && i + k < n && s[i - k - 1] == s[i + k]) k++;
        d2[i] = k--;
        if (i + k > r) l = i - k - 1, r = i + k;
    }
    return {d1, d2};
}
