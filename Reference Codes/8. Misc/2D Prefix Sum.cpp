const int MAX = 1010;
ll arr[MAX][MAX], psum[MAX][MAX];
void buildPsum() {
      FOR(i, 1, MAX) {
            FOR(j, 1, MAX) {
                  psum[i][j] += arr[i][j];
                  psum[i][j] += psum[i][j - 1];
                  psum[i][j] += psum[i - 1][j];
                  psum[i][j] -= psum[i - 1][j - 1];
            }
      }
}