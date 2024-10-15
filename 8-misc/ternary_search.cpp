void ternarySearch() {
    int l = 1, r = 10'000;
    while (r - l >= 3) {
        int mid1 = (2 * l + r) / 3;
        int mid2 = (l + 2 * r) / 3;
        int res1 = f(mid1), res2 = f(mid2);
        if (res1 <= res2) l = mid1;
        else r = mid2;
    }
    int res = 0;
    for (int i = l; i <= r; i++)
        res = max(res, f(i));
}