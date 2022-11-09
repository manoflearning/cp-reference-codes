#include <bits/stdc++.h>
using namespace std;
#define ll long long
const int MAX = 202020;
// Union find
vector<int> p(MAX, -1);
int find(int x) {
	if (p[x] < 0) return x;
	return p[x] = find(p[x]);
}
void merge(int a, int b) {
	int A = find(a), B = find(b);
	if (A == B) return;
	p[A] += p[B];
	p[B] = A;
}
// Kruskal's algorithm
struct wv {
	ll w; int v;
};
struct wuv {
	ll w; int u, v;
	bool operator<(const wuv& rhs) const {
		return w < rhs.w;
	}
};
int n, m;
vector<wuv> a;
vector<wv> adj[MAX];
void input() {
	cin >> n >> m;
	a.resize(m);
	for (auto& i : a) 
		cin >> i.u >> i.v >> i.w;
}
void makingMST() {
	sort(a.begin(), a.end());
	for (auto& i : a) {
		if (find(i.u) == find(i.v)) continue;
		merge(i.u, i.v);
		adj[i.u].push_back({ i.w, i.v });
		adj[i.v].push_back({ i.w, i.u });
	}
}
int main() {
	cin.tie(NULL); cout.tie(NULL);
	ios_base::sync_with_stdio(false);	
	input();
	makingMST();
	return 0;
}