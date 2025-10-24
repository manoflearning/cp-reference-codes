#include "../common/common.hpp"

// Z Algorithm
// Given a string S of length n, the Z Algorithm produces an array Z
// where Z[i] is the length of the longest substring starting from S[i] which is also a prefix of S
const int MAXS = 1010101;
string s;
int z[MAXS];
void input() {
  string du;
  cin >> du;
  for (int i = sz(du) - 1; i >= 0; i--)
    s.push_back(du[i]);
}
void zfunction() {
  z[0] = sz(s);
  int l = 0, r = 0;
  for (int i = 1; i < sz(s); i++) {
    if (i > r) {
      l = r = i;
      while (r < sz(s) && s[r - l] == s[r]) r++;
      z[i] = r - l;
      r--;
    } else {
      int k = i - l;
      if (z[k] < r - i + 1) z[i] = z[k];
      else {
        l = i;
        while (r < sz(s) && s[r - l] == s[r]) r++;
        z[i] = r - l;
        r--;
      }
    }
  }
}
int main() {
  input();
  zfunction();
  int q;
  cin >> q;
  while (q--) {
    int x;
    cin >> x;
    cout << z[sz(s) - x] << '\n';
  }
}