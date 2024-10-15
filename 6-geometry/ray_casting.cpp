// BOJ 1688 AC Code
// https://www.acmicpc.net/problem/1688
#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define pii pair<int, int>
struct point {
    ll x, y;
    bool operator==(const point& rhs) const {
        return x == rhs.x && y == rhs.y;
    }
    bool operator<=(const point& rhs) const {
        if (x < rhs.x || (x == rhs.x && y <= rhs.y)) return 1;
        else return 0;
    }
};
int n;
vector<point> p;
point a, b, c;
void input() {
    cin >> n;
    p.resize(n);
    for (auto& i : p) {
        cin >> i.x >> i.y;
    }
    p.push_back(p[0]);
    cin >> a.x >> a.y;
    cin >> b.x >> b.y;
    cin >> c.x >> c.y;
}
ll ccw(const point& a, const point& b, const point& c) {
    // res > 0 -> ccw, res < 0 -> cw, res = 0 -> colinear
    ll res = (b.x - a.x) * (c.y - a.y) - (c.x - a.x) * (b.y - a.y);
    return (res > 0 ? 1 : (res < 0 ? -1 : 0));
}
// Does the line segment ab and cd intersect?
bool isCross(point a, point b, point c, point d) {
    ll ab = ccw(a, b, c) * ccw(a, b, d);
    ll cd = ccw(c, d, a) * ccw(c, d, b);
    if (ab == 0 && cd == 0) {
        pii A = { a.x, a.y }, B = { b.x, b.y }, C = { c.x, c.y }, D = { d.x, d.y };
        if (A > B) swap(A, B);
        if (C > D) swap(C, D);
        return (A <= D && C <= B);
    }
    else return (ab <= 0 && cd <= 0);
}
bool insidePolygon(point v) {
    point u = { 1010101010ll, v.y + 1 };
    for (int i = 0; i < n; i++) {
        if (p[i] == v) return 1;
    }
    for (int i = 0; i < n; i++) {
        if (!ccw(p[i], p[i + 1], v) && (p[i] <= v ^ p[i + 1] <= v)) return 1;
    }
    int cnt = 0;
    for (int i = 0; i < n; i++) {
        cnt += isCross(p[i], p[i + 1], u, v);
    }
    return cnt & 1;
}
int main() {
    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);
    input();
    cout << (insidePolygon(a) ? 1 : 0) << '\n';
    cout << (insidePolygon(b) ? 1 : 0) << '\n';
    cout << (insidePolygon(c) ? 1 : 0) << '\n';
}