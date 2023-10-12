int n;
vector<int> uf(1010101, -1);

int find(int x) {
	if (uf[x] < 0) return x;
	return uf[x] = find(uf[x]);
}

void merge(int a, int b) {
	int A = find(a), B = find(b);
	if (A == B) return;
	uf[A] += uf[B];
	uf[B] = A;
}