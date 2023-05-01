// TIME COMPLEXITY: O(Nlog(log(N)))
const int MAX = 1e6;
bool isPrime[MAX + 1];
vector<int> prime(1, 2);
void getPrime() {
	fill(isPrime + 2, isPrime + MAX + 1, 1);
	for (ll i = 4; i <= MAX; i += 2)
		isPrime[i] = 0;
	for (ll i = 3; i <= MAX; i += 2) {
		if (isPrime[i]) prime.push_back(i);
		for (ll j = i * i; j <= MAX; j += i * 2)
			isPrime[j] = 0;
	}
}