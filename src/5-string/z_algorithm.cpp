#include "../common/common.hpp"

// what: compute prefix match lengths for each position in a string.
// time: O(n); memory: O(n)
// constraint: z[0]=n, 0-indexed string.
// usage: auto z = z_func(s);
vi z_func(const string &s) {
    // result: z[i] = longest prefix length matching s[i..].
    int n = sz(s);
    vi z(n);
    if (!n) return z;
    z[0] = n;
    for (int i = 1, l = 0, r = 0; i < n; i++) {
        if (i <= r) z[i] = min(r - i + 1, z[i - l]);
        while (i + z[i] < n && s[z[i]] == s[i + z[i]]) z[i]++;
        if (i + z[i] - 1 > r) l = i, r = i + z[i] - 1;
    }
    return z;
}
