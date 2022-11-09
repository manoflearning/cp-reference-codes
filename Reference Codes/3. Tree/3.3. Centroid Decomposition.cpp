#include <bits/stdc++.h>
using namespace std;
const int MAXV = 202020;
vector<int> adj[MAXV];
int used[MAXV], siz[MAXV], dep[MAXV], cdtree[MAXV];
int getSize(int now, int prv) {
	siz[now] = 1;
	for (auto i : adj[now]) {
		if (used[i] || prv == i) continue;
		siz[now] += getSize(i, now);
	}
	return siz[now];
}
int getCent(int now, int prv, int cnt) {
	for (auto& i : adj[now]) {
		if (used[i] || i == prv) continue;
		if (siz[i] > cnt / 2) return getCent(i, now, cnt);
	}
	return now;
}
void cd(int now, int prv) {
	int cnt = getSize(now, prv);
	int cent = getCent(now, prv, cnt);
	cdtree[now] = prv;
	used[cent] = 1;
	for (auto i : adj[cent])
		if (!used[i]) cd(i, cent);
}
int main() {
	cin.tie(NULL); cout.tie(NULL);
	ios_base::sync_with_stdio(false);
	cd(0, -1);
	return 0;
}