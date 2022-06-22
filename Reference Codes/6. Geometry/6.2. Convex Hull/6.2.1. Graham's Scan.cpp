// BOJ 1708 AC Code
// https://www.acmicpc.net/problem/1708
#include <iostream>
#include <vector>
#include <algorithm>
#define ll long long
using namespace std;

struct point {
	ll x, y, px, py; // (px, py) is the relative coordinate value at the reference point
	point() : point(0, 0, 0, 0) {}
	point(int sx, int sy) : point(sx, sy, 0, 0) {}
	point(int sx, int sy, int spx, int spy) : x(sx), y(sy), px(spx), py(spy) {}
	bool operator <(point& O) {
		if (O.px * py != px * O.py) return O.px * py < px * O.py;
		if (y != O.y) return y < O.y;
		return x < O.x;
	}
};

vector<point> p;

ll ccw(point& a, point& b, point& c) {
	// res > 0 -> ccw, res < 0 -> cw, res = 0 -> colinear
	ll res = (b.x - a.x) * (c.y - a.y) - (c.x - a.x) * (b.y - a.y);
	return (res > 0 ? 1 : (res < 0 ? -1 : 0));
}

int main() {
	cin.tie(NULL); cout.tie(NULL);
	ios_base::sync_with_stdio(false);

	int N; cin >> N;

	for (int i = 0; i < N; i++) {
		int x, y;
		cin >> x >> y;
		p.push_back(point(x, y));
	}

	sort(p.begin(), p.end());

	for (int i = 1; i < N; i++) {
		p[i].px = p[i].x - p[0].x;
		p[i].py = p[i].y - p[0].y;
	}

	sort(p.begin() + 1, p.end());

	vector<int> st;
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

	cout << st.size() << '\n';

	return 0;
}