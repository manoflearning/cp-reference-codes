#include <iostream>
#include <algorithm>
using namespace std;

struct point {
	int x, y;
};

//ccw 알고리즘
ll ccw(point a, point b, point c) {
	//양수를 반환하면 ccw, 음수를 반환하면 cw, 0을 반환하면 a, b, c는 한 직선 위에 있다.
	return (b.x - a.x) * (c.y - a.y) - (c.x - a.x) * (b.y - a.y);
}

//두 선분 ab와 cd가 교차하는가?
bool isCross(point a, point b, point c, point d) {
	ll ab = ccw(a, b, c) * ccw(a, b, d);
	ll cd = ccw(c, d, a) * ccw(c, d, b);
	//네 점이 한 직선 위에 있을 경우
	if (ab == 0 && cd == 0) {
		pii A = { a.x, a.y }, B = { b.x, b.y }, C = { c.x, c.y }, D = { d.x, d.y };
		if (A > B) swap(A, B);
		if (C > D) swap(C, D);
		return (A <= D && C <= B);
	}
	//그렇지 않을 경우
	else return (ab <= 0 && cd <= 0);
}
