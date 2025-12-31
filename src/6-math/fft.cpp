#include "../common/common.hpp"
namespace fft {
using real_t = double;
using cpx = complex<real_t>;
void FFT(vector<cpx> &a, bool inv_fft = false) {
    int N = a.size();
    vector<cpx> root(N / 2);
    for (int i = 1, j = 0; i < N; i++) {
        int bit = (N >> 1);
        while (j >= bit) j -= bit, bit >>= 1;
        j += bit;
        if (i < j) swap(a[i], a[j]);
    }
    real_t ang = 2 * acos(-1) / N * (inv_fft ? -1 : 1);
    for (int i = 0; i < N / 2; i++) root[i] = cpx(cos(ang * i), sin(ang * i));
    /*
    XOR Convolution : set roots[*] = 1.
    OR Convolution : set roots[*] = 1, and do following:
    if (!inv) a[j + k] = u + v, a[j + k + i/2] = u;
    else a[j + k] = v, a[j + k + i/2] = u - v;
    */
    for (int i = 2; i <= N; i <<= 1) {
        int step = N / i;
        for (int j = 0; j < N; j += i)
            for (int k = 0; k < i / 2; k++) {
                cpx u = a[j + k], v = a[j + k + i / 2] * root[step * k];
                a[j + k] = u + v;
                a[j + k + i / 2] = u - v;
            }
    }
    if (inv_fft)
        for (int i = 0; i < N; i++) a[i] /= N; // skip for OR convolution.
}
vector<ll> multiply(const vector<ll> &_a, const vector<ll> &_b) {
    vector<cpx> a(all(_a)), b(all(_b));
    int N = 2;
    while (N < a.size() + b.size()) N <<= 1;
    a.resize(N);
    b.resize(N);
    FFT(a);
    FFT(b);
    for (int i = 0; i < N; i++) a[i] *= b[i];
    FFT(a, 1);
    vector<ll> ret(N);
    for (int i = 0; i < N; i++) ret[i] = llround(a[i].real());
    return ret;
}
vector<ll> multiply_mod(const vector<ll> &a, const vector<ll> &b, const ull mod) {
    int N = 2;
    while (N < a.size() + b.size()) N <<= 1;
    vector<cpx> v1(N), v2(N), r1(N), r2(N);
    for (int i = 0; i < a.size(); i++) v1[i] = cpx(a[i] >> 15, a[i] & 32767);
    for (int i = 0; i < b.size(); i++) v2[i] = cpx(b[i] >> 15, b[i] & 32767);
    FFT(v1);
    FFT(v2);
    for (int i = 0; i < N; i++) {
        int j = i ? N - i : i;
        cpx ans1 = (v1[i] + conj(v1[j])) * cpx(0.5, 0);
        cpx ans2 = (v1[i] - conj(v1[j])) * cpx(0, -0.5);
        cpx ans3 = (v2[i] + conj(v2[j])) * cpx(0.5, 0);
        cpx ans4 = (v2[i] - conj(v2[j])) * cpx(0, -0.5);
        r1[i] = (ans1 * ans3) + (ans1 * ans4) * cpx(0, 1);
        r2[i] = (ans2 * ans3) + (ans2 * ans4) * cpx(0, 1);
    }
    FFT(r1, true);
    FFT(r2, true);
    vector<ll> ret(N);
    for (int i = 0; i < N; i++) {
        ll av = llround(r1[i].real()) % mod;
        ll bv = (llround(r1[i].imag()) + llround(r2[i].real())) % mod;
        ll cv = llround(r2[i].imag()) % mod;
        ret[i] = (av << 30) + (bv << 15) + cv;
        ret[i] %= mod;
        ret[i] += mod;
        ret[i] %= mod;
    }
    return ret;
}
} // namespace fft
namespace ntt {
constexpr ll MOD = (119 << 23) + 1, root = 3; // = 998244353
// For p < 2^30 there is also e.g. 5 << 25, 7 << 26, 479 << 21
// and 483 << 21 (same root). The last two are > 10^9.
ll modpow(ll b, ll e) {
    ll ans = 1;
    for (; e; b = b * b % MOD, e /= 2)
        if (e & 1) ans = ans * b % MOD;
    return ans;
}
void ntt(vector<ll> &a) {
    int n = sz(a), L = 31 - __builtin_clz(n);
    static vector<ll> rt(2, 1);
    for (static int k = 2, s = 2; k < n; k *= 2, s++) {
        rt.resize(n);
        ll z[] = {1, modpow(root, MOD >> s)};
        for (int i = k; i < 2 * k; i++)
            rt[i] = rt[i / 2] * z[i & 1] % MOD;
    }
    vector<ll> rev(n);
    for (int i = 0; i < n; i++) rev[i] = (rev[i / 2] | (i & 1) << L) / 2;
    for (int i = 0; i < n; i++)
        if (i < rev[i]) swap(a[i], a[rev[i]]);
    for (int k = 1; k < n; k *= 2)
        for (int i = 0; i < n; i += 2 * k)
            for (int j = 0; j < k; j++) {
                ll z = rt[j + k] * a[i + j + k] % MOD, &ai = a[i + j];
                a[i + j + k] = ai - z + (z > ai ? MOD : 0);
                ai += (ai + z >= MOD ? z - MOD : z);
            }
}
vector<ll> multiply(const vector<ll> &a, const vector<ll> &b) {
    if (a.empty() || b.empty()) return {};
    int s = sz(a) + sz(b) - 1, B = 32 - __builtin_clz(s),
        n = 1 << B;
    int inv = modpow(n, MOD - 2);
    vector<ll> L(a), R(b), out(n);
    L.resize(n), R.resize(n);
    ntt(L), ntt(R);
    for (int i = 0; i < n; i++)
        out[-i & (n - 1)] = (ll)L[i] * R[i] % MOD * inv % MOD;
    ntt(out);
    return {out.begin(), out.begin() + s};
}
} // namespace ntt