// BOJ 1786 AC Code
// https://www.acmicpc.net/problem/1786
// implementation 1
#include <bits/stdc++.h>
using namespace std;
#define sz(x) (int)(x).size()

vector<int> getpi(const string& P) {
	vector<int> pi(sz(P));
	for (int i = 1, j = 0; i < sz(P); i++) {
		while (j > 0 && P[i] != P[j]) j = pi[j - 1];

		if (P[i] == P[j]) pi[i] = ++j;
	}
	return pi;
}

vector<int> kmp(const string& T, const string& P) {
	vector<int> ret;

	vector<int> pi = getpi(P);

	for (int i = 0, j = 0; i < sz(T); i++) {
		while (j > 0 && T[i] != P[j]) j = pi[j-1];
		if (T[i] == P[j]) {
			if (j == sz(P) - 1) {
				ret.push_back(i - (sz(P) - 1));
				j = pi[j];
			}
			else ++j;
		}
	}

	return ret;
}

int main() {
	cin.tie(NULL); cout.tie(NULL);
	ios_base::sync_with_stdio(false);

	string T, P;
	getline(cin, T);
	getline(cin, P);

	vector<int> ans = kmp(T, P);

	cout << sz(ans) << '\n';
	for (int i : ans)
		cout << i + 1 << '\n';

	return 0;
}

// BOJ 1786 AC Code
// https://www.acmicpc.net/problem/1786
// implementation 2
#include <bits/stdc++.h>
using namespace std;
#define sz(x) (int)(x).size()

vector<int> getpi(const string& P) {
	vector<int> pi(sz(P));

	int begin = 1, matched = 0;
	while (begin + matched < sz(P)) {
		if (P[begin + matched] == P[matched]) {
			matched++;
			pi[begin + matched - 1] = matched;
		}
		else {
			if (matched == 0) begin++;
			else {
				begin += matched - pi[matched - 1];
				matched = pi[matched - 1];
			}
		}
	}

	return pi;
}

vector<int> kmp(const string& T, const string& P) {
	vector<int> ret;

	vector<int> pi = getpi(P);

	int begin = 0, matched = 0;
	while (begin <= sz(T) - sz(P)) {
		if (matched < sz(P) && T[begin + matched] == P[matched]) {
			matched++;
			if (matched == sz(P)) ret.push_back(begin);
		}
		else {
			if (matched == 0) begin++;
			else {
				begin += matched - pi[matched - 1];
				matched = pi[matched - 1];
			}
		}
	}

	return ret;
}

int main() {
	cin.tie(NULL); cout.tie(NULL);
	ios_base::sync_with_stdio(false);

	string T, P;
	getline(cin, T);
	getline(cin, P);

	vector<int> ans = kmp(T, P);

	cout << sz(ans) << '\n';
	for (int i : ans)
		cout << i + 1 << '\n';

	return 0;
}