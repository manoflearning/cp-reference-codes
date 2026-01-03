#include "../../src/5-string/z_algorithm.cpp"

// what: tests for z_func.
// time: random + naive; memory: O(1)
// constraint: small n.
// usage: g++ -std=c++17 test_z_algorithm.cpp && ./a.out

mt19937_64 rng(507);
int rnd(int l, int r) {
    uniform_int_distribution<int> dis(l, r);
    return dis(rng);
}
string rnd_s(int n) {
    string s;
    for (int i = 0; i < n; i++) s.pb('a' + rnd(0, 2));
    return s;
}

vector<int> na_z(const string &s) {
    int n = sz(s);
    vector<int> z(n);
    for (int i = 0; i < n; i++) {
        int k = 0;
        while (i + k < n && s[k] == s[i + k]) k++;
        z[i] = k;
    }
    return z;
}

void t_rnd() {
    for (int it = 0; it < 300; it++) {
        string s = rnd_s(rnd(0, 60));
        assert(z_func(s) == na_z(s));
    }
}

int main() {
    t_rnd();
    return 0;
}
