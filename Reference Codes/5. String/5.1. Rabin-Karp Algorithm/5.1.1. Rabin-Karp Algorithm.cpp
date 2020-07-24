#include <iostream>
#include <string>
#include <vector>
#define ll long long
using namespace std;

const int MAX = 1e6 + 5;
const ll MOD = 1e9 + 7;

string T, P;
ll d = 128, dexp[MAX];
vector<int> ans;

void rabinKarp();
bool match(int s);

int main() {
	cin.tie(NULL); cout.tie(NULL);
	ios_base::sync_with_stdio(false);

	dexp[0] = 1;
	for (int i = 1; i < MAX; i++)
		dexp[i] = d * dexp[i - 1] % MOD;

	getline(cin, T);
	getline(cin, P);

	rabinKarp();

	cout << ans.size() << '\n';
	for (int i : ans) cout << i << ' ';

	return 0;
}

void rabinKarp() {
	int len = P.size();

	ll p = 0, t = 0;
	for (int i = 0; i < len; i++) {
		p = (d * p + P[i]) % MOD;
		t = (d * t + T[i]) % MOD;
	}

	if (p == t && match(0)) ans.push_back(0);

	for (int i = 1; i < T.size() - len + 1; i++) {
		t = (d * (t - dexp[len - 1] * T[i - 1]) + T[i + len - 1]) % MOD;
		t = (t + MOD) % MOD;
		if (p == t && match(i)) ans.push_back(i);
	}
}

bool match(int s) {
	for (int i = 0; i < P.size(); i++) {
		if (P[i] != T[s + i]) return false;
	}
	return true;
}
