#include "../../src/7-math/nt_euclid.cpp"

// what: tests for nt_euclid wrapper (euclid functions).
// time: O(1); memory: O(1)
// constraint: none.
// usage: g++ -std=c++17 test_nt_euclid.cpp && ./a.out

int main() {
    assert(euclid::gcd(12, 18) == 6);
    assert(euclid::gcd(-12, 18) == 6);
    assert(euclid::lcm(12, 18) == 36);
    assert(euclid::lcm(0, 18) == 0);

    auto eg = euclid::egcd(30, 18);
    assert(30 * eg.fr.fr + 18 * eg.fr.sc == eg.sc);
    assert(eg.sc == 6);

    assert(euclid::inv_mod(3, 11) == 4);
    assert(euclid::inv_mod(-3, 11) == 7);
    ll x = euclid::lin_cong(4, 2, 6);
    assert(x != -1);
    assert((4 * x - 2) % 6 == 0);
    assert(euclid::lin_cong(2, 1, 4) == -1);
    return 0;
}
