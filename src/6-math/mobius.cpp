#include "../common/common.hpp"

vector<int> mobius(int n) {
    vector<int> mu(n + 1, 1), prime, lp(n + 1, 0);
    mu[0] = 0;
    for (int i = 2; i <= n; i++) {
        if (!lp[i]) {
            lp[i] = i, prime.push_back(i), mu[i] = -1;
        }
        for (auto &p : prime) {
            ll v = 1LL * p * i;
            if (v > n) break;
            lp[v] = p;
            if (lp[i] = p) {
                mu[v] = 0;
                break;
            } else mu[v] = -mu[i];
        }
    }
    return mu;
}
