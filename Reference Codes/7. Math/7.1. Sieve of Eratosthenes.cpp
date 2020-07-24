#include <iostream>
#include <algorithm>
using namespace std;
#define ll long long

const int MAX = 1e6;

bool isPrime[MAX + 1];
vector<int> prime(1, 2);

void getPrime() {
	fill(isPrime, isPrime + MAX + 1, true);

	for (ll i = 4; i <= MAX; i += 2)
		isPrime[i] = false;
	for (ll i = 3; i <= MAX; i++) {
		if (isPrime[i]) prime.push_back(i);
		for (ll j = i * i; j <= MAX; j += i * 2)
			isPrime[j] = false;
	}
}
