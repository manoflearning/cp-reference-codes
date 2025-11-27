#pragma once
#include "../common/common.hpp"
// 1. Finding Divisors in O(sqrt(x))
// INPUT: Given a natural number x.
// OUTPUT: Find all the divisors of x.
// TIME COMPLEXITY: O(sqrt(x)).
vector<ll> get_div(ll x) {
  vector<ll> ret;
  for (ll i = 1; i * i <= x; i++) {
    if (x % i == 0) {
      ret.push_back(i);
      if (x / i != i) ret.push_back(x / i);
    }
  }
  sort(all(ret));
  return ret;
}
// 2. Finding Prime Factorization in O(sqrt(x))
// INPUT: Given a natural number x.
// OUTPUT: Find the result of the prime factorization of x.
// TIME COMPLEXITY: O(sqrt(x)).
vector<ll> factorize(ll x) {
  vector<ll> ret;
  while (x % 2 == 0)
    x /= 2, ret.push_back(2);
  for (int i = 3; i <= sqrt(x); i += 2) {
    while (x % i == 0)
      x /= i, ret.push_back(i);
  }
  if (x > 1) ret.push_back(x);
  return ret;
}