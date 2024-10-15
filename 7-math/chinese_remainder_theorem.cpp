// INPUT: Given 4 integers, M, N, p, q. (1 <= M, 1 <= N, 0 <= p < M, 0 <= q < N)
// OUTPUT: Solve a system of linear congruence, x = p (mod M), x = q (mod N).
// TIME COMPLEXITY: O(log(max(M, N)))
// BOJ 6064 AC Code
// https://www.acmicpc.net/problem/6064
#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define pll pair<ll, ll>
#define fr first
#define sc second

ll gcd(ll x, ll y) {
	if (!y) return x;
	return gcd(y, x % y);
}
ll minv(ll x, ll y) {
	if (x == 0 && y == 1) return 0;
	if (x == 1) return 1;
	return y - minv(y % x, x) * y / x;
}

// x = U.fr (mod U.sc)
// x = V.fr (mod V.sc)
// returns solutions as x = ret.fr (mod ret.sc)
// if no solution, returns { -1, -1 }
pll crt(pll U, pll V) {
	if (U.sc == -1 || V.sc == -1) return { -1, -1 };
	if (U.sc == 1) return V;
	if (V.sc == 1) return U;
	ll g = gcd(U.sc, V.sc);
	ll l = U.sc * V.sc / g;
	// (U and V have a solution) iff (U.fr = U.sc (mod gcd(U.sc,V.sc)))
	// also the solution is unique in the range [0, lcm(U.sc,V.sc)).
	if ((V.fr - U.fr) % g) return { -1, -1 };

	ll u = U.sc / g, v = V.sc / g;
	ll mul = (V.fr - U.fr) / g;
	mul = mul * minv(u % v, v) % v;
	
	pll ret = { mul * U.sc + U.fr, l };
	ret.fr %= ret.sc, ret.fr = (ret.fr + ret.sc) % ret.sc;
	return ret;
}
pll solvingSystemOfLinearCongruence(const vector<pll>& a) {
	if (a.size() == 1) return a[0];
	pll ret = crt(a[0], a[1]);
	for (int i = 2; i < a.size(); i++) ret = crt(ret, a[i]);
	return ret;
}

int main() {
	cin.tie(NULL); cout.tie(NULL);
	ios_base::sync_with_stdio(false);

	int tc; cin >> tc;
	while (tc--) {
		ll M, N, p, q;
		cin >> M >> N >> p >> q;
		p--, q--; // from the given input, 1 <= p <= M, 1 <= q <= N
		vector<pll> cg;
		cg.push_back({ p, M });
		cg.push_back({ q, N });
		pll ans = solvingSystemOfLinearCongruence(cg);
		cout << (ans.fr == -1 ? ans.fr : ans.fr + 1) << '\n';
	}
}