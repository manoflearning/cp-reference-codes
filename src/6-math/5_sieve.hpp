#pragma once
#include "../common/common.hpp"
// 1. Sieve of Eratosthenes
// TIME COMPLEXITY: O(Nlog(log(N)))
namespace sieve {
constexpr int N = 1010101;
bool is_prime[N];
vector<int> prime(1, 2);
void get_prime() {
  fill(is_prime + 2, is_prime + N, 1);
  for (ll i = 4; i < N; i += 2)
    is_prime[i] = 0;
  for (ll i = 3; i < N; i += 2) {
    if (!is_prime[i]) continue;
    prime.push_back(i);
    for (ll j = i * i; j < N; j += i * 2)
      is_prime[j] = 0;
  }
}
}; // namespace sieve
// 2. Linear Sieve
namespace linear_sieve {
constexpr int N = 5050505;
vector<int> sp(N);
vector<ll> prime;
void linear_sieve() { // Determine prime numbers between 1 and MAXN in O(MAXN)
  for (int i = 2; i < N; i++) {
    if (!sp[i]) {
      prime.push_back(i);
      sp[i] = i;
    }
    for (auto j : prime) {
      if (i * j >= N) break;
      sp[i * j] = j;
      if (i % j == 0) break;
    }
  }
}
vector<int> factorize(int x) { // factorization in O(log x)
  vector<int> ret;
  while (x > 1) {
    ret.push_back(sp[x]);
    x /= sp[x];
  }
  return ret;
}
}; // namespace linear_sieve
