#include "../common/common.hpp"

// what: tiny RNG wrapper with fixed default seed for reproducible tests/shuffles.
// time: O(1) per call; memory: O(1)
// constraint: uses mt19937_64.
// usage: rng rd(2); ll x = rd.ll_range(l, r); rd.shuf(v);
struct rng {
    static constexpr ull DEFAULT_SEED = 712367;
    mt19937_64 eng;

    rng(ull seed = DEFAULT_SEED) : eng(seed) {}

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
