// Input: two line segments ab and cd
// Output: 1 if ab and cd intersect, 0 if they do not intersect
// Time Complexity: O(1)

// BOJ 17387 AC Code
// https://www.acmicpc.net/problem/17387

#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define pii pair<int, int>

struct Point { ll x, y; };

ll ccw(const Point& a, const Point& b, const Point& c) {
    // res > 0 -> ccw, res < 0 -> cw, res = 0 -> colinear
    ll res = (b.x - a.x) * (c.y - a.y) - (c.x - a.x) * (b.y - a.y);
    return (res > 0 ? 1 : (res < 0 ? -1 : 0));
}

// Does the line segment ab and cd intersect?
bool isCross(const Point& a, const Point& b, const Point& c, const Point& d) {
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

int main() {
    Point a, b, c, d;
    cin >> a.x >> a.y >> b.x >> b.y;
    cin >> c.x >> c.y >> d.x >> d.y;
    cout << isCross(a, b, c, d);
}