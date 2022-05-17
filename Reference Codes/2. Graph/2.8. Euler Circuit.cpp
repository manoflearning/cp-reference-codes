// Hierholzer's Algorithm
#include <iostream>
#include <vector>
using namespace std;

const int MAXV = 5 * 1e4;

int N, adj[MAXV + 5][MAXV + 5];
vector<int> euler_circult;

void dfs(int now) {
	for(int next = 1; next <= N; next++) {
		if (adj[now][next]) {
			adj[now][next]--;
			adj[next][now]--;
			dfs(next);
		}
	}
	euler_circult.push_back(now);
}