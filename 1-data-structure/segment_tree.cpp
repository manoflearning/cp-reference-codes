// 1. Segment Tree
int flag;  // array size
struct Seg {  // 1-indexed
	vector<ll> t;
	void build(int n) {
		for (flag = 1; flag < n; flag <<= 1);
		t.resize(2 * flag);
		for (int i = flag; i < flag + n; i++) cin >> t[i];
		for (int i = flag - 1; i >= 1; i--) t[i] = t[i << 1] + t[i << 1 | 1];
	}
	void modify(int p, ll value) {  // set value at position p
		for (t[p += flag - 1] = value; p > 1; p >>= 1) t[p >> 1] = t[p] + t[p ^ 1];
	}
	ll query(int l, int r, int n = 1, int nl = 1, int nr = flag) {  // sum on interval [l, r]
		if (r < nl || nr < l) return 0;
		if (l <= nl && nr <= r) return t[n];
		int mid = (nl + nr) / 2;
		return query(l, r, n << 1, nl, mid) + query(l, r, n << 1 | 1, mid + 1, nr);
	}
}seg;

// 2. Iterative Segment Tree
const int MAXN = 1010101;  // limit for array size
struct Seg {  // 0-indexed
	int n;  // array size
	ll t[2 * MAXN];
	void build(int N) {
		n = N;
		for (int i = 0; i < n; i++) cin >> t[n + i];
		for (int i = n - 1; i >= 1; i--) t[i] = t[i << 1] + t[i << 1 | 1];
	}
	void modify(int p, ll value) {  // set value at position p
		for (t[p += n] = value; p > 1; p >>= 1) t[p >> 1] = t[p] + t[p ^ 1];
	}
	ll query(int l, int r) {  // sum on interval [l, r)
		ll ret = 0;
		for (l += n, r += n; l < r; l >>= 1, r >>= 1) {
			if (l & 1) ret += t[l++];
			if (r & 1) ret += t[--r];
		}
		return ret;
	}
}seg;

// 3. k-th Segment Tree
int flag;  // array size
struct Seg {
    vector<ll> t;
    void build(int n) {
        for (flag = 1; flag < n; flag <<= 1);
        t.resize(flag << 1);
    }
    void add(int p, ll value) {  // add value at position p
        for (t[p += flag - 1] += value; p > 1; p >>= 1) t[p >> 1] = t[p] + t[p ^ 1];
    }
    ll kth(ll k, int n = 1) { // find the kth smallest number (1-indexed)
        assert(t[n] >= k);
        if (flag <= n) return n - flag + 1;
        if (k <= t[n << 1]) return kth(k, n << 1);
        else return kth(k - t[n << 1], n << 1 | 1);
    }
}seg;

// 4. Segment Tree with Lazy Propagation
int flag;  // array size
struct Seg {  // 1-indexed
	vector<ll> t, lazy;
	void build(int n) {
		for (flag = 1; flag < n; flag <<= 1);
		t.resize(2 * flag);
		lazy.resize(2 * flag);
		for (int i = flag; i < flag + n; i++) cin >> t[i];
		for (int i = flag - 1; i >= 1; i--) t[i] = t[i << 1] + t[i << 1 | 1];
	}
	// add a value to all elements in interval [l, r]
	void modify(int l, int r, ll value, int n = 1, int nl = 1, int nr = flag) {
		propagate(n, nl, nr);
		if (r < nl || nr < l) return;
		if (l <= nl && nr <= r) {
			lazy[n] += value;
			propagate(n, nl, nr);
			return;
		}
		int mid = (nl + nr) >> 1;
		modify(l, r, value, n << 1, nl, mid);
		modify(l, r, value, n << 1 | 1, mid + 1, nr);
		t[n] = t[n << 1] + t[n << 1 | 1];
	}
	ll query(int l, int r, int n = 1, int nl = 1, int nr = flag) {  // sum on interval [l, r]
		propagate(n, nl, nr);
		if (r < nl || nr < l) return 0;
		if (l <= nl && nr <= r) return t[n];
		int mid = (nl + nr) / 2;
		return query(l, r, n << 1, nl, mid) + query(l, r, n << 1 | 1, mid + 1, nr);
	}
	void propagate(int n, int nl, int nr) {
		if (lazy[n] != 0) {
			if (n < flag) {
				lazy[n << 1] += lazy[n];
				lazy[n << 1 | 1] += lazy[n];
			}
			t[n] += lazy[n] * (nr - nl + 1);
			lazy[n] = 0;
		}
	}
}seg;

