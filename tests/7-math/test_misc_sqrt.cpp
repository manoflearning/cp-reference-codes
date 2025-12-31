#include "../../src/7-math/misc_sqrt.cpp"

// what: tests for sqrt_alg (divisors/prime factors).
// time: random + brute; memory: O(n)
// constraint: fixed seed.
// usage: g++ -std=c++17 test_misc_sqrt.cpp && ./a.out

mt19937_64 rng(14);
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

vector<int> div_ref(int x) {
    vector<int> d;
    for (int i = 1; i <= x; i++)
        if (x % i == 0) d.push_back(i);
    return d;
}

vector<int> fac_ref(int x) {
    vector<int> p;
    for (int i = 2; 1LL * i * i <= x; i++) {
        while (x % i == 0) {
            p.push_back(i);
            x /= i;
        }
    }
    if (x > 1) p.push_back(x);
    return p;
}

int main() {
    assert(sqrt_alg::divisors(1) == vector<int>({1}));
    assert(sqrt_alg::prime_fac(1).empty());
    assert(sqrt_alg::divisors(36) == vector<int>({1, 2, 3, 4, 6, 9, 12, 18, 36}));
    assert(sqrt_alg::prime_fac(36) == vector<int>({2, 2, 3, 3}));
    for (int it = 0; it < 1000; it++) {
        int x = rnd_int(1, 5000);
        auto d1 = sqrt_alg::divisors(x);
        auto d2 = div_ref(x);
        sort(all(d2));
        assert(d1 == d2);

        auto f1 = sqrt_alg::prime_fac(x);
        auto f2 = fac_ref(x);
        assert(f1 == f2);
        int prod = 1;
        for (int p : f1) {
            assert(is_prime_ref(p));
            prod *= p;
        }
        assert(prod == x);
    }
    return 0;
}
