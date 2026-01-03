#pragma once
#include "../common/common.hpp"

// what: precompute primality table and prime list with Eratosthenes sieve.
// time: O(n log log n); memory: O(n)
// constraint: n >= 0.
// usage: era_sieve es(n); if(es.is_prime(x)) ...
struct era_sieve {
    int n;
    vector<char> isp;
    vector<int> primes;

    era_sieve(int n_ = 0) {
        if (n_ >= 0) init(n_);
    }

    void init(int n_) {
        // goal: build isp/primes for [0..n]
        n = n_;
        isp.assign(n + 1, 1);
        if (n >= 0) isp[0] = 0;
        if (n >= 1) isp[1] = 0;
        for (int i = 4; i <= n; i += 2) isp[i] = 0;
        for (ll i = 3; i * i <= n; i += 2) {
            if (!isp[i]) continue;
            for (ll j = i * i; j <= n; j += i << 1) isp[j] = 0;
        }
        primes.clear();
        if (n >= 2) primes.pb(2);
        for (int i = 3; i <= n; i += 2)
            if (isp[i]) primes.pb(i);
    }

    bool is_prime(int x) const { return x >= 2 && x <= n && isp[x]; }
};

// what: linear sieve for lp/primes/mu/phi with factorization helpers.
// time: O(n) build; O(log x) factor; memory: O(n)
// constraint: factor(x) requires 1 <= x <= n.
// usage: lin_sieve sv(n); auto fc=sv.factor_cnt(x); int mu=sv.mu[x];
struct lin_sieve {
    int n;
    vector<int> lp, primes, mu, phi;

    lin_sieve(int n_ = 0) {
        if (n_ >= 0) init(n_);
    }

    void init(int n_) {
        // goal: fill lp/primes/mu/phi for [0..n]
        n = n_;
        lp.assign(n + 1, 0);
        primes.clear();
        mu.assign(n + 1, 0);
        phi.assign(n + 1, 0);
        if (n >= 1) mu[1] = 1, phi[1] = 1;
        for (int i = 2; i <= n; i++) {
            if (!lp[i]) {
                lp[i] = i;
                primes.pb(i);
                mu[i] = -1;
                phi[i] = i - 1;
            }
            for (int p : primes) {
                ll v = 1LL * p * i;
                if (v > n) break;
                lp[v] = p;
                if (p == lp[i]) {
                    mu[v] = 0;
                    phi[v] = phi[i] * p;
                    break;
                }
                mu[v] = -mu[i];
                phi[v] = phi[i] * (p - 1);
            }
        }
    }

    bool is_prime(int x) const { return x >= 2 && x <= n && lp[x] == x; }

    vector<int> factor(int x) const {
        // result: prime factors of x (with repetition), in nondecreasing order
        vector<int> ret;
        while (x > 1) {
            int p = lp[x];
            ret.pb(p);
            x /= p;
        }
        return ret;
    }

    vector<pii> factor_cnt(int x) const {
        // result: {{p, e}} s.t. x = prod p^e, increasing p
        vector<pii> ret;
        while (x > 1) {
            int p = lp[x];
            int e = 0;
            while (x % p == 0) x /= p, e++;
            ret.pb({p, e});
        }
        return ret;
    }
};

// what: compute mobius function mu[0..n].
// time: O(n); memory: O(n)
// constraint: n >= 0.
// usage: auto mu = mobius(n); if(mu[x]) ...
inline vector<int> mobius(int n) {
    lin_sieve sv(n);
    return sv.mu;
}

// what: compute Euler's totient (single n or all up to n).
// time: phi(x) O(sqrt x); phi_upto(n) O(n); memory: O(n)
// constraint: phi(x) assumes x >= 0; phi_upto uses lin_sieve.
// usage: ll v=euler_phi::phi(x); auto ph=euler_phi::phi_upto(n);
struct euler_phi {
    static ll phi(ll x) {
        if (x <= 0) return 0;
        ll ret = x;
        for (ll p = 2; p * p <= x; p++) {
            if (x % p) continue;
            // goal: remove prime p from x.
            while (x % p == 0) x /= p;
            ret = ret / p * (p - 1);
        }
        if (x > 1) ret = ret / x * (x - 1);
        return ret;
    }

    static vector<int> phi_upto(int n) {
        lin_sieve sv(n);
        return sv.phi;
    }
};
