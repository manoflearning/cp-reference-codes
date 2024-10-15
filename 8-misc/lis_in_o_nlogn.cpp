// 1. DP and Binary Search
// INPUT: Given an array of positive integers.
// OUTPUT: Print the length of the LIS.
// TIME COMPLEXITY: O(NlogN).

// BOJ 12015 AC Code
// https://www.acmicpc.net/problem/12015
#include <bits/stdc++.h>
using namespace std;

int n;
vector<int> arr;

int main() {
	cin.tie(NULL); cout.tie(NULL);
	ios_base::sync_with_stdio(false);

	cin >> n;
	
	for (int i = 1; i <= n; i++) {
		int x; cin >> x;
		if (arr.empty() || arr.back() < x) arr.push_back(x);
		else *lower_bound(arr.begin(), arr.end(), x) = x;
	}
	
	cout << arr.size();
}

// 2. DP and Binary Search (Backtrace)
// INPUT: Given an array of positive integers.
// OUTPUT: Print the length of the LIS, and one sequence that is LIS.
// TIME COMPLEXITY: O(NlogN).

// BOJ 14003 AC Code
// https://www.acmicpc.net/problem/14003
#include <bits/stdc++.h>
using namespace std;

int n, a[1010101];
vector<int> arr;
int idx[1010101];

int main() {
    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    // input
    cin >> n;
    for (int i = 1; i <= n; i++) cin >> a[i];
    
    // solve
    for (int i = 1; i <= n; i++) {
        int x = a[i];
        if (arr.empty() || arr.back() < x) {
            arr.push_back(x);
            idx[i] = arr.size();
        }
        else {
            int loc = lower_bound(arr.begin(), arr.end(), x) - arr.begin();
            arr[loc] = x, idx[i] = loc + 1;
        }
    }
    
    // output
    int ans1 = arr.size();
    cout << ans1 << '\n';
    vector<int> ans2;
    for (int i = n; i >= 1; i--) {
        if (idx[i] == ans1) {
            ans1--;
            ans2.push_back(a[i]);
        }
    }
    reverse(ans2.begin(), ans2.end());
    for (auto& i : ans2)
        cout << i << ' ';
}

// 3. Segment Tree
// INPUT: Given an array of positive integers.
// OUTPUT: Print the length of the LIS.
// TIME COMPLEXITY: O(NlogN).

// BOJ 12015 AC Code
// https://www.acmicpc.net/problem/12015
#include <bits/stdc++.h>
using namespace std;

struct Seg {
	int flag;  // array size
	vector<int> t;

	void build(int N) {
		for (flag = 1; flag < N; flag <<= 1);
		t.resize(2 * flag);
	}
	void modify(int p, int value) {  // set value at position p
		for (t[p += flag - 1] = value; p > 1; p >>= 1) t[p >> 1] = max(t[p], t[p ^ 1]);
	}
	int query(int l, int r) {
		return query(l, r, 1, 1, flag);
	}
	int query(int l, int r, int n, int nl, int nr) {  // sum on interval [l, r]
		if (r < nl || nr < l) return 0;
		if (l <= nl && nr <= r) return t[n];

		int mid = (nl + nr) / 2;
		return max(query(l, r, n << 1, nl, mid), query(l, r, n << 1 | 1, mid + 1, nr));
	}
}seg;

struct xidx { int x, idx; };

bool operator<(xidx& a, xidx& b) {
	if (a.x != b.x) return a.x < b.x;
	return a.idx > b.idx;
}

int n;
vector<xidx> a;

void input() {
	cin >> n;
	for (int i = 0; i < n; i++) {
		int x; cin >> x;
		a.push_back({ x, i + 1 });
	}
}

void f() {
	seg.build(n);

	sort(a.begin(), a.end());

	for (auto& i : a) {
		seg.modify(i.idx, seg.query(1, i.idx - 1) + 1);
	}
}

int main() {
	cin.tie(NULL); cout.tie(NULL);
	ios_base::sync_with_stdio(false);

	input();

	f();

	cout << seg.query(1, n);
}
