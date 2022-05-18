// Tarjan's strongly connected components algorithm
#include <iostream>
#include <stack>
#include <vector>
#include <cstring>
#include <algorithm>
using namespace std;

const int MAXV = 101010;

int N, label[MAXV], labelCnt;
int SCCnum[MAXV], SCCcnt;
vector<int> adj[MAXV];
bool finished[MAXV];
stack<int> S;
vector<vector<int>> SCC;

void getSCC() {
	memset(label, -1, sizeof(label));

	for (int v = 0; v < N; v++)
		if (label[v] == -1) dfs(v);
}

int dfs(int v) {
	label[v] = labelCnt++;
	S.push(v);

	int ret = label[v];
	for (int next : adj[v]) {
		// unvisited vertex
		if (label[next] == -1) ret = min(ret, dfs(next));
		// visited but not yet classified as SCC. in other words, edge { v, next } is back edge.
		else if (!finished[next]) ret = min(ret, label[next]);
	}

	if (ret == label[v]) {
		vector<int> vSCC;
		while (1) {
			int t = S.top();
			S.pop();

			vSCC.push_back(t);
			SCCnum[t] = SCCcnt;
			finished[t] = 1;

			if (t == v) break;
		}

		SCC.push_back(vSCC);
		SCCcnt++;
	}

	return ret;
}
