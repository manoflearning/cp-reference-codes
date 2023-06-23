// INPUT: Given a natural number x.
// OUTPUT: Find the result of the prime factorization of x.
// TIME COMPLEXITY: O(sqrt(x)).

vector<int> p;
void primeFactorization(int x) {
    while (x % 2 == 0) {
        x /= 2;
        p.push_back(2);
    }
    for (int i = 3; i <= sqrt(x); i += 2) {
        while (x % i == 0) {
            x /= i;
            p.push_back(i);
        }
    }
    if (x > 1) p.push_back(x);
}