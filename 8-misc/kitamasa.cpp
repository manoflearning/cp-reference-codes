typedef vector<ll> poly;
const int MOD = 1999;
const int MAXN = 1010;
int Mod(ll x) {
  return (x %= MOD) < 0 ? x + MOD : x;
}
poly Mul(const poly &a, const poly &b) {
  poly ret(sz(a) + sz(b) - 1);
  for (int i = 0; i < sz(a); i++)
    for (int j = 0; j < sz(b); j++) {
      ret[i + j] = (ret[i + j] + a[i] * b[j]) % MOD;
    }
  return ret;
}
poly Div(const poly &a, const poly &b) {
  poly ret(all(a));
  for (int i = sz(ret) - 1; i >= sz(b) - 1; i--)
    for (int j = 0; j < sz(b); j++) {
      ret[i + j - sz(b) + 1] = Mod(ret[i + j - sz(b) + 1] - ret[i] * b[j]);
    }
  ret.resize(sz(b) - 1);
  return ret;
}
// kitamasa: A_{n} = \sum c_{i}A_{n-i} = \sum d_{i}A_{i}
// given A, c, n, get d, A_{n} in O(K^2 \log N)
ll kitamasa(poly c, poly a, ll n) {
  poly d = {1};      // result
  poly xn = {0, 1};  // shift = x^1, x^2, x^4, ...
  poly f(sz(c) + 1); // f(x) = x^K - \sum c_{i}x^{i}
  f.back() = 1;
  for (int i = 0; i < sz(c); i++) f[i] = Mod(-c[i]);
  while (n) {
    if (n & 1) d = Div(Mul(d, xn), f);
    n >>= 1;
    xn = Div(Mul(xn, xn), f);
  }
  ll ret = 0;
  for (int i = 0; i < sz(a); i++) ret = Mod(ret + a[i] * d[i]);
  return ret;
}
ll power(ll x, ll y) {
  if (y == 0) return 1;
  if (y == 1) return x;
  ll res = power(x, y / 2);
  return res * res % MOD * (y & 1 ? x : 1) % MOD;
}
int n;
ll m;
vector<ll> dp;
int main() {
  cin >> n >> m;
  if (m < n) {
    cout << power(2, m - 1);
    exit(0);
  }
  vector<ll> c(n);
  for (int i = 0; i < n; i++) {
    if (i == 0) c[i] = power(2, n - 1);
    else c[i] = 1;
  }
  dp.resize(n);
  dp[0] = 1;
  for (int i = 1; i < n; i++)
    for (int j = 0; j < i; j++)
      dp[i] = (dp[i] + dp[j]) % MOD;
  cout << kitamasa(c, dp, m);
}