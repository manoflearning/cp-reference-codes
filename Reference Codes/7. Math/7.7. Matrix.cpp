// Unverified code, many features to be added
#define sz(x) (int)(x).size()
const int MOD = 1e9 + 7;
struct Matrix {
	vector<vector<ll>> a;
	Matrix operator*(const Matrix& rhs) const {
		Matrix ret;
		ret.a.resize(sz(a), vector<ll>(sz(rhs.a[0])));
		for (int y = 0; y < sz(ret.a); y++) {
			for (int x = 0; x < sz(ret.a[y]); x++) {
				ll sum = 0;
				for (int i = 0; i < sz(a[y]); i++) {
					sum = (sum + a[y][i] * rhs.a[i][x]) % MOD;
				}
				ret.a[y][x] = sum;
			}
		}
		return ret;
	}
};
