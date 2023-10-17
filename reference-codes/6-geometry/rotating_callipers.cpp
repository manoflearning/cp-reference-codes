// BOJ 10254 AC Code
// https://www.acmicpc.net/problem/10254
#include <bits/stdc++.h>
using namespace std;
#define ll long long
struct point {
    ll x, y;
    bool operator<(const point& rhs) const {
        if (x != rhs.x) return x < rhs.x;
        return y < rhs.y;
    }
};
int n;
vector<point> p, ch;
point ans1, ans2;
void init() {
    n = 0;
    p.clear();
    ch.clear();
    ans1 = ans2 = { 0, 0 };
}
void input() {
    cin >> n;
    p.resize(n);
    ch.resize(n);
    for (auto& i : p) cin >> i.x >> i.y;
}
ll ccw(const point& a, const point& b, const point& c) {
	// res > 0 -> ccw, res < 0 -> cw, res = 0 -> colinear
	ll res = (b.x - a.x) * (c.y - a.y) - (c.x - a.x) * (b.y - a.y);
	return (res > 0 ? 1 : (res < 0 ? -1 : 0));
}
ll cccw(point a, point b, point c, point d) {
    d.x -= c.x - b.x;
    d.y -= c.y - b.y;
    return ccw(a, b, d);
}
ll dist(const point& p1, const point& p2) {
    return (p1.x - p2.x) * (p1.x - p2.x) + (p1.y - p2.y) * (p1.y - p2.y);
}
bool cmp(const point& p1, const point& p2) {
    return (ccw(p[0], p1, p2) > 0 || (ccw(p[0], p1, p2) == 0 && dist(p[0], p1) < dist(p[0], p2)));
}
void rotatingCallipers() {
    sort(p.begin(), p.end());
    sort(p.begin() + 1, p.end(), cmp);
    ch[0] = p[0];
    ch[1] = p[1];
    ll fl = 2, cnt = 2;
    for (int i = 2; i < n; i++) {
        while (fl >= 2 && ccw(ch[fl - 2], ch[fl - 1], p[i]) <= 0) fl--;
        ch[fl] = p[i], fl++;
    }
    ll fl2 = 1, mx = 0;
    for (int i = 0; i < fl; i++) {
        while ((fl2 + 1) != i && cccw(ch[i], ch[i + 1], ch[fl2 % fl], ch[(fl2 + 1) % fl]) > 0) {
            if (mx < dist(ch[i], ch[fl2 % fl])) {
                ans1 = ch[i], ans2 = ch[fl2 % fl];
                mx = dist(ch[i], ch[fl2 % fl]);
            }
            fl2++;
        }
        if (mx < dist(ch[i], ch[fl2 % fl])) {
            ans1 = ch[i], ans2 = ch[fl2 % fl];
            mx = dist(ch[i], ch[fl2 % fl]);
        }
    }
}
int main() {
    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);
    int tc; cin >> tc;
    while (tc--) {
        init();
        input();
        rotatingCallipers();
        cout << ans1.x << ' ' << ans1.y << ' ';
        cout << ans2.x << ' ' << ans2.y << '\n';
    }
}