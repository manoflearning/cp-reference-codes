// Bulldozer Trick
// There are a total of O(N^2) results of sorting points on a two-dimensional plane based on an arbitrary axis.
// The Bulldozer Trick traverses all O(N^2) results in O(N^2logN) time.

struct Point {
    ll x, y;
    bool operator<(const Point& rhs) const {
        return tie(x, y) < tie(rhs.x, rhs.y);
    }
};

struct Line {
    int u, v; ll dx, dy; // u < v, dx >= 0;
    bool operator<(const Line& rhs) const {
        if (dy * rhs.dx != rhs.dy * dx) return dy * rhs.dx < rhs.dy * dx;
        return tie(u, v) < tie(rhs.u, rhs.v);
    }
    bool operator==(const Line& rhs) const {
        return dy * rhs.dx == rhs.dy * dx;
    }
};

int n, pos[2020];
Point p[2020];

void bulldozerTrick() {
    sort(p + 1, p + 1 + n);
    for (int i = 1; i <= n; i++) pos[i] = i;

    // find the slope between every two points.
    vector<Line> arr;
    for (int i = 1; i <= n; i++) {
        for (int j = i + 1; j <= n; j++) {
            arr.push_back({ i, j, p[j].x - p[i].x, p[j].y - p[i].y });
        }
    }
    sort(arr.begin(), arr.end());

    // can check one of the results of sorting points at here.
    
    for (int i = 0, j = 0; i < arr.size(); i = j) {
        while (j < arr.size() && arr[j] == arr[i]) j++; // all lines in [i, j) are same
        for (int k = i; k < j; k++) {
            int u = arr[k].u, v = arr[k].v;
            swap(p[pos[u]], p[pos[v]]);
            swap(pos[u], pos[v]);
        }

        // can check one of the results of sorting points at here.
    }
}