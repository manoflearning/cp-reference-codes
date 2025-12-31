#include "../common/common.hpp"
#include <immintrin.h>

// what: AVX2 usage snippets (i32 add/sum/min/count, f32 dot/add).
// time: O(n/8); memory: O(1)
// constraint: compile with -mavx2; 0-indexed; sums fit in ll.
// usage: simd_i32::add(a,b,c,n); ll s=simd_i32::sum(a,n); int mn=simd_i32::range_min(a,l,r);
// usage: int cnt=simd_i32::count_eq(a,n,v); float d=simd_f32::dot(a,b,n);

struct simd_i32 {
    static void add(const int *a, const int *b, int *c, int n) {
        // goal: c[i] = a[i] + b[i]
        int i = 0;
        for (; i + 8 <= n; i += 8) {
            __m256i va = _mm256_loadu_si256((const __m256i *)(a + i));
            __m256i vb = _mm256_loadu_si256((const __m256i *)(b + i));
            __m256i vc = _mm256_add_epi32(va, vb);
            _mm256_storeu_si256((__m256i *)(c + i), vc);
        }
        for (; i < n; i++) c[i] = a[i] + b[i];
    }

    static ll sum(const int *a, int n) {
        // goal: sum all values with 64-bit accumulation
        int i = 0;
        __m256i acc0 = _mm256_setzero_si256();
        __m256i acc1 = _mm256_setzero_si256();
        for (; i + 8 <= n; i += 8) {
            __m256i v = _mm256_loadu_si256((const __m256i *)(a + i));
            __m128i lo = _mm256_castsi256_si128(v);
            __m128i hi = _mm256_extracti128_si256(v, 1);
            acc0 = _mm256_add_epi64(acc0, _mm256_cvtepi32_epi64(lo));
            acc1 = _mm256_add_epi64(acc1, _mm256_cvtepi32_epi64(hi));
        }
        alignas(32) ll tmp0[4], tmp1[4];
        _mm256_store_si256((__m256i *)tmp0, acc0);
        _mm256_store_si256((__m256i *)tmp1, acc1);
        ll res = 0;
        for (int k = 0; k < 4; k++) res += tmp0[k] + tmp1[k];
        for (; i < n; i++) res += a[i];
        return res;
    }

    static int range_min(const int *a, int l, int r) {
        // goal: min in [l, r]
        int i = l;
        __m256i mn = _mm256_set1_epi32(INT_MAX);
        for (; i + 8 <= r + 1; i += 8) {
            __m256i cur = _mm256_loadu_si256((const __m256i *)(a + i));
            mn = _mm256_min_epi32(mn, cur);
        }
        alignas(32) int tmp[8];
        _mm256_store_si256((__m256i *)tmp, mn);
        int res = INT_MAX;
        for (int k = 0; k < 8; k++) res = min(res, tmp[k]);
        for (; i <= r; i++) res = min(res, a[i]);
        return res;
    }

    static int count_eq(const int *a, int n, int v) {
        // goal: count occurrences of v
        int i = 0;
        int cnt = 0;
        __m256i needle = _mm256_set1_epi32(v);
        for (; i + 8 <= n; i += 8) {
            __m256i cur = _mm256_loadu_si256((const __m256i *)(a + i));
            __m256i cmp = _mm256_cmpeq_epi32(cur, needle);
            int mask = _mm256_movemask_epi8(cmp);
            cnt += __builtin_popcount((unsigned)mask) / 4;
        }
        for (; i < n; i++) cnt += (a[i] == v);
        return cnt;
    }
};

struct simd_f32 {
    static void add_inplace(float *a, const float *b, int n) {
        // goal: a[i] += b[i]
        int i = 0;
        for (; i + 8 <= n; i += 8) {
            __m256 va = _mm256_loadu_ps(a + i);
            __m256 vb = _mm256_loadu_ps(b + i);
            _mm256_storeu_ps(a + i, _mm256_add_ps(va, vb));
        }
        for (; i < n; i++) a[i] += b[i];
    }

    static float dot(const float *a, const float *b, int n) {
        // goal: dot product
        int i = 0;
        __m256 acc = _mm256_setzero_ps();
        for (; i + 8 <= n; i += 8) {
            __m256 va = _mm256_loadu_ps(a + i);
            __m256 vb = _mm256_loadu_ps(b + i);
            acc = _mm256_add_ps(acc, _mm256_mul_ps(va, vb));
        }
        alignas(32) float tmp[8];
        _mm256_store_ps(tmp, acc);
        float res = 0.0f;
        for (int k = 0; k < 8; k++) res += tmp[k];
        for (; i < n; i++) res += a[i] * b[i];
        return res;
    }
};
