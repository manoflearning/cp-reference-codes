// 1. Fenwick Tree
struct Fenwick { // 0-indexed
  int flag, cnt; // array size
  vector<ll> arr, t;
  void build(int n) {
    for (flag = 1; flag < n; flag <<= 1, cnt++);
    arr.resize(flag);
    t.resize(flag);
    for (int i = 0; i < n; i++) cin >> arr[i];
    for (int i = 0; i < n; i++) {
      t[i] += arr[i];
      if (i | (i + 1) < flag) t[i | (i + 1)] += t[i];
    }
  }
  void add(int p, ll value) { // add value at position p
    arr[p] += value;
    while (p < flag) {
      t[p] += value;
      p |= p + 1;
    }
  }
  void modify(int p, ll value) { // set value at position p
    add(p, value - arr[p]);
  };
  ll query(int x) {
    ll ret = 0;
    while (x >= 0) ret += t[x], x = (x & (x + 1)) - 1;
    return ret;
  }
  ll query(int l, int r) {
    return query(r) - (l ? query(l - 1) : 0);
  }
  int kth(int k) { // find the kth smallest number (1-indexed)
    assert(t.back() >= k);
    int l = 0, r = arr.size();
    for (int i = 0; i <= cnt; i++) {
      int mid = (l + r) >> 1;
      ll val = mid ? t[mid - 1] : t.back();
      if (val >= k) r = mid;
      else l = mid, k -= val;
    }
    return l;
  }
} fw;

// 2. Fenwick Tree Range Update Point Query
struct Fenwick { // 1-indexed
  int flag;
  vector<ll> t;
  void build(int N) {
    flag = N;
    t.resize(flag + 1);
  }
  void modify(int l, int r, int val) { // add a val to all elements in interval [l, r]
    for (; l <= flag; l += l & -l) t[l] += val;
    for (r++; r <= flag; r += r & -r) t[r] -= val;
  }
  ll query(int x) {
    ll ret = 0;
    for (; x; x ^= x & -x) ret += t[x];
    return ret;
  }
} fw;

// 3. 2D Fenwick Tree
// INPUT: Given an 2D array of integers of size N * M.
// Can modify the value of the (x, y)th element.
// Can find the sum of elements from (sx, sy) to (ex, ey).
// OUTPUT: Given the query (1 sx sy ex ey), output the sum of elements from the interval (sx, sy) to (ex, ey)
// TIME COMPLEXITY: O(N * M) for initialize fenwick tree, O(logN * logM) for each query.
struct Fenwick2D { // 0-indexed
  int n, m, real_n, real_m;
  vector<vector<ll>> arr, t;
  void build(int N, int M) {
    real_n = N, real_m = M;

    n = m = 1;
    while (n < N) n <<= 1;
    while (m < M) m <<= 1;
    arr.resize(n, vector<ll>(m));
    t.resize(n, vector<ll>(m));

    for (int i = 0; i < real_n; i++) {
      for (int j = 0; j < real_m; j++) {
        cin >> arr[i][j];
      }
    }
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < m; j++) {
        t[i][j] += arr[i][j];

        int ni = i | (i + 1), nj = j | (j + 1);
        if (ni < n) t[ni][j] += t[i][j];
        if (nj < m) t[i][nj] += t[i][j];
        if (ni < n && nj < m) t[ni][nj] -= t[i][j];
      }
    }
  }
  void add(int x, int y, ll value) { // add value at position (x, y)
    assert(0 <= x && x < real_n && 0 <= y && y < real_m);
    arr[x][y] += value;
    for (int i = x; i < n; i |= i + 1) {
      for (int j = y; j < m; j |= j + 1) {
        t[i][j] += value;
      }
    }
  }
  void modify(int x, int y, ll value) { // set value at position (x, y)
    assert(0 <= x && x < real_n && 0 <= y && y < real_m);
    add(x, y, value - arr[x][y]);
  }
  ll query(ll x, ll y) {
    assert(0 <= x && x < real_n && 0 <= y && y < real_m);
    ll ret = 0;
    for (int i = x; i >= 0; i = (i & (i + 1)) - 1) {
      for (int j = y; j >= 0; j = (j & (j + 1)) - 1) {
        ret += t[i][j];
      }
    }
    return ret;
  }
  ll query(ll sx, ll sy, ll ex, ll ey) {
    assert(0 <= sx && sx <= ex && ex < real_n);
    assert(0 <= sy && sy <= ey && ey < real_m);
    ll ret = query(ex, ey);
    if (sx) ret -= query(sx - 1, ey);
    if (sy) ret -= query(ex, sy - 1);
    if (sx && sy) ret += query(sx - 1, sy - 1);
    return ret;
  }
} fw2d;