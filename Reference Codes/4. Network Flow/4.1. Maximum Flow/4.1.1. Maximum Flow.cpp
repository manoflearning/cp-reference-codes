// Edmonds-Karp algorithm
// time complexity : O(V * E^2)
#include <bits/stdc++.h>
using namespace std;
#define ll long long
const int MAXV = 1010;
const int INF = 1e9 + 7; 
int n;
ll c[MAXV][MAXV], f[MAXV][MAXV];
vector<int> adj[MAXV];
int prv[MAXV];
void input() {
    cin >> n;
    for (int i = 0; i < n; i++) {
        int u, v, cap;
        cin >> u >> v >> cap;
        c[u][v] += cap;
        adj[u].push_back(v);
        // add reverse edge
        adj[v].push_back(u);
    }
}
void bfs(int st, int en) {
    memset(prv, -1, sizeof(prv));
    queue<int> q;
    q.push(st);
    prv[st] = 0;
    while (!q.empty() && prv[en] == -1) {
        int now = q.front();
        q.pop();
        for (int next : adj[now]) {
            if (prv[next] == -1 && c[now][next] - f[now][next] > 0) {
                q.push(next);
                prv[next] = now;
            }
        }
    }
}
ll flow(int st, int en) {
    ll block = INF;
    for (int i = en; i != st; i = prv[i]) {
        block = min(block, c[prv[i]][i] - f[prv[i]][i]);
    }
    for (int i = en; i != st; i = prv[i]) {
        f[prv[i]][i] += block;
        f[i][prv[i]] -= block;
    }
    return block;
}
ll maxFlow(int st, int en) {
    ll ret = 0;
    while (1) {
        bfs(st, en);
        if (prv[en] == -1) break;
        ret += flow(st, en);
    }
    return ret;
}
int main() {
    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);
    input();
    ll total = maxFlow(1, n);
    cout << total << '\n';
    return 0;
}