// INPUT: Given an array of positive integers.
// OUTPUT: Print the length of the LIS, and one sequence that is LIS.
// TIME COMPLEXITY: O(NlogN).

// BOJ 14003 AC Code
// https://www.acmicpc.net/problem/14003
#include <bits/stdc++.h>
using namespace std;

int n, a[1010101];
vector<int> arr;
int idx[1010101];

int main() {
    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    // input
    cin >> n;
    for (int i = 1; i <= n; i++) cin >> a[i];
    
    // solve
    for (int i = 1; i <= n; i++) {
        int x = a[i];
        if (arr.empty() || arr.back() < x) {
            arr.push_back(x);
            idx[i] = arr.size();
        }
        else {
            int loc = lower_bound(arr.begin(), arr.end(), x) - arr.begin();
            arr[loc] = x, idx[i] = loc + 1;
        }
    }
    
    // output
    int ans1 = arr.size();
    cout << ans1 << '\n';
    vector<int> ans2;
    for (int i = n; i >= 1; i--) {
        if (idx[i] == ans1) {
            ans1--;
            ans2.push_back(a[i]);
        }
    }
    reverse(ans2.begin(), ans2.end());
    for (auto& i : ans2)
        cout << i << ' ';
}