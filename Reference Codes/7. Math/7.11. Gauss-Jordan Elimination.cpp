// Inverse Matrix
void inverse_matrix(vector<vector<double>> &a){
    int n = a.size();
    int m = n + n;
    for(int i = 0; i < n; ++i)
        for(int j = 0; j < n; ++j)
            a[i].push_back(i==j);
    for(int c = 0, r = 0; c < m && r < n; ++c){
        int p = r; // pivot row
        for(int i = r; i < n; ++i)
            if(a[p][c] < a[i][c])
                p = i;
        if(a[p][c] == 0){ puts("no inverse"); return; }; 
        for(int j = 0; j < m; ++j)
            swap(a[p][j], a[r][j]);
        double t = a[r][c];
        for(int j = 0; j < m; ++j)
            a[r][j] /= t;
        for(int i = 0; i < n; ++i) if(i != r){
            double t = a[i][c];
            for(int j = c; j < m; ++j)
                a[i][j] -= a[r][j] * t;
        }
        ++r;
    }
    for(int i=0;i<n;++i,puts(""))
        for(int j=0;j<n;++j)
            printf("%lf ",a[i][n+j]);
}
// Gauss-Jordan Elimination modulo p
vector<int> gauss_mod(vector<vector<int>> &a,int mod){
    vector<int> inv(mod); // modulo inverse 전처리
    inv[1] = 1;
    for(int i = 2; i < mod; ++i)
        inv[i] = mod - (mod/i) * inv[mod%i] % mod;
    int n = a.size();
    int m = a[0].size();
    vector<int> w(m, -1); // i번째 열에 있는 pivot이 몇 번째 행에 있는지 저장
    for(int c = 0, r = 0; c < m && r < n; ++c){
        int p = r; // pivot row
        for(int i = r; i < n; ++i)
            if(a[p][c] < a[i][c])
                p = i;
        if(a[p][c] == 0) continue; // free variable
        for(int j = 0; j < m; ++j)
            swap(a[p][j], a[r][j]);
        w[c] = r;
        int t = a[r][c];
        for(int j = 0; j < m; ++j)
            a[r][j] = a[r][j] * inv[t] % mod;
        for(int i = 0; i < n; ++i) if(i != r){
            int t = a[i][c];
            for(int j = c; j < m; ++j)
                a[i][j] = (a[i][j] - a[r][j] * t % mod + mod) % mod;
        }
        ++r;
    }
    for(int i = 0; i < n; ++i) // existence of solution
        if(count(a[i].begin(), --a[i].end(), 0) == m-1 && a[i][m-1])
            return vector<int>(); // no solution
    vector<int> ans(m);
    for(int i = 0; i < m; ++i)
        if(~w[i]) ans[i] = a[w[i]][m-1];
    return ans; // solution exist
}
// Gauss-Jordan Elimination modulo 2
const int sz = 500;
bitset<sz> gauss_bit(vector<bitset<sz>> &a){
    int n = a.size();
    int m = a[0].size();
    vector<int> w(m, -1);
    for(int c = 0, r = 0; c < m && r < n; ++c){
        for(int i = r; i < n; ++i)
            if(a[i][c]){
                swap(a[i],a[r]);
                break;
            }
        if(a[r][c] == 0) continue;
        w[c] = r;
        for(int i = 0; i < n; ++i) if(i != r)
            if(a[i][c]) a[i] ^= a[r];
        ++r;
    }
    // .. same
}