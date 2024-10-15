// 1. SCC (Kosaraju's Algorithm)
// INPUT: Given a directed graph.
// OUTPUT: Decompose this graph into SCCs and print them in lexicographical order.
// TIME COMPLEXITY: O(V + E)

// BOJ 2150 AC Code
// https://www.acmicpc.net/problem/2150

#include <bits/stdc++.h>
using namespace std;
#define sz(x) (int)(x).size()

const int MAXV = 10101;

int n, m;
vector<int> adj[MAXV], radj[MAXV];
int in[MAXV], out[MAXV], num, p[2 * MAXV];
int vi[MAXV], cnt;
vector<vector<int>> scc;

void input() {
  cin >> n >> m;
  for (int i = 0; i < m; i++) {
    int u, v;
    cin >> u >> v;
    adj[u].push_back(v);
    radj[v].push_back(u);
  }
}

void dfs(int v) {
  in[v] = ++num;
  for (auto &i : radj[v]) {
    if (!in[i]) dfs(i);
  }
  out[v] = ++num;
  p[num] = v;
}

void flood(int v) {
  scc[cnt].push_back(v);
  vi[v] = cnt;
  for (auto &i : adj[v]) {
    if (!vi[i]) flood(i);
  }
}

void kosaraju() {
  for (int v = 1; v <= n; v++) {
    if (!in[v]) dfs(v);
  }
  for (int v = 2 * n; v >= 1; v--) {
    if (!p[v]) continue;
    if (vi[p[v]]) continue;
    cnt++;
    scc.resize(cnt + 1);
    flood(p[v]);
  }
}

void print() {
  for (auto &i : scc)
    sort(i.begin(), i.end());
  sort(scc.begin(), scc.end());
  cout << sz(scc) - 1 << '\n';
  for (int i = 1; i < sz(scc); i++) {
    auto &arr = scc[i];
    for (auto &j : arr) cout << j << ' ';
    cout << -1 << '\n';
  }
}

int main() {
  cin.tie(NULL), cout.tie(NULL);
  ios_base::sync_with_stdio(false);

  input();
  kosaraju();
  print();
}

// 2. SCC (Tarjan's strongly connected components algorithm)
// INPUT: Given a directed graph.
// OUTPUT: Decompose this graph into SCCs and print them in lexicographical order.
// TIME COMPLEXITY: O(V + E)

// BOJ 2150 AC Code
// https://www.acmicpc.net/problem/2150

#include <bits/stdc++.h>
using namespace std;
#define sz(x) (int)(x).size()

const int MAXV = 101010;

int n, m, label[MAXV], labelCnt;
int SCCnum[MAXV], SCCcnt, finished[MAXV];
vector<int> adj[MAXV];
stack<int> stk;
vector<vector<int>> SCC;

void input() {
  cin >> n >> m;
  for (int i = 0; i < m; i++) {
    int u, v;
    cin >> u >> v;
    adj[u].push_back(v);
  }
}

int dfs(int v) {
  label[v] = labelCnt++;
  stk.push(v);
  int ret = label[v];
  for (int next : adj[v]) {
    // Unvisited node.
    if (label[next] == -1) ret = min(ret, dfs(next));
    // Visited but not yet classified as SCC. In other words, edge { v, next } is back edge.
    else if (!finished[next]) ret = min(ret, label[next]);
  }
  // If there is no edge to the ancestor node among itself and its descendants, find scc.
  if (ret == label[v]) {
    vector<int> vSCC;
    while (1) {
      int t = stk.top();
      stk.pop();
      vSCC.push_back(t);
      SCCnum[t] = SCCcnt;
      finished[t] = 1;
      if (t == v) break;
    }
    SCC.push_back(vSCC);
    SCCcnt++;
  }
  return ret;
}

void getSCC() {
  memset(label, -1, sizeof(label));
  for (int v = 1; v <= n; v++)
    if (label[v] == -1) dfs(v);
}

