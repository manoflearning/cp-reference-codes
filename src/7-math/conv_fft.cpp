#pragma once
#include "../common/common.hpp"
#include "num.hpp"

// what: multiply integer sequences using FFT (optionally via split for mod).
// time: O(n log n); memory: O(n)
// constraint: precision errors for huge coeffs; mul_mod uses split 15 bits.
// usage: auto c=fft_conv::mul(a,b); auto d=fft_conv::mul_mod(a,b,mod);
struct fft_conv {
    using real_t = double;
    using cpx = complex<real_t>;

    static void fft(vector<cpx> &a, bool inv = 0) {
        // goal: compute DFT (or inverse DFT if inv=1).
        int n = sz(a);
        for (int i = 1, j = 0; i < n; i++) {
            int bit = n >> 1;
            while (j >= bit) j -= bit, bit >>= 1;
            j += bit;
            if (i < j) swap(a[i], a[j]);
        }
        vector<cpx> root(n / 2);
        real_t ang = 2 * acos(-1) / n * (inv ? -1 : 1);
        for (int i = 0; i < n / 2; i++) root[i] = cpx(cos(ang * i), sin(ang * i));
        for (int len = 2; len <= n; len <<= 1) {
            int step = n / len;
            for (int i = 0; i < n; i += len)
                for (int j = 0; j < len / 2; j++) {
                    cpx u = a[i + j], v = a[i + j + len / 2] * root[step * j];
                    a[i + j] = u + v;
                    a[i + j + len / 2] = u - v;
                }
        }
        if (inv)
            for (int i = 0; i < n; i++) a[i] /= n;
    }

    static vl mul(const vl &a, const vl &b) {
        // result: integer convolution of a and b.
        if (a.empty() || b.empty()) return {};
        int n = 1;
        while (n < sz(a) + sz(b)) n <<= 1;
        vector<cpx> fa(all(a)), fb(all(b));
        fa.resize(n);
        fb.resize(n);
        fft(fa);
        fft(fb);
        for (int i = 0; i < n; i++) fa[i] *= fb[i];
        fft(fa, 1);
        vl ret(n);
        for (int i = 0; i < n; i++) ret[i] = llround(fa[i].real());
        return ret;
    }

    static vl mul_mod(const vl &a, const vl &b, ll mod) {
        // result: convolution of a and b modulo mod.
        if (a.empty() || b.empty()) return {};
        int n = 1;
        while (n < sz(a) + sz(b)) n <<= 1;
        vector<cpx> v1(n), v2(n), r1(n), r2(n);
        for (int i = 0; i < sz(a); i++) v1[i] = cpx(a[i] >> 15, a[i] & 32767);
        for (int i = 0; i < sz(b); i++) v2[i] = cpx(b[i] >> 15, b[i] & 32767);
        fft(v1);
        fft(v2);
        for (int i = 0; i < n; i++) {
            int j = i ? n - i : i;
            cpx a1 = (v1[i] + conj(v1[j])) * cpx(0.5, 0);
            cpx a2 = (v1[i] - conj(v1[j])) * cpx(0, -0.5);
            cpx b1 = (v2[i] + conj(v2[j])) * cpx(0.5, 0);
            cpx b2 = (v2[i] - conj(v2[j])) * cpx(0, -0.5);
            r1[i] = (a1 * b1) + (a1 * b2) * cpx(0, 1);
            r2[i] = (a2 * b1) + (a2 * b2) * cpx(0, 1);
        }
        fft(r1, 1);
        fft(r2, 1);
        vl ret(n);
        for (int i = 0; i < n; i++) {
            ll av = llround(r1[i].real()) % mod;
            ll bv = (llround(r1[i].imag()) + llround(r2[i].real())) % mod;
            ll cv = llround(r2[i].imag()) % mod;
            ll v = ((av << 30) + (bv << 15) + cv) % mod;
            if (v < 0) v += mod;
            ret[i] = v;
        }
        return ret;
    }
};

// what: multiply polynomials under a single NTT-friendly prime.
// time: O(n log n); memory: O(n)
// constraint: MOD is NTT prime, ROOT is primitive root; n is power of two.
// usage: auto c=ntt_mod<MOD,ROOT>::mul(a,b);
template <ll MOD_, ll ROOT_>
struct ntt_mod {
    static constexpr ll MOD = MOD_;
    static constexpr ll ROOT = ROOT_;

    static ll norm(ll x) {
        x %= MOD;
        if (x < 0) x += MOD;
        return x;
    }

