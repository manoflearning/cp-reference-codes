// BOJ 1786 TLE Code
// https://www.acmicpc.net/problem/1786
// The basic Rabin-Karp Algorithm works on average in O(N + M), but in the worst case it works on O(NM)
#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define sz(x) (int)(x).size()
const int MAX = 1010101;
const int MOD = 1e9 + 7;
string T, P;
ll d = 128, dexp[MAX];
vector<int> ans;
bool match(int s) {
	for (int i = 0; i < sz(P); i++) {
		if (P[i] != T[s + i]) return false;
	}
	return true;
}
void rabinKarp() {
	int len = sz(P);
	ll p = 0, t = 0;
	for (int i = 0; i < len; i++) {
		p = (d * p + P[i]) % MOD;
		t = (d * t + T[i]) % MOD;
	}
	if (p == t && match(0)) ans.push_back(0);
	for (int i = 1; i < sz(T) - len + 1; i++) {
		t = (d * (t - dexp[len - 1] * T[i - 1]) + T[i + len - 1]) % MOD;
		t = (t + MOD) % MOD;
		if (p == t && match(i)) ans.push_back(i);
	}
}
int main() {
	cin.tie(NULL); cout.tie(NULL);
	ios_base::sync_with_stdio(false);
	dexp[0] = 1;
	for (int i = 1; i < MAX; i++)
		dexp[i] = d * dexp[i - 1] % MOD;
	getline(cin, T);
	getline(cin, P);
	rabinKarp();
	cout << sz(ans) << '\n';
	for (int i : ans) cout << i + 1 << ' ';
	return 0;
}