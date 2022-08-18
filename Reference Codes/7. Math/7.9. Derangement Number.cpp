// Counting derangements of a set amounts to the hat-check problem, 
// in which one considers the number of ways in which n hats
// can be returned to n people such that no hat makes it back to its owner.

// Recurrence relation: 
// f1 = 0, f2 = 1.
// fi = (i - 1) * (f{i-1} + f{i-2}) (i >= 3)
#include <bits/stdc++.h>
using namespace std;
#define ll long long

const int MOD = 1e9 + 7;
const int MAX = 101010;

ll dp[MAX];

int main() {
    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    dp[1] = 0, dp[2] = 1;
    for (int i = 2; i < MAX; i++) {
        dp[i] = (i - 1) * (dp[i - 1] + dp[i - 2]) % MOD;
    }

    int n; cin >> n;
    cout << dp[n];

    return 0;
}