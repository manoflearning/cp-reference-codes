#include <bits/stdc++.h>
using namespace std;
int main() {
	cin.tie(NULL); cout.tie(NULL);
	ios_base::sync_with_stdio(false);
	vector<int> a;
	sort(a.begin(), a.end());
	a.erase(unique(a.begin(), a.end()), a.end());
	int q; cin >> q;
	for (int i = 0; i < q; i++) {
		int num; cin >> num;
		cout << lower_bound(a.begin(), a.end(), num) - a.begin();
	}
	return 0;
}