#include "../common/common.hpp"
// INPUT: ln: A vector of directed lines (half-planes).
// - IMPORTANT: The valid region is to the LEFT of the line (s -> t).
// - Tip: Add a bounding box (4 lines) if the area might be unbounded.
// OUTPUT: A vector of vertices representing the intersection polygon.
// - Order: Counter-Clockwise (CCW).
// - Returns an empty vector if the intersection is empty or degenerate.
// TIME COMPLEXITY: O(nlogn)
struct Point {
  ld x, y;
};
struct Line {
  Point s, t;
};
constexpr ld EPS = 1e-9;
inline bool equals(ld a, ld b) { return abs(a - b) < EPS; }
bool line_intersect(Point &s1, Point &e1, Point &s2, Point &e2, Point &v) {
  ld vx1 = e1.x - s1.x, vy1 = e1.y - s1.y;
  ld vx2 = e2.x - s2.x, vy2 = e2.y - s2.y;
  ld det = vx1 * (-vy2) - (-vx2) * vy1;
  if (equals(det, 0)) return 0;
  ld s = (ld)((s2.x - s1.x) * (-vy2) + (s2.y - s1.y) * vx2) / det;
  v.x = s1.x + vx1 * s;
  v.y = s1.y + vy1 * s;
  return 1;
}
bool bad(Line &a, Line &b, Line &c) {
  Point v;
  if (!line_intersect(a.s, a.t, b.s, b.t, v)) return 0;
  ld crs = (c.t.x - c.s.x) * (v.y - c.s.y) - (c.t.y - c.s.y) * (v.x - c.s.x);
  return crs < 0 || equals(crs, 0);
}
vector<Point> hpi(vector<Line> &ln) {
  auto lsgn = [&](const Line &a) {
    if (a.s.y == a.t.y) return a.s.x > a.t.x;
    return a.s.y > a.t.y;
  };
  sort(ln.begin(), ln.end(), [&](const Line &a, const Line &b) {
    if (lsgn(a) != lsgn(b)) return lsgn(a) < lsgn(b);
    return (a.t.x - a.s.x) * (b.t.y - b.s.y) - (a.t.y - a.s.y) * (b.t.x - b.s.x) > 0;
  });
  deque<Line> dq;
  for (int i = 0; i < sz(ln); i++) {
    while (dq.size() >= 2 && bad(dq[dq.size() - 2], dq.back(), ln[i]))
      dq.pop_back();
    while (dq.size() >= 2 && bad(dq[0], dq[1], ln[i]))
      dq.pop_front();
    if (dq.size() < 2 || !bad(dq.back(), ln[i], dq[0]))
      dq.push_back(ln[i]);
  }
  vector<Point> ret;
  if (dq.size() >= 3)
    for (int i = 0; i < sz(dq); i++) {
      int j = (i + 1) % sz(dq);
      Point v;
      if (!line_intersect(dq[i].s, dq[i].t, dq[j].s, dq[j].t, v)) continue;
      ret.push_back(v);
    }
  return ret;
}
