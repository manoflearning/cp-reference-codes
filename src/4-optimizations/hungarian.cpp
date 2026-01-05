#include "../0-common/common.hpp"

// what: solve rectangular assignment problem (min-cost matching) via Hungarian.
// time: O(n m^2); memory: O(n+m)
// constraint: 1 <= n <= m, 1-indexed cost a[1..n][1..m] (minimization).
// usage: hungarian hu; auto [cost, match_l] = hu.run(n, m, a); // match_l[i]=j
struct hungarian {
    pair<ll, vector<int>> run(int n, int m, const vector<vector<ll>> &a) {
        // result: {min_cost, match_l} with match_l[i]=assigned column.
        const ll INF = (1LL << 62);
        vector<ll> u(n + 1), v(m + 1);
        vector<int> p(m + 1), way(m + 1);
        for (int i = 1; i <= n; i++) {
            p[0] = i;
            int j0 = 0;
            vector<ll> minv(m + 1, INF);
            vector<char> used(m + 1, 0);
            do {
                used[j0] = 1;
                int i0 = p[j0], j1 = 0;
                ll delta = INF;
                for (int j = 1; j <= m; j++) {
                    if (used[j]) continue;
                    ll cur = a[i0][j] - u[i0] - v[j];
                    if (cur < minv[j]) minv[j] = cur, way[j] = j0;
                    if (minv[j] < delta) delta = minv[j], j1 = j;
                }
                for (int j = 0; j <= m; j++) {
                    if (used[j]) {
                        u[p[j]] += delta;
                        v[j] -= delta;
                    } else {
                        minv[j] -= delta;
                    }
                }
                j0 = j1;
            } while (p[j0] != 0);
            do {
                int j1 = way[j0];
                p[j0] = p[j1];
                j0 = j1;
            } while (j0);
        }
        vector<int> match_l(n + 1, 0);
        for (int j = 1; j <= m; j++)
            if (p[j]) match_l[p[j]] = j;
        return {-v[0], match_l};
    }
};
