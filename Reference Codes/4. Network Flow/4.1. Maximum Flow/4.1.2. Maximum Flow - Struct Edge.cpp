// Edmonds-Karp algorithm
// time complexity : O(V * E^2)
#include <bits/stdc++.h>
using namespace std;
#define ll long long
const int MAXV = 1010;
const int INF = 1e9 + 7;
struct edge {
	int v;
	ll c, f;
	edge* dual; // pointer to reverse edge
	edge() : edge(-1, 0) {}
	edge(int v1, ll c1) : v(v1), c(c1), f(0), dual(nullptr) {}
	ll residual() {
		return c - f;
	}
	void addFlow(int f1) {
		f += f1;
		dual->f -= f1;
	}
};
int n;
vector<edge*> adj[MAXV + 5];
int prv[MAXV + 5];
edge* path[MAXV + 5];
void input() {
	cin >> n;
	for (int i = 0; i < n; i++) {
		int n1, n2, cap;
		cin >> n1 >> n2 >> cap;
		edge* e1 = new edge(n2, cap), * e2 = new edge(n1, 0);
		e1->dual = e2, e2->dual = e1;
		adj[n1].push_back(e1);
		adj[n2].push_back(e2);
	}
}
void bfs(int st, int en) {
	memset(prv, -1, sizeof(prv));
	queue<int> q;
	q.push(st);
	prv[st] = 0;
	while (!q.empty() && prv[en] == -1) {
		int now = q.front();
		q.pop();
		for (auto* e : adj[now]) {
			int next = e->v;
			if (prv[next] == -1 && e->residual() > 0) {
				q.push(next);
				prv[next] = now;
				path[next] = e;
			}
		}
	}
}
ll flow(int st, int en) {
	ll block = INF;
	for (int i = en; i != st; i = prv[i]) {
		block = min(block, path[i]->residual());
	}
	for (int i = en; i != st; i = prv[i]) {
		path[i]->addFlow(block);
	}
	return block;
}
ll maxFlow(int st, int en) {
	ll ret = 0;
	while (1) {
		bfs(st, en);
		if (prv[en] == -1) break;
		ret += flow(st, en);
	}
	return ret;
}
int main() {
	cin.tie(NULL); cout.tie(NULL);
	ios_base::sync_with_stdio(false);
	input();
	ll total = maxFlow(1, n);
	cout << total << '\n';
	return 0;
}