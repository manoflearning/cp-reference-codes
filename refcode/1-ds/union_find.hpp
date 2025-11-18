#include "../common/common.hpp"
namespace refcode {
struct UF {
  vector<int> uf;
  void build(int n) {
    uf.clear();
    uf.resize(n + 1, -1);
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
};
} // namespace refcode