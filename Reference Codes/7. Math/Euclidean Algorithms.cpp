// GCD, LCM
ll gcd(ll a, ll b) {
	if (b == 0) return a;
	else return gcd(b, a % b);
}
ll lcm(ll a, ll b) {
	return a * b / gcd(a, b);
}

// Extended GCD

// Bezout's Lemma
// Let a and b be integers with d := gcd(a, b).
// Then there exist integers x and y such that ax + by = d.
// Moreover, the integers of the form ax + by are exactly the multiples of d.
// If the integers x1 and y1 satisfy a * x1 + b * y1 = d,
// x2 := x1 + k * b / gcd(a, b) and
// y2 := y1 - k * a / gcd(a, b) also satisfy a * x2 + b * y2 = d for some integer k.

// Results from Bezout's Lemma
// (1) : gcd(a,b) = d => gcd(a/d, b/d) = 1.
// (2) : gcd(a,b) = 1, a|c, b|c => ab|c.
// (3) : a|bc, gcd(a,b) = 1 => a|c.
// (4) : d|a, d|b <=> d|gcd(a,b)
// (5) : gcd(ab,ac) = |a|gcd(b,c)
// (6) : a|bc <=> (a/gcd(a,b))|c

// Linear Congreunce
// Finding set of x satisfies ax = b (mod n).
// We can think ax = b (mod n) as ax + ny = b.
// Then we need to find all (x, y) that satisfy ax + ny = b.
// ax + ny = b has a solution iff gcd(a,n) | b

// Modular Inverse
// In particular, if gcd(a,n) = 1, then we can find a unique x in (mod n) such that ax = 1 (mod n).
// This is called the modular inverse of a over (mod n), sometimes written a^{-1}.
// Multiplying the modular inverse is equivalent to dividing by a.

// TIME COMPLEXITY: O(log(AB))

// BOJ 14565 AC Code
// https://www.acmicpc.net/problem/14565
#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define pll pair<ll, ll>
pair<pll, ll> egcd(ll a, ll b) { 
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
	// a * olds + b * oldt = d
	// oldr = gcd(a, b)
	return { { olds, oldt }, oldr };
}
ll linearCongruence(ll a, ll b, ll n) { // Find x such that ax = b (mod n).
	pair<pll, ll> res = egcd(a, n);
	// ax + ny = b has a solution iff gcd(a,n) | b.
	if (b % res.second) return -1;
	return (res.first.first + n) % n;
}
ll modInv(ll a, ll p) { // Find x such that ax = 1 (mod p).
	pair<pll, ll> res = egcd(a, p);
	// Modular inverse exists iff gcd(a, p) = 1.
	if (res.second == 1) return (res.first.first + p) % p;
	else return -1;
}
int main() {
	ll N, A;
	cin >> N >> A;
	cout << N - A << ' ' << modInv(A, N);
}