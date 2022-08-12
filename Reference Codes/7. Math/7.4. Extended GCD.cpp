// BOJ 14565 AC Code
// https://www.acmicpc.net/problem/14565
#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define pll pair<ll, ll>
#define fr first
#define sc second

// Bézout's identity
// Let a and b be integers with greatest common divisor d.
// Then there exist integers x and y such that ax + by = d.
// Moreover, the integers of the form az + bt are exactly the multiples of d.

// If the integers x1 and y1 satisfy a * x1 + b * y1 = d,
// x2 := x1 + k * b / gcd(a, b) and
// y2 := y1 - k * a / gcd(a, b) also satisfy a * x2 + b * y2 = d for some integer k.

pair<pll, ll> egcd(ll a, ll b) { // time complexity: O(max(loga, logb))
    ll s = 0, olds = 1;
    ll t = 1, oldt = 0;
    ll r = b, oldr = a;

    while (r != 0) {
        ll q = oldr / r;
        ll tmp = oldr - q * r;
        oldr = r, r = tmp;
        tmp = olds - q * s;
        olds = s, s = tmp;
        tmp = oldt - q * t;
        oldt = t, t = tmp;
    }

    // The integers x and y are called Bézout coefficients for (a, b)
    // Bézout coefficients: (olds, oldt)
    // greatest common divisor: oldr
    // quotients by the gcd: (t, s)
    
    return { { olds, oldt }, oldr };
}

ll modInv(ll a, ll p) { // Find x such that ax = 1 (mod p).
    pair<pll, ll> res = egcd(a, p);
    // Modular inverse exists iff gcd(a, p) = 1.
    if (res.sc == 1) return (res.fr.fr + p) % p;
    else return -1;
}

int main() {
    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    ll N, A;
    cin >> N >> A;

    cout << N - A << ' ' << modInv(A, N);

    return 0;
}