    static ll mod_pow(ll b, ll e) {
        ll ans = 1;
        while (e) {
            if (e & 1) ans = ans * b % MOD;
            b = b * b % MOD;
            e >>= 1;
        }
        return ans;
    }

    static void ntt(vl &a) {
        // goal: inplace NTT of a.
        int n = sz(a), lg = 31 - __builtin_clz(n);
        static vl rt(2, 1);
        for (static int k = 2, s = 2; k < n; k <<= 1, s++) {
            rt.resize(n);
            ll z[] = {1, mod_pow(ROOT, MOD >> s)};
            for (int i = k; i < 2 * k; i++) rt[i] = rt[i / 2] * z[i & 1] % MOD;
        }
        vl rev(n);
        for (int i = 0; i < n; i++) rev[i] = (rev[i / 2] | (i & 1) << lg) / 2;
        for (int i = 0; i < n; i++)
            if (i < rev[i]) swap(a[i], a[rev[i]]);
        for (int k = 1; k < n; k <<= 1)
            for (int i = 0; i < n; i += 2 * k)
                for (int j = 0; j < k; j++) {
                    ll z = rt[j + k] * a[i + j + k] % MOD;
                    ll &ai = a[i + j];
                    a[i + j + k] = ai - z + (z > ai ? MOD : 0);
                    ai += (ai + z >= MOD ? z - MOD : z);
                }
    }

    static vl mul(const vl &a, const vl &b) {
        // result: convolution under MOD.
        if (a.empty() || b.empty()) return {};
        int s = sz(a) + sz(b) - 1;
        int n = 1;
        while (n < s) n <<= 1;
        int inv = mod_pow(n, MOD - 2);
        vl l(n, 0), r(n, 0), out(n);
        for (int i = 0; i < sz(a); i++) l[i] = norm(a[i]);
        for (int i = 0; i < sz(b); i++) r[i] = norm(b[i]);
        ntt(l);
        ntt(r);
        for (int i = 0; i < n; i++)
            out[-i & (n - 1)] = (ll)l[i] * r[i] % MOD * inv % MOD;
        ntt(out);
        return {out.begin(), out.begin() + s};
    }
};

// what: convolution wrapper specialized to the common 998244353 prime.
// time: O(n log n); memory: O(n)
// constraint: mod fixed to 998244353; n must be power of two.
// usage: auto c=ntt_conv::mul(a,b);
struct ntt_conv : ntt_mod<998244353, 3> {};

// what: convolution under any modulus by combining three NTT primes with CRT.
// time: O(n log n); memory: O(n)
// constraint: mod > 0; result fits in ll; good for mod < 2^62.
// usage: auto c=ntt_any::mul(a,b,mod);
struct ntt_any {
    static constexpr ll M1 = 167772161;
    static constexpr ll M2 = 469762049;
    static constexpr ll M3 = 1224736769;

    static vl mul(const vl &a, const vl &b, ll mod) {
        // result: convolution under arbitrary mod via CRT.
        if (a.empty() || b.empty()) return {};
        using ntt1 = ntt_mod<M1, 3>;
        using ntt2 = ntt_mod<M2, 3>;
        using ntt3 = ntt_mod<M3, 3>;

        auto c1 = ntt1::mul(a, b);
        auto c2 = ntt2::mul(a, b);
        auto c3 = ntt3::mul(a, b);

        const ll M1M2 = M1 * M2;
        const ll INV_M1_M2 = euclid::inv_mod(M1, M2);
        const ll INV_M1M2_M3 = euclid::inv_mod(M1M2 % M3, M3);

        int n = sz(c1);
        vl ret(n);
        for (int i = 0; i < n; i++) {
            ll x1 = c1[i];
            ll x2 = c2[i] - x1;
            x2 %= M2;
            if (x2 < 0) x2 += M2;
            x2 = (ll)((__int128)x2 * INV_M1_M2 % M2);

            ll t = (x1 + (ll)((__int128)M1 * x2 % M3)) % M3;
            ll x3 = c3[i] - t;
            x3 %= M3;
            if (x3 < 0) x3 += M3;
            x3 = (ll)((__int128)x3 * INV_M1M2_M3 % M3);

            __int128 val = x1 + (__int128)M1 * x2 + (__int128)M1M2 * x3;
            ll v = (ll)(val % mod);
            if (v < 0) v += mod;
            ret[i] = v;
        }
        return ret;
    }
};
