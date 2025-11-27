#pragma once
#include "../common/common.hpp"
namespace binom {
// nCr mod p in O(1)
constexpr int MOD = 1e9 + 7;
constexpr int N = 4040404;
ll fac[N], inv[N], facInv[N];
void build() { // You must run build() before you call binom(int n, int r).
  fac[0] = fac[1] = inv[1] = 1;
  facInv[0] = facInv[1] = 1;
  for (int i = 2; i < N; i++) {
    fac[i] = i * fac[i - 1] % MOD;
    inv[i] = -(MOD / i) * inv[MOD % i] % MOD;
    if (inv[i] < 0) inv[i] += MOD;
    facInv[i] = facInv[i - 1] * inv[i] % MOD;
  }
}
ll binom(int n, int r) {
  return fac[n] * facInv[r] % MOD * facInv[n - r] % MOD;
}
}; // namespace binom
