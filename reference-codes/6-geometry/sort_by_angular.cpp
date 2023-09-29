// Sort by Angular (Relative to Origin)
struct Point {
    ll x, y;
    bool operator<(const Point& rhs) const {
        return x ^ rhs.x ? x < rhs.x : y < rhs.y;
    }
};

const Point o = { 0, 0 };
vector<Point> p;

ll ccw(const Point& a, const Point& b, const Point& c) {
    // res > 0 -> ccw, res < 0 -> cw, res = 0 -> colinear
    ll res = (b.x - a.x) * (c.y - a.y) - (c.x - a.x) * (b.y - a.y);
    return (res > 0 ? 1 : (res < 0 ? -1 : 0));
}
inline ll dist(const Point& v) { return v.x * v.x + v.y * v.y; }

// If the angle between any two points and the origin is less than 180 degrees,
// they can be sorted through the cross product of the vectors.
// Therefore, the points were divided into 1st and 4th quadrants and 2nd and 3rd quadrants,
// and the points in the 1st and 4th quadrants were arranged in front.
void sortByAngular() {
    sort(p.begin(), p.end(), [&](const Point& lhs, const Point& rhs) {
        if ((lhs < o) ^ (rhs < o)) return (lhs < o) < (rhs < o);
        if (ccw(o, lhs, rhs)) return ccw(o, lhs, rhs) > 0;
        return dist(lhs) < dist(rhs);
    });
}