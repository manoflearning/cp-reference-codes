// TIME COMPLEXITY: O(n log n)
// - The height of a centroid tree is O(log n).
// - A path between two arbitrary nodes u, v in the original tree traverses l := lca(u, v) in the centroid tree. 
//   We can think of the path (u, v) in the original tree as splitting into paths (u, l) and (l, v).
// - In the original tree, all paths through (v, i) can be separated into paths through v, par(v), par(par(v)), ..., root in the centroid tree.
namespace CD {
const int MAXN = 202020;

vector<int> adj[MAXN], cdchd[MAXN];
int siz[MAXN], cdpar[MAXN];
bool used[MAXN];

int getSize(int now, int prv) {
  siz[now] = 1;
  for (auto i : adj[now]) {
    if (used[i] || prv == i) continue;
    siz[now] += getSize(i, now);
  }
  return siz[now];
}
int getCent(int now, int prv, int mxsiz) {
  for (auto &i : adj[now]) {
    if (used[i] || i == prv) continue;
    if (siz[i] > mxsiz / 2) return getCent(i, now, mxsiz);
  }
  return now;
}
void cd(int now, int prv) {
  int mxsiz = getSize(now, prv);
  int cent = getCent(now, prv, mxsiz);
  cdpar[cent] = prv;
  cdchd[prv].push_back(cent);
  used[cent] = 1;
  for (auto i : adj[cent])
    if (!used[i]) cd(i, cent);
}
} // namespace CD