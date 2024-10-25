struct UF {
  vector<int> uf;
  void build(int N) {
    uf.clear();
    uf.resize(N + 1, -1);
  }
  int find(int v) {
    if (uf[v] < 0) return v;
    return uf[v] = find(uf[v]);
  }
  void merge(int u, int v) {
    int U = find(u), V = find(v);
    if (U == V) return;
    uf[U] += uf[V];
    uf[V] = U;
  }
} uf;