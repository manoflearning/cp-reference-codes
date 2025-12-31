#include "../common/common.hpp"

// BOJ 14438 AC Code
// https://www.acmicpc.net/problem/14438
#pragma GCC optimize("O3")
#pragma GCC target("avx2")

#include <bits/stdc++.h>
#include <x86intrin.h>
using namespace std;

int N, M;
int A[101010] __attribute__((aligned(32)));

int main() {
    cin >> N;
    for (int i = 1; i <= N; i++) cin >> A[i];
    cin >> M;
    while (M--) {
        int op, x, y;
        cin >> op >> x >> y;
        if (op == 1) A[x] = y;
        else {
            int ans = 1e9 + 7;

            int i;
            __m256i mn = _mm256_set1_epi32(1e9 + 7);
            for (i = x; i + 8 <= y; i += 8) {
                __m256i cur = _mm256_load_si256((const __m256i *)&A[i]);
                mn = _mm256_min_epi32(mn, cur);
            }
            for (; i <= y; i++) ans = min(ans, A[i]);

            int tmp[8];
            _mm256_store_si256((__m256i *)tmp, mn);
            for (int i = 0; i < 8; i++)
                ans = min(ans, tmp[i]);

            cout << ans << '\n';
        }
    }
}