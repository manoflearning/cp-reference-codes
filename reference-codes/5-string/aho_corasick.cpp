// BOJ 9250 AC Code
// https://www.acmicpc.net/problem/9250
#include <bits/stdc++.h>
using namespace std;
const char st = 'a';
const int MAXC = 'z' - 'a' + 1;
struct trie {
	trie* child[MAXC];
	trie* fail;
	bool term;
	trie() {
		fill(child, child + MAXC, nullptr);
		fail = nullptr;
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
};
trie* root = new trie;
void getFail() {
	queue<trie*> q;
	q.push(root);
	root->fail = root;
	while (!q.empty()) {
		trie* now = q.front();
		q.pop();
		for (int i = 0; i < MAXC; i++) {
			trie* next = now->child[i];
			if (!next) continue;
			if (now == root) next->fail = root;
			else {
				trie* t = now->fail;
				while (t != root && !t->child[i])
					t = t->fail;
				if (t->child[i]) t = t->child[i];
				next->fail = t;
			}
			if (next->fail->term) next->term = true;
			q.push(next);
		}
	}
}
bool isMatch(const string& s) {
	trie* now = root;
	bool ret = false;
	for (int c = 0; c < s.size(); c++) {
		int next = s[c] - st;
		while (now != root && !now->child[next])
			now = now->fail;
		if (now->child[next])
			now = now->child[next];
		if (now->term) {
			ret = true;
			break;
		}
	}
	return ret;
}
int main() {
	cin.tie(NULL); cout.tie(NULL);
	ios_base::sync_with_stdio(false);
	int N; cin >> N;
	for (int i = 0; i < N; i++) {
		string s; cin >> s;
		root->insert(s);
	}
	getFail();
	int M; cin >> M;
	for (int i = 0; i < M; i++) {
		string s; cin >> s;
		if (isMatch(s)) cout << "YES\n";
		else cout << "NO\n";
	}
	delete root;
	return 0;
}