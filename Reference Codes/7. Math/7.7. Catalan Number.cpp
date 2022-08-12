// BOJ 9343 AC Code
// https://www.acmicpc.net/problem/9343
#include <bits/stdc++.h>
using namespace std;
#define ll long long

const int MOD = 1e9 + 7;
const int MAXN = 2020202;

ll fac[MAXN], inv[MAXN], facInv[MAXN];

ll catalanNumber(int n) { // Cn = 2nCn / (n + 1) = (2n)! / (n!(n + 1)!)
    return fac[2 * n] * facInv[n] % MOD * facInv[n + 1] % MOD;
}

int main() {
    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    // Preprocessing in O(N)
    fac[0] = fac[1] = inv[1] = 1;
    facInv[0] = facInv[1] = 1;
    for (int i = 2; i < MAXN; i++) {
        fac[i] = i * fac[i - 1] % MOD;

        inv[i] = -(MOD / i) * inv[MOD % i] % MOD;
        if (inv[i] < 0) inv[i] += MOD;
        facInv[i] = facInv[i - 1] * inv[i] % MOD;
    }

    // Answer each query in O(1)
    int q; cin >> q;
    while (q--) {
        int n; cin >> n;
        cout << catalanNumber(n) << '\n';
    }

    return 0;
}