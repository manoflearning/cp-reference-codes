#define ll long long

struct Fraction {
    ll n, d; // represent n/d

    Fraction(ll N, ll D) { n = N, d = D; reduce(); }
    Fraction(ll N) { n = N, d = 1; }
    Fraction() { n = 0, d = 1; }

    ll gcd(ll a, ll b) {
        if (b == 0) return a;
        else return gcd(b, a % b);
    }
    void reduce() {
        //ll g = gcd(n, d);
        //n /= g, d /= g;
        if (d < 0) n *= -1, d *= -1;
    }

    bool operator==(const Fraction& rhs) const {
        return n * rhs.d == rhs.n * d;
    }
    bool operator!=(const Fraction& rhs) const {
        return n * rhs.d != rhs.n * d;
    }
    bool operator<(const Fraction& rhs) const {
        return n * rhs.d < rhs.n * d;
    }
    bool operator>(const Fraction& rhs) const {
        return n * rhs.d > rhs.n * d;
    }

    Fraction operator+(const Fraction& rhs) const {
        Fraction ret;
        ret.n = n * rhs.d + rhs.n * d;
        ret.d = d * rhs.d;
        ret.reduce();
        return ret;
    }
    Fraction operator-(const Fraction& rhs) const {
        Fraction ret;
        ret.n = n * rhs.d - rhs.n * d;
        ret.d = d * rhs.d;
        ret.reduce();
        return ret;
    }
    Fraction operator*(const Fraction& rhs) {
        Fraction ret;
        ret.n = n * rhs.n;
        ret.d = d * rhs.d;
        ret.reduce();
        return ret;
    }
    Fraction operator/(const Fraction& rhs) {
        Fraction ret;
        ret.n = n * rhs.d;
        ret.d = d * rhs.n;
        ret.reduce();
        return ret;
    }
};