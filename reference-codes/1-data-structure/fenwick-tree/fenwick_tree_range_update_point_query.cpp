struct Fenwick { // 1-indexed
    int flag;
    vector<ll> t;
    void build(int N) {
        flag = N;
        t.resize(flag + 1);
    }
    void modify(int l, int r, int val) { // add a val to all elements in interval [l, r]
        for (; l <= flag; l += l & -l) t[l] += val;
        for (r++; r<= flag; r += r & -r) t[r] -= val;
    }
    ll query(int x) {
        ll ret = 0;
        for (; x; x ^= x & -x) ret += t[x];
        return ret;
    }
} fw;
