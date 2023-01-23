// Depth-first Search

// INPUT: Given a undirected graph.
// OUTPUT: Output a number of connected components.
// TIME COMPLEXITY: O(n + m)

// BOJ 11724 AC Code
// https://www.acmicpc.net/problem/11724

#include <bits/stdc++.h>
using namespace std;
#define ll long long

const int MAXN = 101010;

int n, m, vi[MAXN];
vector<int> adj[MAXN];

void dfs(int v) {
    vi[v] = 1;
    for (auto& u : adj[v]) {
        if (!vi[u]) dfs(u);
    }
}

int main() {
    // input
    cin >> n >> m;
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    // get answer
    int ans = 0;
    for (int v = 1; v <= n; v++) {
        if (!vi[v]) { ans++; dfs(v); }
    }

    cout << ans;
    
    return 0;
}

// Breadth-first Search

// INPUT: Given a undirected graph.
// OUTPUT: Output a number of connected components.
// TIME COMPLEXITY: O(n + m)

// BOJ 11724 AC Code
// https://www.acmicpc.net/problem/11724

#include <bits/stdc++.h>
using namespace std;
#define ll long long

const int MAXN = 101010;

int n, m, dist[MAXN];
vector<int> adj[MAXN];

void bfs(int st) {
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
    // input
    cin >> n >> m;
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    // get answer
    int ans = 0;

    memset(dist, -1, sizeof(dist));
    for (int v = 1; v <= n; v++) {
        if (dist[v] == -1) { ans++; bfs(v); }
    }

    cout << ans;
    
    return 0;
}