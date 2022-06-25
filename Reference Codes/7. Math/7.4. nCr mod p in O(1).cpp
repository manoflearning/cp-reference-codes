// C++ program to answer queries
// of nCr in O(1) time.
#include <iostream>
using namespace std;
#define ll long long

const int N = 1000001;

// array to store inverse of 1 to N
ll factorialNumInverse[N + 1];

// array to precompute inverse of 1! to N!
ll naturalNumInverse[N + 1];

// array to store factorial of first N numbers
ll fact[N + 1];

// Function to precompute inverse of numbers
void InverseofNumber(ll p) {
	naturalNumInverse[0] = naturalNumInverse[1] = 1;
	for (int i = 2; i <= N; i++)
		naturalNumInverse[i] = naturalNumInverse[p % i] * (p - p / i) % p;
}
// Function to precompute inverse of factorials
void InverseofFactorial(ll p) {
	factorialNumInverse[0] = factorialNumInverse[1] = 1;

	// precompute inverse of natural numbers
	for (int i = 2; i <= N; i++)
		factorialNumInverse[i] = (naturalNumInverse[i] * factorialNumInverse[i - 1]) % p;
}

// Function to calculate factorial of 1 to N
void factorial(ll p) {
	fact[0] = 1;

	// precompute factorials
	for (int i = 1; i <= N; i++) {
		fact[i] = (fact[i - 1] * i) % p;
	}
}

// Function to return nCr % p in O(1) time
ll Binomial(ll N, ll R, ll p) {
	// n C r = n!*inverse(r!)*inverse((n-r)!)
	ll ans = ((fact[N] * factorialNumInverse[R])
			% p * factorialNumInverse[N - R])
			% p;
	return ans;
}

// Driver Code
int main() {
	cin.tie(NULL); cout.tie(NULL);
	ios_base::sync_with_stdio(false);

	// Calling functions to precompute the
	// required arrays which will be required
	// to answer every query in O(1)
	ll p = 1000000007;
	InverseofNumber(p);
	InverseofFactorial(p);
	factorial(p);

	// 1st query
	ll N = 15;
	ll R = 4;
	cout << Binomial(N, R, p) << '\n';

	// 2nd query
	N = 20;
	R = 3;
	cout << Binomial(N, R, p) << '\n';

	return 0;
}