// 5. Persistent Segment Tree
// TIME COMPLEXITY: O(n) for initialize PST, O(logn) for each query.
// SPACE COMPLEXITY: O(nlogm).
struct PST { // 1-indexed
    int flag; // array size
    struct Node { int l, r; ll val; };
    vector<Node> t;
    vector<int> root;

    void addNode() { t.push_back({ -1, -1, 0 }); }
    void build(int l, int r, int n)  {
        assert(0 <= n && n < sz(t));
        if (l == r) { t[n].val = a[l]; return; }
        addNode();
        t[n].l = sz(t) - 1;
        addNode();
        t[n].r = sz(t) - 1;

        int mid = (l + r) >> 1;
        build(l, mid, t[n].l);
        build(mid + 1, r, t[n].r);
        t[n].val = t[t[n].l].val + t[t[n].r].val;
    }
    void build(int Flag) {
        addNode();
        root.push_back(sz(t) - 1);
        flag = Flag;
        build(1, flag, root[0]);
    }
    void modify(int p, ll val, int l, int r, int n1, int n2) {
        assert(0 <= n1 && n1 < sz(t));
        assert(0 <= n2 && n2 < sz(t));
        if (p < l || r < p) { t[n2] = t[n1]; return; }
        if (l == r) { t[n2].val = val; return; }

        int mid = (l + r) >> 1;
        if (p <= mid) {
            t[n2].r = t[n1].r;
            addNode();
            t[n2].l = sz(t) - 1;
            modify(p, val, l, mid, t[n1].l, t[n2].l);
        }
        else {
            t[n2].l = t[n1].l;
            addNode();
            t[n2].r = sz(t) - 1;
            modify(p, val, mid + 1, r, t[n1].r, t[n2].r);
        }
        t[n2].val = t[t[n2].l].val + t[t[n2].r].val;
    }
    void modify(int p, ll val) {
        addNode();
        root.push_back(sz(t) - 1);
        modify(p, val, 1, flag, root[sz(root) - 2], root[sz(root) - 1]);
    }
    ll query(int l, int r, int n, int nl, int nr) {
        assert(0 <= n && n < sz(t));
        if (r < nl || nr < l) return 0;
        if (l <= nl && nr <= r) return t[n].val;
        int mid = (nl + nr) >> 1;
        return query(l, r, t[n].l, nl, mid) + query(l, r, t[n].r, mid + 1, nr);
    }
    ll query(int l, int r, int n) {
        assert(n < sz(root));
        return query(l, r, root[n], 1, flag);
    }
}pst;

// 6. Dynamic Segment Tree
const int MAXL = 1, MAXR = 1000000;

struct Node {
    ll x; int l, r;
};

struct Dyseg {
    vector<Node> t = { { 0, -1, -1 }, { 0, -1, -1 } };
    void modify(int p, ll x, int n = 1, int nl = MAXL, int nr = MAXR) {
        if (p < nl || nr < p) return;
        t[n].x += x;
        if (nl < nr) {
            int mid = (nl + nr) >> 1;
            if (p <= mid) {
                if (t[n].l == -1) {
                    t[n].l = sz(t);
                    t.push_back({ 0, -1, -1 });
                }
                modify(p, x, t[n].l, nl, mid);
            }
            else {
                if (t[n].r == -1) {
                    t[n].r = sz(t);
                    t.push_back({ 0, -1, -1 });
                }
                modify(p, x, t[n].r, mid + 1, nr);
            }
        }
    }
    ll query(int l, int r, int n = 1, int nl = MAXL, int nr = MAXR) {
        if (r < nl || nr < l) return 0;
        if (l <= nl && nr <= r) return t[n].x;
        int mid = (nl + nr) >> 1;
        ll ret = 0;
        if (l <= mid) {
            if (t[n].l == -1) {
                t[n].l = sz(t);
                t.push_back({ 0, -1, -1 });
            }
            ret += query(l, r, t[n].l, nl, mid);
        }
        if (mid + 1 <= r) {
            if (t[n].r == -1) {
                t[n].r = sz(t);
                t.push_back({ 0, -1, -1 });
            }
            ret += query(l, r, t[n].r, mid + 1, nr);
        }
        return ret;
    }
}dyseg;
