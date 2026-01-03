#include "../0-common/common.hpp"

// what: mt19937_64 quick usage snippet (time-seeded + rand range + shuffle).
// time: O(1) per draw; memory: O(1)
// constraint: uniform_int_distribution is inclusive [l, r].
// constraint: chrono seed isn't cryptographically secure.
// usage: mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
// usage: ll x = uniform_int_distribution<ll>(l, r)(rng); shuffle(all(v), rng);
