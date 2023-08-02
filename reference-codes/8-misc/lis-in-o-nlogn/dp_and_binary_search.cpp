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