#include <bits/stdc++.h>
using namespace std;
#define ll long long

const int MAXN = 101010;

int vi[MAXN];
vector<int> adj[MAXN];

void dfs(int v) {
    vi[v] = 1;
    for (auto& u : adj[v]) {
        if (!vi[u]) dfs(u);
    }
}

int main() {
	cin.tie(NULL); cout.tie(NULL);
	ios_base::sync_with_stdio(false);
	
	return 0;
}