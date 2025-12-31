#include "../../src/8-misc/random.cpp"

// what: tests for rng helper (reproducibility).
// time: O(n); memory: O(n)
// constraint: fixed seed.
// usage: g++ -std=c++17 test_random.cpp && ./a.out

void test_repro() {
    rng a(2), b(2);
    for (int i = 0; i < 100; i++) {
        assert(a.int_range(-5, 5) == b.int_range(-5, 5));
        assert(a.ll_range(-100, 100) == b.ll_range(-100, 100));
    }
}

void test_shuffle() {
    vector<int> v(50), w(50);
    iota(v.begin(), v.end(), 0);
    w = v;
    rng a(7), b(7);
    a.shuf(v);
    b.shuf(w);
    assert(v == w);
}

int main() {
    test_repro();
    test_shuffle();
    return 0;
}
