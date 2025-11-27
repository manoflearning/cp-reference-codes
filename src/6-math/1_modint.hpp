#pragma once
#include "../common/common.hpp"
template <int m>
class modint {
  static_assert(m > 0, "Modulus must be positive");

public:
  static constexpr int mod() { return m; }
  constexpr modint(ll y = 0) : x(y >= 0 ? y % m : (y % m + m) % m) {}
  constexpr int val() const { return x; }
  constexpr modint &operator+=(const modint &r) {
    if ((x += r.x) >= m) x -= m;
    return *this;
  }
  constexpr modint &operator-=(const modint &r) {
    if ((x += m - r.x) >= m) x -= m;
    return *this;
  }
  constexpr modint &operator*=(const modint &r) {
    x = static_cast<int>(1LL * x * r.x % m);
    return *this;
  }
  constexpr modint &operator/=(const modint &r) { return *this *= r.inv(); }
  constexpr bool operator==(const modint &r) const { return x == r.x; }
  constexpr modint operator+() const { return *this; }
  constexpr modint operator-() const { return modint{-x}; }
  constexpr friend modint operator+(const modint &l, const modint &r) {
    return modint{l} += r;
  }
  constexpr friend modint operator-(const modint &l, const modint &r) {
    return modint{l} -= r;
  }
  constexpr friend modint operator*(const modint &l, const modint &r) {
    return modint{l} *= r;
  }
  constexpr friend modint operator/(const modint &l, const modint &r) {
    return modint{l} /= r;
  }
  constexpr modint inv() const {
    int a = x, b = m, u = 1, v = 0;
    while (b > 0) {
      int t = a / b;
      swap(a -= t * b, b);
      swap(u -= t * v, v);
    }
    return modint{u};
  }
  constexpr modint pow(ll n) const {
    modint ret(1), mul(x);
    while (n > 0) {
      if (n & 1) ret *= mul;
      mul *= mul;
      n >>= 1;
    }
    return ret;
  }
  friend ostream &operator<<(ostream &os, const modint &r) {
    return os << r.x;
  }
  friend istream &operator>>(istream &is, modint &r) {
    ll t;
    is >> t;
    r = modint{t};
    return is;
  }

private:
  int x;
};
