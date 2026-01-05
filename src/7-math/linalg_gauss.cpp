#pragma once
#include "num.hpp"

constexpr ld EPS = 1e-12;
constexpr int GAUSS_BSZ = 500;

// what: invert a real matrix (and solve) with Gauss-Jordan elimination.
// time: O(n^3); memory: O(n^2)
// constraint: a must be square; uses EPS for pivot check.
// usage: vector<vector<ld>> a=...; bool ok=gauss_real::inv(a);
struct gauss_real {
    static bool inv(vector<vector<ld>> &a) {
        int n = sz(a);
        vector<vector<ld>> b(n, vector<ld>(2 * n, 0));
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) b[i][j] = a[i][j];
            b[i][n + i] = 1;
        }
        int r = 0;
        for (int c = 0; c < n; c++) {
            // goal: find pivot in column c.
            int p = r;
            for (int i = r; i < n; i++)
                if (fabsl(b[i][c]) > fabsl(b[p][c])) p = i;
            if (fabsl(b[p][c]) <= EPS) return 0;
            swap(b[p], b[r]);
            ld inv = 1.0L / b[r][c];
            for (int j = 0; j < 2 * n; j++) b[r][j] *= inv;
            for (int i = 0; i < n; i++) {
                if (i == r) continue;
                ld f = b[i][c];
                if (fabsl(f) <= EPS) continue;
                for (int j = 0; j < 2 * n; j++) b[i][j] -= f * b[r][j];
            }
            r++;
        }
        for (int i = 0; i < n; i++) {
            a[i].assign(b[i].begin() + n, b[i].end());
        }
        return 1;
    }
};

// what: solve linear system modulo prime with Gauss-Jordan elimination.
// time: O(n*m^2); memory: O(n*m)
// constraint: mod is prime; matrix is n x (m+1) augmented.
// usage: auto x=gauss_mod::solve(a, mod); // empty if no solution
struct gauss_mod {
    static vector<int> solve(vector<vector<int>> a, int mod) {
        int n = sz(a);
        int m = sz(a[0]) - 1;
        vector<int> where(m, -1);
        int r = 0;
        for (int c = 0; c < m && r < n; c++) {
            int p = r;
            for (int i = r; i < n; i++)
                if (a[i][c]) {
                    p = i;
                    break;
                }
            if (a[p][c] == 0) continue;
            swap(a[p], a[r]);
            where[c] = r;
            ll inv = euclid::inv_mod(a[r][c], mod);
            for (int j = c; j <= m; j++) a[r][j] = (ll)a[r][j] * inv % mod;
            for (int i = 0; i < n; i++) {
                if (i == r || a[i][c] == 0) continue;
                int f = a[i][c];
                for (int j = c; j <= m; j++) {
                    ll v = a[i][j] - (ll)f * a[r][j] % mod;
                    if (v < 0) v += mod;
                    a[i][j] = (int)v;
                }
            }
            r++;
        }
        for (int i = r; i < n; i++) {
            bool all0 = 1;
            for (int j = 0; j < m; j++)
                if (a[i][j]) {
                    all0 = 0;
                    break;
                }
            if (all0 && a[i][m]) return {};
        }
        vector<int> ans(m, 0);
        for (int i = 0; i < m; i++)
            if (where[i] != -1) ans[i] = a[where[i]][m];
        return ans;
    }
};

// what: solve xor linear system over GF(2) using bitset Gauss-Jordan.
// time: O(n*m^2/64); memory: O(n*m/64)
// constraint: each row is size >= m+1; last bit is RHS.
// usage: auto x=gauss_xor::solve(a, m); // empty if no solution
struct gauss_xor {
    static vector<int> solve(vector<bitset<GAUSS_BSZ>> a, int m) {
        int n = sz(a);
        vector<int> where(m, -1);
        int r = 0;
        for (int c = 0; c < m && r < n; c++) {
            int p = -1;
            for (int i = r; i < n; i++)
                if (a[i][c]) {
                    p = i;
                    break;
                }
            if (p == -1) continue;
            swap(a[p], a[r]);
            where[c] = r;
            for (int i = 0; i < n; i++)
                if (i != r && a[i][c]) a[i] ^= a[r];
            r++;
        }
        for (int i = r; i < n; i++) {
            bool all0 = 1;
            for (int j = 0; j < m; j++)
                if (a[i][j]) {
                    all0 = 0;
                    break;
                }
            if (all0 && a[i][m]) return {};
        }
        vector<int> ans(m, 0);
        for (int i = 0; i < m; i++)
            if (where[i] != -1) ans[i] = a[where[i]][m];
        return ans;
    }
};
