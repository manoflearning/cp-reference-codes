// BOJ 11401 AC Code
// https://www.acmicpc.net/problem/11401
#include <bits/stdc++.h>
using namespace std;
#define ll long long

const int MOD = 1e9 + 7;

// Fermat’s little theorem
// A / B = A * B^{p - 2} (mod p)
ll modInv(ll x, ll y) { 
    if (y == 0) return 1;
    if (y == 1) return x;

    ll res = modInv(x, y / 2);
    return res * res % MOD * (y & 1 ? x : 1) % MOD;
}

int main() {
    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    ll fac[4040404] = { 1, };
    for (int i = 1; i < 4040404; i++)
        fac[i] = i * fac[i - 1] % MOD;

    int n, r;
    cin >> n >> r;

    // print nCr (mod 1e9+7)
    cout << fac[n] * modInv(fac[r], MOD - 2) % MOD * modInv(fac[n - r], MOD - 2) % MOD;

    return 0;
}