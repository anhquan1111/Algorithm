#include <bits/stdc++.h>

using namespace std;

const int mod  = 1e9;

using type = int;

struct Matrix {
    vector <vector <type> > data;

    int row() const { return data.size(); }

    int col() const { return data[0].size(); }

    auto & operator [] (int i) { return data[i]; }

    const auto & operator[] (int i) const { return data[i]; }

    Matrix() = default;

    Matrix(int r, int c): data(r, vector <type> (c)) { }

    Matrix(const vector <vector <type> > &d): data(d) { }

    friend ostream & operator << (ostream &out, const Matrix &d) {
        for (auto x : d.data) {
            for (auto y : x) out << y << ' ';
            out << '\n';
        }
        return out;
    }

    static Matrix identity(long long n) {
        Matrix a = Matrix(n, n);
        while (n--) a[n][n] = 1;
        return a;
    }

    Matrix operator * (const Matrix &b) {
        Matrix a = *this;
        assert(a.col() == b.row());
        Matrix c(a.row(), b.col());
        for (int i = 0; i < a.row(); ++i)
            for (int j = 0; j < b.col(); ++j)
                for (int k = 0; k < a.col(); ++k){
                    c[i][j] += 1ll * a[i][k] % mod * (b[k][j] % mod) % mod;
                    c[i][j] %= mod;
                }
        return c;
    }

    Matrix pow(long long exp) {
        assert(row() == col());
        Matrix base = *this, ans = identity(row());
        for (; exp > 0; exp >>= 1, base = base * base)
            if (exp & 1) ans = ans * base;
        return ans;
    }
};

int b[15], c[15];

int main(){
    int t;
    cin >> t;
    while (t--) {
        int n, k;
        cin >> k;
        for (int i = 1; i <= k; ++i) cin >> b[i];
        for (int i = 1; i <= k; ++i) cin >> c[i];
        cin >> n;

        if (n <= k) { cout << b[n] << '\n'; continue; }

        // Xây dựng ma trận cơ sở
        Matrix base(k, 1);
        for (int i = 1; i <= k; ++i) base[i - 1][0] = b[i];

        // Xây dựng ma trận hệ số D
        Matrix d(k, k);
        for (int i = 0; i < k - 1; ++i) d[i][i + 1] = 1;
        for (int i = 0; i < k; ++i) d[k - 1][i] = c[k - i];

        Matrix ans = d.pow(n - k) * base;
        cout << ans[k - 1][0] << '\n';
    }
}
