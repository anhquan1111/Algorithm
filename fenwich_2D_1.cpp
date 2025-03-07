#include <bits/stdc++.h>
using namespace std;

const int N = 1005, M = 1005; // Giới hạn tối đa của mảng
int a[10][10];
int BIT[N][M]; // Cây BIT 2D để quản lý cập nhật và truy vấn
int n, m, q;   // Kích thước ma trận và số truy vấn

// Cập nhật giá trị tại (u, v) với x
void add(int u, int v, int x) {
    for (int i = u; i <= n; i += i & (-i)) {
        for (int j = v; j <= m; j += j & (-j)) {
            BIT[i][j] += x;
        }
    }
}

// Truy vấn tổng từ (1,1) đến (u,v)
int query(int u, int v) {
    int sum = 0;
    for (int i = u; i > 0; i -= i & (-i)) {
        for (int j = v; j > 0; j -= j & (-j)) {
            cout<<i<<" "<<j<<":";
            sum += BIT[i][j];
            cout<<endl;
        }
    }
    return sum;
}

// Truy vấn tổng từ (1,1) đến (u,v)
int sumRegion(int u, int v) {
    return query(u, v);
}

int main() {
    cout<<"Nhap n,m: ";
    cin >> n >> m;
    for(int i=1;i<=n;i++){
      cout<<"Nhap hang "<<i<<": ";
      for(int j=1;j<=m;j++){
        cin>>a[i][j];
        add(i,j,a[i][j]);
      }
    }
    cout<<"Bit 2D:"<<endl;
    for(int i=1;i<=n;i++){
      cout<<"Hang "<<i<<": ";
      for(int j=1;j<=m;j++){
        cout<<BIT[i][j]<<" ";
      }
      cout<<endl;
    }
    cout<<sumRegion(2,3);

    // while (q--) {
    //     int type;
    //     cin >> type;

    //     if (type == 1) { // Truy vấn cập nhật
    //         int u, v, x;
    //         cin >> u >> v >> x;
    //         add(u, v, x);
    //     } else if (type == 2) { // Truy vấn tổng
    //         int u, v;
    //         cin >> u >> v;
    //         cout << sumRegion(u, v) << "\n";
    //     }
    // }

    // return 0;
}
