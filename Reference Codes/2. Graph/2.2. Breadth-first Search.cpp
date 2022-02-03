#define _USE_MATH_DEFINES
#include <bits/stdc++.h>
#include <cassert>
using namespace std;
#define ll long long
#define pii pair<int, int>
#define pll pair<ll, ll>
#define vi vector<int>
#define vvi vector<vector<int>>
#define vl vector<ll>
#define vvl vector<vector<ll>>

const int INF = 1e9 + 7;
const int MOD = 1e9 + 7;
const int dy[] = { 0, 0, 1, -1 };
const int dx[] = { 1, -1, 0, 0 };

const int MAXN = 1e5 + 5;

int dist[MAXN];
vi adj[MAXN];

void init() {
    memset(dist, -1, sizeof(dist));
}

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
	cin.tie(NULL); cout.tie(NULL);
	ios_base::sync_with_stdio(false);
	
	return 0;
}