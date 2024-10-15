// 1. Graham Scan
// BOJ 1708 AC Code
// https://www.acmicpc.net/problem/1708
#include <bits/stdc++.h>
using namespace std;
#define ll long long
struct point {
  ll x, y;
  bool operator<(const point &rhs) const {
    if (y != rhs.y) return y < rhs.y;
    return x < rhs.x;
  }
};
int N;
vector<point> p;
vector<int> st;
ll ccw(const point &a, const point &b, const point &c) {
  // res > 0 -> ccw, res < 0 -> cw, res = 0 -> colinear
  ll res = (b.x - a.x) * (c.y - a.y) - (c.x - a.x) * (b.y - a.y);
  return (res > 0 ? 1 : (res < 0 ? -1 : 0));
}
void input() {
  cin >> N;
  for (int i = 0; i < N; i++) {
    int x, y;
    cin >> x >> y;
    p.push_back({x, y});
  }
}
ll dist(const point &p1, const point &p2) {
  return (p1.x - p2.x) * (p1.x - p2.x) + (p1.y - p2.y) * (p1.y - p2.y);
}
bool cmp(const point &p1, const point &p2) {
  return (ccw(p[0], p1, p2) > 0 || (ccw(p[0], p1, p2) == 0 && dist(p[0], p1) < dist(p[0], p2)));
}
void grahamScan() {
  sort(p.begin(), p.end());
  sort(p.begin() + 1, p.end(), cmp);
  st.push_back(0);
  st.push_back(1);
  for (int next = 2; next < N; next++) {
    while (st.size() >= 2) {
      int first = st.back();
      st.pop_back();
      int second = st.back();
      if (ccw(p[second], p[first], p[next]) > 0) {
        st.push_back(first);
        break;
      }
    }
    st.push_back(next);
  }
}
int main() {
  cin.tie(NULL), cout.tie(NULL);
  ios_base::sync_with_stdio(false);
  input();
  grahamScan();
  cout << st.size();
}

// 2. Monotone Chain
// BOJ 1708 AC Code
// https://www.acmicpc.net/problem/1708
#include <bits/stdc++.h>
using namespace std;
#define ll long long
struct point {
  ll x, y;
  bool operator<(const point &rhs) const {
    if (x != rhs.x) return x < rhs.x;
    else return y < rhs.y;
  }
};
int N;
vector<point> p;
vector<int> dh, uh;
ll ccw(const point &a, const point &b, const point &c) {
  // res > 0 -> ccw, res < 0 -> cw, res = 0 -> colinear
  ll res = (b.x - a.x) * (c.y - a.y) - (c.x - a.x) * (b.y - a.y);
  return (res > 0 ? 1 : (res < 0 ? -1 : 0));
}
void input() {
  cin >> N;
  for (int i = 0; i < N; i++) {
    int x, y;
    cin >> x >> y;
    p.push_back({x, y});
  }
}
void monotoneChain() {
  sort(p.begin(), p.end());
  // calculate lower hull
  dh.push_back(0);
  dh.push_back(1);
  for (int next = 2; next < N; next++) {
    while (dh.size() >= 2) {
      int first = dh.back();
      dh.pop_back();
      int second = dh.back();
      if (ccw(p[second], p[first], p[next]) > 0) {
        dh.push_back(first);
        break;
      }
    }
    dh.push_back(next);
  }
  // calculate upper hull
  uh.push_back(N - 1);
  uh.push_back(N - 2);
  for (int next = N - 3; next >= 0; next--) {
    while (uh.size() >= 2) {
      int first = uh.back();
      uh.pop_back();
      int second = uh.back();
      if (ccw(p[second], p[first], p[next]) > 0) {
        uh.push_back(first);
        break;
      }
    }
    uh.push_back(next);
  }
}
int main() {
  cin.tie(NULL), cout.tie(NULL);
  ios_base::sync_with_stdio(false);
  input();
  monotoneChain();
  cout << (int)dh.size() + (int)uh.size() - 2;
}