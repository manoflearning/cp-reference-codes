#include "../common/common.hpp"

// what: rng helper for reproducible randoms and shuffle.
// time: O(1) per call; memory: O(1)
// constraint: uses mt19937_64.
// usage: rng rd(2); ll x = rd.ll_range(l, r); rd.shuf(v);
struct rng {
    mt19937_64 eng;

    rng(ull seed = (ull)chrono::steady_clock::now().time_since_epoch().count()) : eng(seed) {}

    ll ll_range(ll l, ll r) {
        // edge: l <= r
        uniform_int_distribution<ll> dis(l, r);
        return dis(eng);
    }

    int int_range(int l, int r) {
        uniform_int_distribution<int> dis(l, r);
        return dis(eng);
    }

    template <class T>
    void shuf(vector<T> &v) {
        shuffle(all(v), eng);
    }
};
