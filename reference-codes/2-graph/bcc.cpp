// A Biconnected Component (BCC) is a subset of vertices in an undirected graph that satisfies the following conditions:
// (1) If you delete any vertex from a subset, the remaining vertices are connected to each other.
// (2) Adding other vertices to this subset does not satisfy (1). (This is the largest set that satisfies (1))
// TIME COMPLEXITY: O(V + E)

// A vertex at which the graph is divided into two or more components when the vertex is removed is called a 'articulation point'.
// After decomposing the graph into BCCs, vertices belonging to two or more BCCs are articulation point.
// Similarly, a edge at which the graph is divided into two or more components when the edge is removed is called a 'articulation edge'.
// For all tree edges on a dfs spanning tree, if tmp > dfsn[now], the edge { now, next } is a articulation edge.

#include <bits/stdc++.h>
using namespace std;
#define pii pair<int, int>

const int MAXV = 101010;

int n, m;
vector<int> adj[MAXV];
vector<vector<pii>> bcc;
set<int> aPoint;
set<pii> aEdge;

void input() {
	cin >> n >> m;
	for (int i = 0; i < m; i++) {
		int u, v;
		cin >> u >> v;
		adj[u].push_back(v);
		adj[v].push_back(u);
	} 
}

int dfsn[MAXV], dCnt;
stack<pii> stk;
int dfs(int now, int prv) {
	int ret = dfsn[now] = ++dCnt;

	int childCnt = 0;
	for (int next : adj[now]) {
		if (next == prv) continue;

		// If an edge { now, next } has not yet been visited, puts an edge on the stack.
		if (dfsn[now] > dfsn[next]) stk.push({ now, next });
		
		// Back edge
		if (dfsn[next] != -1) ret = min(ret, dfsn[next]);
		// Tree edge
		else {
			childCnt++;
			int tmp = dfs(next, now);
			ret = min(ret, tmp);

			if (prv != -1 && tmp >= dfsn[now]) 
				aPoint.insert(now);
			if (tmp > dfsn[now])
				aEdge.insert({ min(now, next), max(now, next) });

			// If next cannot go to ancestor node of now, find BCC
			if (tmp >= dfsn[now]) {
				vector<pii> nowBCC;
				while (true) {
					pii t = stk.top();
					stk.pop();
					nowBCC.push_back(t);
					if (t == make_pair(now, next)) break;
				}
				bcc.push_back(nowBCC);
			}
		}
	}

	if (prv == -1 && childCnt > 1)
		aPoint.insert(now);
	
	return ret;
}

void getBCC() {
	memset(dfsn, -1, sizeof(dfsn));
	for (int v = 1; v <= n; v++)
		if (dfsn[v] == -1) dfs(v, -1);
}

int main() {
	cin.tie(NULL); cout.tie(NULL);
	ios_base::sync_with_stdio(false);

	input();
	getBCC();
}