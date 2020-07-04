#include <iostream>
#include <vector>
using namespace std;

const int MAXV = 5 * 1e4;

int N, adj[MAXV + 5][MAXV + 5];
vector<int> euler_circult;

void DFS(int now) {
	//인접행렬
	for(int next = 1; next <= N; next++)
		if (adj[now][next]) {
			adj[now][next]--;
			adj[next][now]--;
			DFS(next);
		}
	//경로의 역순으로 배열이 구성된다.
	euler_circult.push_back(now);
}
