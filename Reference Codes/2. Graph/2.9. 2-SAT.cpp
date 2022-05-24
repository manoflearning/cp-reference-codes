#include <iostream>
#include <vector>
#include <cmath>
#include <cstring>
#include <stack>
#include <algorithm>
using namespace std;

const int MAXV = 2020;

int dfsn[MAXV], dCnt, sNum[MAXV], sCnt;
bool finished[MAXV];
vector<int> adj[MAXV];
stack<int> stk;

inline int trans(int x) {
	return (x > 0) ? 2 * (x - 1) : 2 * (-x - 1) + 1;
}

int dfs(int now) {
	int ret = dfsn[now] = ++dCnt;

	stk.push(now);

	for (int next : adj[now]) {
		if (dfsn[next] == -1) ret = min(ret, dfs(next));
		else if (!finished[next]) ret = min(ret, dfsn[next]);
	}

	if (ret >= dfsn[now]) {
		while (true) {
			int t = stk.top();
			stk.pop();

			sNum[t] = sCnt;
			finished[t] = true;
			
			if (t == now) break;
		}
		sCnt++;
	}

	return ret;
}

int main() {
	cin.tie(NULL); cout.tie(NULL);
	ios_base::sync_with_stdio(false);

	memset(dfsn, -1, sizeof(dfsn));

	int n, m;
	cin >> n >> m;

	// graph modeling
	for (int i = 0; i < m; i++) {
		int a, b;
		cin >> a >> b;
		adj[trans(-a)].push_back(trans(b));
		adj[trans(-b)].push_back(trans(a));
	}

	// scc (dfs tree)
	for (int v = 0; v < 2 * n; v++)
		if (dfsn[v] == -1) dfs(v);

	// determining satisfiability 
	int isS = 1;
	for (int v = 0; v < 2 * n; v += 2) {
		// if v and (v + 1) is in same scc, then the proposition is not satisfiable
		if (sNum[v] == sNum[v + 1]) {
			isS = 0;
			break;
		}
	}

	if (isS) cout << 1;
	else cout << 0;

	return 0;
}