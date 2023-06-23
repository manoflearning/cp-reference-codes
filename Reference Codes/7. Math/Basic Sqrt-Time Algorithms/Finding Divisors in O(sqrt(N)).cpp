// INPUT: Given a natural number x.
// OUTPUT: Find all the divisors of x.
// TIME COMPLEXITY: O(sqrt(x)).

vector<int> di;
void findingDivisors(int x) {
    for (int i = 1; i <= sqrt(x); i++) {
        if (x % i == 0) {
            di.push_back(i);
            if (x / i != i) di.push_back(x / i);
        }
    }
    sort(di.begin(), di.end());
}