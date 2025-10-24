#include "../common/common.hpp"

// Dinic's Algorithm
// time complexity : O(V^2 * E) (In networks with unit capacities, it runs in O(min(V^{2/3}, E^{1/2}) * E) time)
const int INF = 1e9 + 7;
const int MAXV = 505;
int N, st = 0, en = MAXV + 1;
vector<int> adj[MAXV + 5];
int c[MAXV + 5][MAXV + 5], f[MAXV + 5][MAXV + 5];
int level[MAXV + 5], work[MAXV + 5];
void input() {
  // TODO
}
void bfs() {
  memset(level, -1, sizeof(level));
  level[st] = 0;
  queue<int> q;
  q.push(st);
  while (!q.empty()) {
    int now = q.front();
    q.pop();
    for (int next : adj[now]) {
      if (level[next] == -1 && c[now][next] - f[now][next] > 0) {
        level[next] = level[now] + 1;
        q.push(next);
      }
    }
  }
}
int dfs(int now, int flow) {
  if (now == en) return flow;
  for (int &i = work[now]; i < adj[now].size(); i++) {
    int next = adj[now][i];
    if (level[next] == level[now] + 1 && c[now][next] - f[now][next] > 0) {
      int df = dfs(next, min(c[now][next] - f[now][next], flow));
      if (df > 0) {
        f[now][next] += df;
        f[next][now] -= df;
        return df;
      }
    }
  }
  return 0;
}
int dinic() {
  int ret = 0;
  while (true) {
    bfs();
    if (level[en] == -1) break;
    memset(work, 0, sizeof(work));
    while (true) {
      int flow = dfs(st, INF);
      if (flow == 0) break;
      ret += flow;
    }
  }
  return ret;
}
int main() {
  input();
  int total = dinic();
  cout << total << '\n';
}