#include "../common/common.hpp"

// what: normalized rational type with exact arithmetic and comparisons.
// time: O(log max(|n|,|d|)) per op; memory: O(1)
// constraint: denominator != 0; results must fit in 64-bit.
// usage: fraction a(1, 3), b(2, 5); fraction c = a + b;
struct fraction {
    ll n, d;

    fraction(ll n_ = 0, ll d_ = 1) { set(n_, d_); }

    static ll gcd_ll(ll a, ll b) {
        if (a < 0) a = -a;
        if (b < 0) b = -b;
        while (b) {
            ll t = a % b;
            a = b;
            b = t;
        }
        return a;
    }

    void set(ll n_, ll d_) {
        // goal: normalize sign + reduce
        n = n_;
        d = d_;
        norm();
    }

    void norm() {
        if (d < 0) n = -n, d = -d;
        ll g = gcd_ll(n, d);
        if (g) n /= g, d /= g;
    }

    bool operator==(const fraction &rhs) const { return n == rhs.n && d == rhs.d; }
    bool operator!=(const fraction &rhs) const { return !(*this == rhs); }
    bool operator<(const fraction &rhs) const {
        return (__int128)n * rhs.d < (__int128)rhs.n * d;
    }
    bool operator>(const fraction &rhs) const { return rhs < *this; }
    bool operator<=(const fraction &rhs) const { return !(rhs < *this); }
    bool operator>=(const fraction &rhs) const { return !(*this < rhs); }

    fraction operator+(const fraction &rhs) const {
        fraction ret;
        ret.n = n * rhs.d + rhs.n * d;
        ret.d = d * rhs.d;
        ret.norm();
        return ret;
    }
    fraction operator-(const fraction &rhs) const {
        fraction ret;
        ret.n = n * rhs.d - rhs.n * d;
        ret.d = d * rhs.d;
        ret.norm();
        return ret;
    }
    fraction operator*(const fraction &rhs) const {
        fraction ret;
        ret.n = n * rhs.n;
        ret.d = d * rhs.d;
        ret.norm();
        return ret;
    }
    fraction operator/(const fraction &rhs) const {
        fraction ret;
        ret.n = n * rhs.d;
        ret.d = d * rhs.n;
        ret.norm();
        return ret;
    }
};
