#include "../common/common.hpp"
// TIME COMPLEXITY: O(n m^2)
// PRECONDITION: 1 <= n <= m, a is 1-indexed [1..n][1..m]
constexpr ll INF = 1e18;
ll hungarian(int n, int m, const vector<vector<ll>> &a) {
    vector<ll> u(n + 1), v(m + 1);
    vector<int> p(m + 1), way(m + 1);
    for (int i = 1; i <= n; i++) {
        p[0] = i;
        int j0 = 0;
        vector<ll> minv(m + 1, INF);
        vector<bool> used(m + 1, 0);
        do {
            used[j0] = 1;
            int i0 = p[j0], j1;
            ll delta = INF;
            for (int j = 1; j <= m; j++)
                if (!used[j]) {
                    ll cur = a[i0][j] - u[i0] - v[j];
                    if (cur < minv[j])
                        minv[j] = cur, way[j] = j0;
                    if (minv[j] < delta)
                        delta = minv[j], j1 = j;
                }
            for (int j = 0; j <= m; ++j)
                if (used[j])
                    u[p[j]] += delta, v[j] -= delta;
                else
                    minv[j] -= delta;
            j0 = j1;
        } while (p[j0] != 0);
        do {
            int j1 = way[j0];
            p[j0] = p[j1];
            j0 = j1;
        } while (j0);
    }
    return -v[0];
}