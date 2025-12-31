#include "../common/common.hpp"

namespace miller_rabin {
ll mul(ll x, ll y, ll mod) { return (__int128_t)x * y % mod; }
ll ipow(ll x, ll y, ll p) {
    ll ret = 1, piv = x % p;
    while (y) {
        if (y & 1) ret = mul(ret, piv, p);
        piv = mul(piv, piv, p);
        y >>= 1;
    }
    return ret;
}
bool miller_rabin(ll x, ll a) {
    if (x % a == 0) return 0;
    ll d = x - 1;
    while (1) {
        ll tmp = ipow(a, d, x);
        if (d & 1) return (tmp != 1 && tmp != x - 1);
        else if (tmp == x - 1) return 0;
        d >>= 1;
    }
}
bool isprime(ll x) {
    for (auto &i : {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37}) {
        if (x == i) return 1;
        if (x > 40 && miller_rabin(x, i)) return 0;
    }
    if (x <= 40) return 0;
    return 1;
}
}; // namespace miller_rabin
namespace pollard_rho {
ll f(ll x, ll n, ll c) {
    return (c + miller_rabin::mul(x, x, n)) % n;
}
void rec(ll n, vector<ll> &v) {
    if (n == 1) return;
    if (n % 2 == 0) {
        v.push_back(2);
        rec(n / 2, v);
        return;
    }
    if (miller_rabin::isprime(n)) {
        v.push_back(n);
        return;
    }
    ll a, b, c;
    while (1) {
        a = rand() % (n - 2) + 2;
        b = a;
        c = rand() % 20 + 1;
        do {
            a = f(a, n, c);
            b = f(f(b, n, c), n, c);
        } while (gcd(abs(a - b), n) == 1);
        if (a != b) break;
    }
    ll x = gcd(abs(a - b), n);
    rec(x, v);
    rec(n / x, v);
}
vector<ll> factorize(ll n) {
    vector<ll> ret;
    rec(n, ret);
    sort(ret.begin(), ret.end());
    return ret;
}
}; // namespace pollard_rho