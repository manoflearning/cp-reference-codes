#include <bits/stdc++.h>
using namespace std;
const char st = '0';
const int MAXC = '9' - '0' + 1;
const int MAXN = 100 * 100 * MAXC + 1; 
struct trie {
	int cnt, t[MAXN][MAXC];
	bool term[MAXN];
	void clear() {
		memset(t, 0, sizeof(t));
		memset(term, 0, sizeof(term));
		cnt = 0;
	}
	void insert(string& s) {
		int here = 0;
		for (char& i : s) {
			if (!t[here][i - st]) t[here][i - st] = ++cnt;
			here = t[here][i - st];
		}
		term[here] = true;
	}
	bool find(string& s) {
		int here = 0;
		for (int i = 0; i < s.size(); i++) {
			if (!t[here][s[i] - st]) return false;
			here = t[here][s[i] - st];
			if (i == s.size() - 1 && term[here]) return true;
		}
		return false;
	}
};
trie T;
int main() {
	cin.tie(NULL); cout.tie(NULL);
	ios_base::sync_with_stdio(false);
	int N; cin >> N;
	for (int i = 0; i < N; i++) {
		string s; cin >> s;
		T.insert(s);
	}
	int Q; cin >> Q;
	while (Q--) {
		string s; cin >> s;
		if (T.find(s)) cout << "Is exist.\n";
		else cout << "Is not exist.\n";
	}
	return 0;
}