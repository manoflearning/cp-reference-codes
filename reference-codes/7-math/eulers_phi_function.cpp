// INPUT: Given a natural number n.
// OUTPUT: Find the number of natural numbers 1 ≤ k ≤ n such that GCD(n, k) = 1.
// TIME COMPLEXITY: O(sqrt(n))
// BOJ 11689 AC Code
// https://www.acmicpc.net/problem/11689
#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define pll pair<ll, ll>
#define fr first
#define sc second
ll phi(ll x) { // Find phi(x) in O(sqrt(x)).
    vector<pll> p;
    // Factorization in O(sqrt(x)).
    for (ll i = 2; i <= sqrt(x); i++) {
        ll res = 1;
        while (x % i == 0) {
            x /= i, res *= i;
        }
        if (res > 1) p.push_back({ res, i });
    }
    if (x > 1) p.push_back({ x, x });
    // Find phi(x).
    // phi(p^k) = p^{k-1} * (p - 1) for any prime number p.
    // phi(mn) = phi(m) * phi(n) if gcd(m, n) = 1
    ll ret = 1;
    for (auto& i : p) {
        ret *= (i.fr / i.sc) * (i.sc - 1);
    }
    return ret;
}
int main() {
    ll n; cin >> n;
    cout << phi(n);
}