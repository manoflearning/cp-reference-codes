// 1. Dijkstra's Algorithm
// TIME COMPLEXITY: O(ElogV)
int n, m, st;
vector<wv> adj[202020];
vector<ll> dist(202020, (ll)1e18);
struct wv {
  ll w;
  int v;
  bool operator<(const wv &rhs) const {
    return w > rhs.w;
  }
};
void dijkstra(int st) {
  priority_queue<wv> pq;
  pq.push({0, st});
  dist[st] = 0;
  while (!pq.empty()) {
    auto [w, v] = pq.top();
    pq.pop();
    if (w > dist[v]) continue;
    for (auto &i : adj[v]) {
      if (dist[i.v] > w + i.w) {
        dist[i.v] = w + i.w;
        pq.push({w + i.w, i.v});
      }
    }
  }
}

// 2. Bellman-Ford Algorithm
// INPUT: Given a directed graph with weighted(possibly negative) edges and no negative cycles. Given a starting vertex.
// OUTPUT: Outputs the shortest distance from the starting vertex to all vertices.
// TIME COMPLEXITY: O(VE)
struct wv {
  ll w;
  int v;
};
int n, m;
vector<wv> adj[101010];
vector<ll> upper(101010, (ll)1e18);
int bellmanFord() {
  upper[1] = 0;
  int update = 1;
  for (int i = 0; i <= n; i++) {
    update = 0;
    for (int now = 1; now <= n; now++) {
      if (upper[now] == INF) continue;
      for (wv e : adj[now]) {
        int next = e.v;
        if (upper[next] > upper[now] + e.w) {
          upper[next] = upper[now] + e.w;
          update = 1;
        }
      }
    }
    if (!update) break;
  }
  return !update; // Returns false <=> The graph has a negative cycle.
}

// 3. Floyd-Warshall Algorithm
// INPUT: Given a directed graph with weighted(possibly negative) edges and no negative cycles.
// OUTPUT: Outputs the shortest distance from all vertices to all vertices.
// TIME COMPLEXITY: O(V^3)
int n, m;
ll adj[1010][1010];
void floyd() {
  for (int i = 0; i < 1010; i++) {
    for (int j = 0; j < 1010; j++) {
      adj[i][j] = (ll)1e18;
    }
  }
  for (int i = 1; i <= n; i++) adj[i][i] = 0;
  for (int k = 1; k <= n; k++) {
    for (int u = 1; u <= n; u++) {
      for (int v = 1; v <= n; v++) {
        adj[u][v] = min(adj[u][v], adj[u][k] + adj[k][v]);
      }
    }
  }
}