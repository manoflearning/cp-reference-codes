// BOJ 11444 AC Code
// https://www.acmicpc.net/problem/11444
#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define sz(x) (int)(x).size()
const int MOD = 1e9 + 7;
struct Matrix {
    vector<vector<ll>> a;
    Matrix operator*(const Matrix& rhs) const {
        Matrix ret;
        ret.a.resize(sz(a), vector<ll>(sz(rhs.a[0])));
        for (int y = 0; y < sz(ret.a); y++) {
            for (int x = 0; x < sz(ret.a[y]); x++) {
                ll sum = 0;
                for (int i = 0; i < sz(a[y]); i++) {
                    sum = (sum + a[y][i] * rhs.a[i][x]) % MOD;
                }
                ret.a[y][x] = sum;
            }
        }
        return ret;
    }
};
Matrix matrixPower(const Matrix& val, ll exp) {
    if (exp == 1) return val;
    Matrix res = matrixPower(val, exp / 2);
    Matrix ret = res * res;
    if (exp & 1) ret = ret * val;
    return ret;
}
int main() {
    ll n; cin >> n;
    if (n == 1) {
        cout << 1;
        return 0;
    }
    // Base Matrix
    Matrix base;
    base.a.resize(2, vector<ll>(2));
    base.a[0][0] = base.a[0][1] = base.a[1][0] = 1;
    // Matrix Exponentiation
    Matrix ans = matrixPower(base, n - 1);
    cout << ans.a[0][0];
}