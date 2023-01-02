// INPUT: Given a graph with weights on the edges.
// OUTPUT: Print the minimum cost of mst.
// TIME COMPLEXITY: O(ElogE)

// BOJ 1197 AC Code
// https://www.acmicpc.net/problem/1197

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
struct wv { ll w; int v; };
struct Edge { ll w; int u, v; };

int n, m;
vector<Edge> a;
vector<wv> adj[MAX];

void input() {
	cin >> n >> m;
	a.resize(m);
	for (auto& i : a) 
		cin >> i.u >> i.v >> i.w;
}

ll buildMST() {
	ll ret = 0;
	sort(a.begin(), a.end(), [&](const Edge& lhs, const Edge& rhs) {
		return lhs.w < rhs.w;
	});
	for (auto& i : a) {
		if (find(i.u) == find(i.v)) continue;
		merge(i.u, i.v);
		adj[i.u].push_back({ i.w, i.v });
		adj[i.v].push_back({ i.w, i.u });
		ret += i.w;
	}
	return ret;
}

int main() {
	cin.tie(NULL); cout.tie(NULL);
	ios_base::sync_with_stdio(false);

	input();
	cout << buildMST();
	
	return 0;
}