#include "../../src/7-math/nt_sieve.cpp"
#include "../../src/7-math/num.hpp"

// what: tests for era_sieve/lin_sieve/mobius/euler_phi.
// time: random + brute; memory: O(n)
// constraint: fixed seed.
// usage: g++ -std=c++17 test_nt_sieve.cpp && ./a.out

mt19937_64 rng(13);
int rnd_int(int l, int r) {
    uniform_int_distribution<int> dis(l, r);
    return dis(rng);
}

bool is_prime_ref(int x) {
    if (x < 2) return 0;
    for (int i = 2; 1LL * i * i <= x; i++)
        if (x % i == 0) return 0;
    return 1;
}

int mu_ref(int x) {
    if (x == 1) return 1;
    int cnt = 0;
    for (int p = 2; 1LL * p * p <= x; p++) {
        if (x % p) continue;
        int e = 0;
        while (x % p == 0) x /= p, e++;
        if (e > 1) return 0;
        cnt++;
    }
    if (x > 1) cnt++;
    return (cnt & 1) ? -1 : 1;
}

int phi_ref(int x) {
    if (x == 0) return 0;
    int ret = x;
    for (int p = 2; 1LL * p * p <= x; p++) {
        if (x % p) continue;
        while (x % p == 0) x /= p;
        ret = ret / p * (p - 1);
    }
    if (x > 1) ret = ret / x * (x - 1);
    return ret;
}

vector<int> divisors(int x) {
    vector<int> d;
    for (int i = 1; 1LL * i * i <= x; i++) {
        if (x % i) continue;
        d.pb(i);
        if (i * i != x) d.pb(x / i);
    }
    return d;
}

void test_era() {
    int n = 5000;
    era_sieve es(n);
    for (int i = 0; i <= n; i++) assert(es.is_prime(i) == is_prime_ref(i));
    for (int p : es.primes) assert(is_prime_ref(p));
    assert(es.primes.empty() || es.primes[0] == 2);
    for (int i = 1; i < sz(es.primes); i++) assert(es.primes[i - 1] < es.primes[i]);
}

void test_lin() {
    int n = 5000;
    lin_sieve sv(n);
    for (int i = 0; i <= n; i++) assert(sv.is_prime(i) == is_prime_ref(i));
    for (int i = 1; i <= n; i++) {
        assert(sv.mu[i] == mu_ref(i));
        assert(sv.phi[i] == phi_ref(i));
        assert(sv.mu[i] >= -1 && sv.mu[i] <= 1);
        if (i >= 2 && sv.is_prime(i)) {
            assert(sv.mu[i] == -1);
            assert(sv.phi[i] == i - 1);
        }
    }
    for (int it = 0; it < 2000; it++) {
        int x = rnd_int(2, n);
        auto f = sv.factor(x);
        int prod = 1;
        for (int p : f) prod *= p;
        assert(prod == x);
        for (int p : f) assert(is_prime_ref(p));
        auto fc = sv.factor_cnt(x);
        prod = 1;
        for (auto [p, e] : fc) {
            int cur = 1;
            for (int i = 0; i < e; i++) cur *= p;
            prod *= cur;
        }
        assert(prod == x);
    }
}

void test_small() {
    lin_sieve s0(0);
    assert(sz(s0.mu) == 1 && s0.mu[0] == 0);
    lin_sieve s1(1);
    assert(s1.mu[1] == 1);
    assert(s1.phi[1] == 1);
}

void test_mobius_func() {
    int n = 2000;
    auto mu = mobius(n);
    for (int i = 1; i <= n; i++) assert(mu[i] == mu_ref(i));
}

void test_euler_phi() {
    for (int x = 1; x <= 2000; x++) {
        assert(euler_phi::phi(x) == phi_ref(x));
    }
    int n = 2000;
    auto ph = euler_phi::phi_upto(n);
    for (int i = 1; i <= n; i++) assert(ph[i] == phi_ref(i));
}

void test_mu_phi_identities() {
    int n = 2000;
    lin_sieve sv(n);
    for (int i = 1; i <= n; i++) {
        ll sum_mu = 0, sum_phi = 0;
        for (int d : divisors(i)) {
            sum_mu += sv.mu[d];
            sum_phi += sv.phi[d];
        }
        assert(sum_mu == (i == 1));
        assert(sum_phi == i);
    }
    for (int it = 0; it < 2000; it++) {
        int a = rnd_int(1, 200);
        int b = rnd_int(1, 200);
        if (euclid::gcd(a, b) != 1) continue;
        int ab = a * b;
        if (ab > n) continue;
        assert(sv.phi[ab] == sv.phi[a] * sv.phi[b]);
    }
}

int main() {
    test_small();
    test_era();
    test_lin();
    test_mobius_func();
    test_euler_phi();
    test_mu_phi_identities();
    return 0;
}
