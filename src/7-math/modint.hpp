#pragma once

#include "num.hpp"

// what: modular integer with compile-time modulus and safe arithmetic ops.
// time: O(1) per op; memory: O(1)
// constraint: inv() exists iff gcd(v, MOD) = 1.
// usage: using mint=modint<998244353>; mint a=3; a+=4; auto b=a.inv();
template <ll MOD_>
struct modint {
    static constexpr ll MOD = MOD_;
    ll v;

    static ll norm(ll x) {
        // goal: normalize x into [0, MOD).
        x %= MOD;
        if (x < 0) x += MOD;
        return x;
    }
    static ll mul(ll a, ll b) { return (ll)((__int128)a * b % MOD); }
    modint(ll x = 0) : v(norm(x)) {}
    static ll mod() { return MOD; }
    modint &operator+=(const modint &o) {
        v += o.v;
        if (v >= MOD) v -= MOD;
        return *this;
    }
    modint &operator-=(const modint &o) {
        v -= o.v;
        if (v < 0) v += MOD;
        return *this;
    }
    modint &operator*=(const modint &o) {
        v = mul(v, o.v);
        return *this;
    }
    modint &operator/=(const modint &o) { return (*this) *= o.inv(); }
    modint operator-() const { return modint(v ? MOD - v : 0); }
    friend modint operator+(modint a, const modint &b) { return a += b; }
    friend modint operator-(modint a, const modint &b) { return a -= b; }
    friend modint operator*(modint a, const modint &b) { return a *= b; }
    friend modint operator/(modint a, const modint &b) { return a /= b; }

    bool operator==(const modint &o) const { return v == o.v; }
    bool operator!=(const modint &o) const { return v != o.v; }
    modint pow(ll e) const { return pow_mod(v, e, MOD); }
    modint inv() const { return euclid::inv_mod(v, MOD); }
    explicit operator ll() const { return v; }
    friend ostream &operator<<(ostream &os, const modint &x) { return os << x.v; }
    friend istream &operator>>(istream &is, modint &x) {
        ll t;
        is >> t;
        x = modint(t);
        return is;
    }
};

// what: modular integer with runtime modulus (set once per ID).
// time: O(1) per op; memory: O(1)
// constraint: call set_mod() before use; inv() exists iff gcd(v, mod) = 1.
// usage: using dm=dyn_modint<0>; dm::set_mod(1'000'000'007); dm x=5;
template <int ID>
struct dyn_modint {
    inline static ll mod_ = 1;
    ll v;

    static ll norm(ll x) {
        // goal: normalize x into [0, mod_).
        x %= mod_;
        if (x < 0) x += mod_;
        return x;
    }
    static ll mul(ll a, ll b) { return (ll)((__int128)a * b % mod_); }
    dyn_modint(ll x = 0) : v(norm(x)) {}
    static void set_mod(ll m) { mod_ = m; }
    static ll mod() { return mod_; }
    dyn_modint &operator+=(const dyn_modint &o) {
        v += o.v;
        if (v >= mod_) v -= mod_;
        return *this;
    }
    dyn_modint &operator-=(const dyn_modint &o) {
        v -= o.v;
        if (v < 0) v += mod_;
        return *this;
    }
    dyn_modint &operator*=(const dyn_modint &o) {
        v = mul(v, o.v);
        return *this;
    }
    dyn_modint &operator/=(const dyn_modint &o) { return (*this) *= o.inv(); }
    dyn_modint operator-() const { return dyn_modint(v ? mod_ - v : 0); }
    friend dyn_modint operator+(dyn_modint a, const dyn_modint &b) { return a += b; }
    friend dyn_modint operator-(dyn_modint a, const dyn_modint &b) { return a -= b; }
    friend dyn_modint operator*(dyn_modint a, const dyn_modint &b) { return a *= b; }
    friend dyn_modint operator/(dyn_modint a, const dyn_modint &b) { return a /= b; }

    bool operator==(const dyn_modint &o) const { return v == o.v; }
    bool operator!=(const dyn_modint &o) const { return v != o.v; }
    dyn_modint pow(ll e) const { return pow_mod(v, e, mod_); }
    dyn_modint inv() const { return euclid::inv_mod(v, mod_); }
    explicit operator ll() const { return v; }
    friend ostream &operator<<(ostream &os, const dyn_modint &x) { return os << x.v; }
    friend istream &operator>>(istream &is, dyn_modint &x) {
        ll t;
        is >> t;
        x = dyn_modint(t);
        return is;
    }
};
