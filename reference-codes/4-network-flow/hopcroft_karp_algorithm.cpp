// Bipartite Matching Algorithm
// time complexity : O(E * sqrt(V))
#include <bits/stdc++.h>
using namespace std;
const int INF = 1e9 + 7;
const int MAXV = 10101;
int n, A[MAXV], B[MAXV], dist[MAXV];
bool used[MAXV];
vector<int> adj[MAXV];
void input() {
	// TODO
}
void bfs() {
	queue<int> q;
	for (int i = 0; i < n; i++) {
		if (!used[i]) {
			dist[i] = 0;
			q.push(i);
		}
		else dist[i] = INF;
	}
	while (!q.empty()) {
		int a = q.front();
		q.pop();
		for (int b : adj[a]) {
			if (B[b] != -1 && dist[B[b]] == INF) {
				dist[B[b]] = dist[a] + 1;
				q.push(B[b]);
			}
		}
	}
}
bool dfs(int a) {
	for (int b : adj[a]) {
		if (B[b] == -1 || (dist[B[b]] == dist[a] + 1 && dfs(B[b]))) {
			used[a] = true;
			A[a] = b;
			B[b] = a;
			return true;
		}
	}
	return false;
}
int hopcroft() {
	memset(A, -1, sizeof(A));
	memset(B, -1, sizeof(B));
	int ret = 0;
	while (true) {
		bfs();
		int flow = 0;
		for (int i = 0; i < n; i++)
			if (!used[i] && dfs(i)) flow++;
		if (flow == 0) break;
		ret += flow;
	}
	return ret;
}
int main() {
	cin.tie(NULL); cout.tie(NULL);
	ios_base::sync_with_stdio(false);
	input();
	int total = hopcroft();
	cout << total << '\n';
}