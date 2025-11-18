#include "../common/common.hpp"
mt19937 rng((unsigned)chrono::steady_clock::now().time_since_epoch().count());
uniform_int_distribution<int> dist(0, 100);
auto gen = bind(dist, rng); // usage: int x = gen();
shuffle(v.begin(), v.end(), rng);