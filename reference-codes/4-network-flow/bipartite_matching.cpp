// all edges have a capacity of 1
// O(VE)
#include <bits/stdc++.h>
using namespace std;
const int MAXV = 1010;
int n, m, A[MAXV], B[MAXV];
vector<int> adj[MAXV];
bool visited[MAXV];
void input() {
	cin >> n >> m;
	for (int i = 1; i <= n; i++) {
		int cnt; cin >> cnt;
		while (cnt--) {
			int x; cin >> x;
			adj[i].push_back(x);
		}
	}
}
bool dfs(int a) {
	visited[a] = 1;
	for (int b : adj[a]) {
		if (B[b] == -1 || (!visited[B[b]] && dfs(B[b]))) {
			A[a] = b;
			B[b] = a;
			return 1;
		}
	}
	return 0;
}
int bipartiteMatch() {
	memset(A, -1, sizeof(A));
	memset(B, -1, sizeof(B));
	int ret = 0;
	for (int i = 1; i <= n; i++) {
		memset(visited, 0, sizeof(visited));
		if (dfs(i)) ret++;
	}
	return ret;
}
int main() {
	cin.tie(NULL); cout.tie(NULL);
	ios_base::sync_with_stdio(false);
	input();
	int ans = bipartiteMatch();
	cout << ans << '\n';
	return 0;
}