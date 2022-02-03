#include <iostream>
using namespace std;

const int MAXV = 5 * 1e4;

int N, adj[MAXV][MAXV];

void floyd() {
	for (int i = 0; i < N; i++) adj[i][i] = 0;

	for (int k = 0; k < N; k++) {
		for (int u = 0; u < N; u++) {
			for (int v = 0; v < N; v++) {
				adj[u][v] = min(adj[u][v], adj[u][k] + adj[k][v]);
			}
		}
	}
}
