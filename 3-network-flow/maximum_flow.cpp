// 1. Maximum Flow
// Edmonds-Karp algorithm
// time complexity : O(V * E^2)
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
  input();
  ll total = maxFlow(1, n);
  cout << total << '\n';
}

// 2. Maximum Flow (Struct Edge)
// Edmonds-Karp algorithm
// time complexity : O(V * E^2)
const int MAXV = 1010;
const int INF = 1e9 + 7;
struct edge {
  int v;
  ll c, f;
  edge *dual; // pointer to reverse edge
  edge() : edge(-1, 0) {}
  edge(int v1, ll c1) : v(v1), c(c1), f(0), dual(nullptr) {}
  ll residual() {
    return c - f;
  }
  void addFlow(int f1) {
    f += f1;
    dual->f -= f1;
  }
};
int n;
vector<edge *> adj[MAXV + 5];
int prv[MAXV + 5];
edge *path[MAXV + 5];
void input() {
  cin >> n;
  for (int i = 0; i < n; i++) {
    int n1, n2, cap;
    cin >> n1 >> n2 >> cap;
    edge *e1 = new edge(n2, cap), *e2 = new edge(n1, 0);
    e1->dual = e2, e2->dual = e1;
    adj[n1].push_back(e1);
    adj[n2].push_back(e2);
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
    for (auto *e : adj[now]) {
      int next = e->v;
      if (prv[next] == -1 && e->residual() > 0) {
        q.push(next);
        prv[next] = now;
        path[next] = e;
      }
    }
  }
}
ll flow(int st, int en) {
  ll block = INF;
  for (int i = en; i != st; i = prv[i]) {
    block = min(block, path[i]->residual());
  }
  for (int i = en; i != st; i = prv[i]) {
    path[i]->addFlow(block);
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
  input();
  ll total = maxFlow(1, n);
  cout << total << '\n';
}