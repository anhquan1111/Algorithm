#include <bits/stdc++.h>

using namespace std;

const int mod = 10;

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

    // Phép trừ ma trận
    Matrix operator - (const Matrix &b) {
        Matrix a = *this;

        // Kiểm tra điều kiện phép trừ ma trận
        assert(a.row() == b.row() && a.col() == b.col());

        for (int i = 0; i < a.row(); ++i)
            for (int j = 0; j < a.col(); ++j)
                a[i][j] = (a[i][j] - b[i][j] + mod) % mod;
        return a;
    }

    Matrix operator * (const Matrix &b) {
        Matrix a = *this;
        assert(a.col() == b.row());
        Matrix c(a.row(), b.col());
        for (int i = 0; i < a.row(); ++i)
            for (int j = 0; j < b.col(); ++j)
                for (int k = 0; k < a.col(); ++k){
                    c[i][j] += a[i][k] % mod * (b[k][j] % mod) % mod;
                    c[i][j] %= mod;
                }
        return c;
    }
};

mt19937 rd(chrono::steady_clock::now().time_since_epoch().count());

int random(int l, int r) { return l + rd() % (r - l + 1); }

bool check(Matrix a, Matrix b, Matrix c, int n) {
    int k = 5;
    while (k--) {
        Matrix v(n, 1);
        for (int i = 0; i < n; ++i) v[i][0] = random(0, 1);
        Matrix p = (a * (b * v)) - (c * v);
        for (int i = 0; i < n; ++i)
            if (p[i][0]) return false;
    }
    return true;
}

int main(){
    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        Matrix a(n, n), b(n, n), c(n, n);
        for (int i = 0; i < 3 * n; ++i) {
            string s;
            cin >> s;
            for (int j = 0; j < s.size(); ++j) {
                if (i / n == 0) a[i][j] = s[j] - '0';
                if (i / n == 1) b[i - n][j] = s[j] - '0';
                if (i / n == 2) c[i - n - n][j] = s[j] - '0';
            }
        }

        if (check(a, b, c, n)) cout << "YES\n";
        else cout << "NO\n";
    }
}
