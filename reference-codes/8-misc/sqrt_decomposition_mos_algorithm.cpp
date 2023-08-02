#include <bits/stdc++.h>
using namespace std;
int sq;
struct se {
	int s, e, idx;
	bool operator<(const se& rhs) const {
		if (s / sq != rhs.s / sq) return s / sq < rhs.s / sq;
		return e < rhs.e;
	}
};
// Zigzag Mo's (faster than basic Mo's Algorithm)
/*struct se {
	int s, e, idx;
	bool operator<(const se &rhs) const {
		if(s / sq != rhs.s / sq) return s / sq < rhs.s / sq;
		else return (s / sq) & 1 ? e < rhs.e : e > rhs.e;
	}
};*/
vector<se> q;
vector<int> ans;
void input() {
	// TODO: 1. receive input 2. resize q, ans 3. calculate sq 
}
void add(int idx) {
	// TODO: add value at idx from data structure
}
void del(int idx) {
	// TODO: remove value at idx from data structure
}
int query() {
	// TODO: extract the current answer of the data structure
}
void f() {
	int s = q[0].s, e = q[0].e;
	// TODO: initialize data structure
	ans[q[0].idx] = query();
	for (int i = 1; i < q.size(); i++) {
		while (q[i].s < s) add(--s);
		while (e < q[i].e) add(++e);
		while (s < q[i].s) del(s++);
		while (q[i].e < e) del(e--);
		ans[q[i].idx] = query();
	}
}
int main() {
	cin.tie(NULL); cout.tie(NULL);
	ios_base::sync_with_stdio(false);
	input();
	sort(q.begin(), q.end());
	f();
	for (auto& i : ans) 
		cout << i << '\n';
}