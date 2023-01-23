#include <bits/stdc++.h>
using namespace std;
const char st = 'a';
const int MAXC = 'z' - 'a' + 1;
struct trie {
	trie* child[MAXC];
	bool term;
	trie() {
		fill(child, child + MAXC, nullptr);
		term = false;
	}
	~trie() {
		for (int i = 0; i < MAXC; i++)
			if (child[i]) delete child[i];
	}
	void insert(const string& s, int key = 0) {
		if (s.size() == key) term = true;
		else {
			int next = s[key] - st;
			if (!child[next]) child[next] = new trie;
			child[next]->insert(s, key + 1);
		}
	}
	bool find(const string& s, int key = 0) {
		if (s.size() == key) return term;
		else {
			int next = s[key] - st;
			if (!child[next]) return false;
			else return child[next]->find(s, key + 1);
		}
	}
};
int main() {
	cin.tie(NULL); cout.tie(NULL);
	ios_base::sync_with_stdio(false);	
	trie* root = new trie;
	int N; cin >> N;
	for (int i = 0; i < N; i++) {
		string s; cin >> s;
		root->insert(s);
	}
	int Q; cin >> Q;
	while (Q--) {
		string s; cin >> s;
		if (root->find(s)) cout << "Is exist.\n";
		else cout << "Is not exist.\n";
	}
	delete root;
	return 0;
}
