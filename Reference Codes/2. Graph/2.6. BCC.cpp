#include <bits/stdc++.h>
using namespace std;
#define pii pair<int, int>
const int MAXV = 101010;
int n, m, dfsn[MAXV + 5], dCnt;
vector<int> adj[MAXV + 5];
stack<pii> stk;
vector<vector<pii>> bcc;
void input() {
	cin >> n >> m;
	for (int i = 0; i < m; i++) {
		int u, v;
		cin >> u >> v;
		adj[u].push_back(v);
		adj[v].push_back(u);
	} 
}
int dfs(int now, int prv) {
	int ret = dfsn[now] = ++dCnt;
	for (int next : adj[now]) {
		if (next == prv) continue;
		// If an edge { now, next } has not yet been visited, it puts an edge on the stack.
		if (dfsn[now] > dfsn[next]) stk.push({ now, next });
		// Back edge
		if (dfsn[next] != -1) ret = min(ret, dfsn[next]);
		// Tree edge
		else {
			int tmp = dfs(next, now);
			ret = min(ret, tmp);
			// if next cannot go to ancestor node of now, find BCC
			if (tmp >= dfsn[now]) {
				vector<pair<int, int>> nowBCC;
				while (true) {
					pair<int, int> t = stk.top();
					stk.pop();
					nowBCC.push_back(t);
					if (t == pair<int, int>(now, next)) break;
				}
				bcc.push_back(nowBCC);
			}
		}
	}
	return ret;
}
void getBCC() {
	memset(dfsn, -1, sizeof(dfsn));
	for (int v = 1; v <= n; v++)
		if (dfsn[v] == -1) dfs(v, 0);
}
int main() {
	cin.tie(NULL); cout.tie(NULL);
	ios_base::sync_with_stdio(false);
	input();
	getBCC();
	return 0;
}