// Code to find Catalan number in O(n) time
#include <iostream>
using namespace std;
#define ll long long 

// Returns value of Binomial Coefficient C(n, k)
ll binomialCoeff(ll n, ll k) {
    ll res = 1;

    // Since C(n, k) = C(n, n-k)
    if (k > n - k) k = n - k;

    // Calculate value of [n*(n-1)*---*(n-k+1)] /
    // [k*(k-1)*---*1]
    for (int i = 0; i < k; i++) {
        res *= (n - i);
        res /= (i + 1);
    }

    return res;
}

// A Binomial coefficient based function to find nth catalan
// number in O(n) time
ll catalan(ll n) {
    // Calculate value of 2nCn
    ll c = binomialCoeff(2 * n, n);
    // return 2nCn/(n+1)
    return c / (n + 1);
}

// Driver code
int main() {
    cin.tie(NULL); cout.tie(NULL);
	ios_base::sync_with_stdio(false);

    for (int i = 0; i < 5; i++)
        cout << catalan(i) << " ";
        
    return 0;
}