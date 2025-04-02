#include <bits/stdc++.h>
using namespace std;
struct Matrix{
    vector<vector<int>>data;
    // Số lượng hàng của ma trận
    int row () const{
        return data.size();
    }
    // Số lượng cột của ma trận
    int col () const{
        return data[0].size();
    }
    // Nạp chồng toán tử [] để truy vấn vector hàng i
    auto & operator [] (int i){
        return data[i];
    }
    const auto & operator [] (int i) const {
        return data[i];
    }
    // Constructor mặc định
    Matrix() = default;
    // Constructor có tham số
    Matrix(int r,int c) : data(r,vector<int>(c)){}
    // Constructor bỏ sẵn vector và Kiểm tra các hàng có cùng size ko
    Matrix(vector<vector<int>>d):data(d){
    } 
    // Nạp chồng toán tử in
    friend ostream& operator << (ostream& out, const Matrix &d){
        for(auto x:d.data){
            for(auto y:x){
                out<<y<<" ";
            }
            out<<endl;
        }
        return out;
    }
    // Ma trận đơn vị
    static Matrix identity(long long n){
        auto ans = Matrix(n,n);
        while(n--){
            ans[n][n]=1;
        }
        return ans;
    }
    //Nhân ma trận
    Matrix operator * (const Matrix &b){
        Matrix a = *this;
        if(a.col()!=b.row()){
            cout<<"Error: Col != Row"<<endl;
        }
        Matrix c = Matrix(a.row(),b.col());
        for(int i=0;i<a.row();i++){
            for(int j=0;j<b.col();j++){
                for(int k=0;k<a.col();k++){
                    c[i][j] += a[i][k]*b[k][j];
                }
            }
        }
        return c;
    }
    // Lũy thừa ma trận
    Matrix pow(long long exp){
        Matrix base = *this;
        Matrix ans = identity(base.row());
        while(exp>0){
            if(exp%2==1){
                ans = ans * base;
            }
            base = base * base;
            exp /= 2;
        }
        return ans;
    }
};
int main(){
    Matrix a({
        {1, 2},
        {3, 4}
    });

    Matrix b({
        {0, 10, 100},
        {1,  1,  10}
    });

    cout << a * b << '\n';
    // 2 12 120
    // 4 34 340

    cout << a.pow(3) << '\n';
    // 37 54
    // 81 118

    b = a;
    cout << b << '\n';
    // 1 2
    // 3 4

    b = Matrix::identity(3);
    cout << b << '\n';
    // 1 0 0
    // 0 1 0
    // 0 0 1

    b = Matrix(2, 3);
    cout << b << '\n';
    // 0 0 0
    // 0 0 0

    Matrix c(3, 2);
    cout << c << '\n';
    // 0 0
    // 0 0
    // 0 0
}
