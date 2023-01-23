// Manber-Myers Algorithm for Suffix Array
// Time Conplexity: O(nlog^2n)
// Kasai's Algorithm for LCP(Longest Common Prefix)
// Time Complexity: O(n)
// BOJ 9248 AC Code
// https://www.acmicpc.net/problem/9248
#include <bits/stdc++.h>
using namespace std;
#define sz(x) (int)(x).size()
vector<int> buildsa(const string& s) {
    int n = sz(s);
    vector<int> sa(n), r(n + 1), nr(n + 1);
    for (int i = 0; i < n; i++) sa[i] = i, r[i] = s[i];
    for (int d = 1; d < n; d <<= 1) {
        auto cmp = [&](int i, int j) {
            if (r[i] ^ r[j]) return r[i] < r[j];
            return r[i + d] < r[j + d];
        };
        sort(sa.begin(), sa.end(), cmp);
        nr[sa[0]] = 1;
        for (int i = 1; i < n; i++)
            nr[sa[i]] = nr[sa[i - 1]] + cmp(sa[i - 1], sa[i]);
        r = nr;
    }
    return sa;
}
vector<int> buildlcp(const string& s, const vector<int>& sa) {
    int n = sz(s);
    vector<int> lcp(n), isa(n);
    for (int i = 0; i < n; i++) isa[sa[i]] = i;
    for (int k = 0, i = 0; i < n; i++) if (isa[i]) {
        for (int j = sa[isa[i] - 1]; s[i + k] == s[j + k]; k++);
        lcp[isa[i]] = (k ? k-- : 0);
    }
    return lcp;
}
int main() {
    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);
    string s; cin >> s;
    vector<int> sa = buildsa(s);
    vector<int> lcp = buildlcp(s, sa);
    for (auto& i : sa) cout << i + 1 << ' ';
    cout << '\n';
    cout << "x ";
    for (int i = 1; i < sz(lcp); i++) cout << lcp[i] << ' ';
    return 0;
}
// Manber-Myers Algorithm for Suffix Array
// Time Conplexity: O(nlogn)
// Kasai's Algorithm for LCP(Longest Common Prefix)
// Time Complexity: O(n)
// BOJ 9248 AC Code
// https://www.acmicpc.net/problem/9248
#include <bits/stdc++.h>
using namespace std;
#define sz(x) (int)(x).size()
vector<int> buildsa(const string& s) {
    int n = sz(s), m = max(256, n) + 1;
    vector<int> sa(n), r(2 * n), nr(2 * n), cnt(m), idx(n);
    for (int i = 0; i < n; i++) sa[i] = i, r[i] = s[i];
    for (int d = 1; d < n; d <<= 1) {
        auto cmp = [&](int i, int j) {
            if (r[i] ^ r[j]) return r[i] < r[j];
            return r[i + d] < r[j + d];
        };
        for (int i = 0; i < m; i++) cnt[i] = 0;
        for (int i = 0; i < n; i++) cnt[r[i + d]]++;
        for (int i = 1; i < m; i++) cnt[i] += cnt[i - 1];
        for (int i = n - 1; ~i; i--) idx[--cnt[r[i + d]]] = i;
        for (int i = 0; i < m; i++) cnt[i] = 0;
        for (int i = 0; i < n; i++) cnt[r[i]]++;
        for (int i = 1; i < m; i++) cnt[i] += cnt[i - 1];
        for (int i = n - 1; ~i; i--) sa[--cnt[r[idx[i]]]] = idx[i];
        nr[sa[0]] = 1;
        for (int i = 1; i < n; i++) nr[sa[i]] = nr[sa[i - 1]] + cmp(sa[i - 1], sa[i]);
        for (int i = 0; i < n; i++) r[i] = nr[i];
        if (r[sa[n - 1]] == n) break;
    }
    return sa;
}
vector<int> buildlcp(const string& s, const vector<int>& sa) {
    int n = sz(s);
    vector<int> lcp(n), isa(n);
    for (int i = 0; i < n; i++) isa[sa[i]] = i;
    for (int k = 0, i = 0; i < n; i++) if (isa[i]) {
        for (int j = sa[isa[i] - 1]; s[i + k] == s[j + k]; k++);
        lcp[isa[i]] = (k ? k-- : 0);
    }
    return lcp;
}
int main() {
    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);
    string s; cin >> s;
    vector<int> sa = buildsa(s);
    vector<int> lcp = buildlcp(s, sa);
    for (auto& i : sa) cout << i + 1 << ' ';
    cout << '\n';
    cout << "x ";
    for (int i = 1; i < sz(lcp); i++) cout << lcp[i] << ' ';
    return 0;
}