#include <bits/stdc++.h>
using namespace std;
#define ll long long

const int MAXN = 101010;

int vi[MAXN], dist[MAXN];
vector<int> adj[MAXN];

// DFS
void dfs(int v) {
    vi[v] = 1;
    for (auto& u : adj[v]) {
        if (!vi[u]) dfs(u);
    }
}

// BFS
void bfs(int st) {
    memset(dist, -1, sizeof(dist));

    queue<int> q;

    q.push(st);
    dist[st] = 0;

    while (!q.empty()) {
        int v = q.front();
        q.pop();

        for (auto& u : adj[v]) {
            if (dist[u] != -1) continue;
            dist[u] = dist[v] + 1;
            q.push(u);
        }
    }
}

int main() {
	cin.tie(NULL); cout.tie(NULL);
	ios_base::sync_with_stdio(false);
	
	return 0;
}