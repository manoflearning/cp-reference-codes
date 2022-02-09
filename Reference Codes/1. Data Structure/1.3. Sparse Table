const int MAX = 1e5, MAXD = 17;

int sp[MAX][MAXD];

int main() {
	cin.tie(NULL); cout.tie(NULL);
	ios_base::sync_with_stdio(false);
  
  	//initialize
	for (int i = 0; i < MAX; i++) cin >> sp[i][0];

	for (int i = 0; i < MAX; i++) {
		for (int j = 1; j < MAXD; j++) {
			sp[i][j] = sp[sp[i][j - 1]][j - 1];
		}
	}
  
  	//query
	int q; cin >> q;

	for (int i = 0; i < q; i++) {
		int n, x;
		cin >> n >> x;
		
		for (int i = MAXD - 1; i >= 0; i--) {
			if (n & sp[x][i]) x = sp[x][i];
		}
	}

	return 0;
}
