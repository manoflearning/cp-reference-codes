#include <iostream>
#include <algorithm>
using namespace std;
#define ll long long
#define pii pair<int, int>

struct point {
	ll x, y;
};

//ccw �˰�����
ll ccw(point a, point b, point c) {
	//����� ��ȯ�ϸ� ccw, ������ ��ȯ�ϸ� cw, 0�� ��ȯ�ϸ� a, b, c�� �� ���� ���� �ִ�.
	ll res = (b.x - a.x) * (c.y - a.y) - (c.x - a.x) * (b.y - a.y);
	return (res > 0 ? 1 : (res < 0 ? -1 : 0));
}

//�� ���� ab�� cd�� �����ϴ°�?
bool isCross(point a, point b, point c, point d) {
	ll ab = ccw(a, b, c) * ccw(a, b, d);
	ll cd = ccw(c, d, a) * ccw(c, d, b);
	//�� ���� �� ���� ���� ���� ���
	if (ab == 0 && cd == 0) {
		pii A = { a.x, a.y }, B = { b.x, b.y }, C = { c.x, c.y }, D = { d.x, d.y };
		if (A > B) swap(A, B);
		if (C > D) swap(C, D);
		return (A <= D && C <= B);
	}
	//�׷��� ���� ���
	else return (ab <= 0 && cd <= 0);
}