void print() {
  for (auto &i : SCC)
    sort(i.begin(), i.end());
  sort(SCC.begin(), SCC.end());
  cout << sz(SCC) << '\n';
  for (int i = 0; i < sz(SCC); i++) {
    auto &arr = SCC[i];
    for (auto &j : arr) cout << j << ' ';
    cout << -1 << '\n';
  }
}

int main() {
  cin.tie(NULL), cout.tie(NULL);
  ios_base::sync_with_stdio(false);

  input();
  getSCC();
  print();
}

// 3. 2-SAT
// INPUT: A 2-CNF is given. 2-CNF is a boolean expression in the form (x ∨ y) ∧ (￢ y ∨ z) ∧ (x ∨ ￢ z) ∧ (z ∨ y).
// OUTPUT: Determine whether there exists a case where a given 2-CNF expression can be true. (2-Satisfiability Problem)
// TIME COMPLEXITY: O(n + m) = O(n) (m = 2n)

// BOJ 11281 AC Code
// https://www.acmicpc.net/problem/11281

#include <bits/stdc++.h>
using namespace std;
#define pii pair<int, int>
#define fr first
#define sc second

const int MAXV = 20202;

int n, m;
int dfsn[MAXV], dCnt, sNum[MAXV], sCnt;
int finished[MAXV];
vector<int> adj[MAXV];
stack<int> stk;
pii p[MAXV];
int ans[MAXV / 2];

inline int inv(int x) {
  // negative number -a indicates ¬a.
  return (x > 0) ? 2 * (x - 1) : 2 * (-x - 1) + 1;
}

void twoCnf(int a, int b) {
  // (a ∨ b) iff (¬a → b) iff (¬b → a)
  adj[inv(-a)].push_back(inv(b));
  adj[inv(-b)].push_back(inv(a));
}

void input() {
  cin >> n >> m;
  for (int i = 0; i < m; i++) {
    int a, b;
    cin >> a >> b;
    twoCnf(a, b);
  }
}

int dfs(int now) {
  int ret = dfsn[now] = ++dCnt;
  stk.push(now);
  for (int next : adj[now]) {
    if (dfsn[next] == -1) ret = min(ret, dfs(next));
    else if (!finished[next]) ret = min(ret, dfsn[next]);
  }
  if (ret >= dfsn[now]) {
    while (1) {
      int t = stk.top();
      stk.pop();
      sNum[t] = sCnt;
      finished[t] = 1;
      if (t == now) break;
    }
    sCnt++;
  }
  return ret;
}

int isSatisfiable() {
  // determining satisfiability
  int isS = 1;
  for (int v = 0; v < 2 * n; v += 2) {
    // if x and ¬x is in same scc, then the proposition is not satisfiable
    if (sNum[v] == sNum[v + 1]) {
      isS = 0;
      break;
    }
  }
  return isS;
}

void findValueOfEachVariable() {
  // order of scc is the reverse of the topological sort
  for (int v = 0; v < 2 * n; v++) {
    p[v] = {sNum[v], v};
  }
  sort(p, p + 2 * n);
  // determining true/false of each variable
  for (int i = 2 * n - 1; i >= 0; i--) {
    int v = p[i].sc;
    if (ans[v / 2 + 1] == -1)
      ans[v / 2 + 1] = (v & 1) ? 1 : 0;
  }
  for (int v = 1; v <= n; v++)
    cout << ans[v] << ' ';
}

int main() {
  cin.tie(NULL), cout.tie(NULL);
  ios_base::sync_with_stdio(false);

  memset(dfsn, -1, sizeof(dfsn));
  memset(ans, -1, sizeof(ans));

  input();

  // finding scc
  for (int v = 0; v < 2 * n; v++)
    if (dfsn[v] == -1) dfs(v);

  if (isSatisfiable()) {
    cout << 1 << '\n';
    findValueOfEachVariable();
  } else cout << 0;
}