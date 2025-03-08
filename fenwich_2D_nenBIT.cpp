#include <bits/stdc++.h>
using namespace std;

const int N = 1005;  // Giới hạn tối đa cho n và m
int n, m, q;

vector<int> pos[N];  // Lưu danh sách tọa độ đã xuất hiện (dùng để nén tọa độ)
vector<int> BIT[N];  // Fenwick Tree 2D

// Ghi nhận tọa độ cần nén
void fakeAdd(int u, int v) {
    for (int i = u; i <= n; i += i & (-i)) {
        pos[i].push_back(v);
    }
}

void fakeQuery(int u, int v){
  for(u; u > 0; u -= u&(-u)){
      pos[u].push_back(v);
  }
}
// Nén tọa độ cho từng dòng của BIT
void compress() {
    for (int i = 1; i <= n; i++) {
        pos[i].push_back(0);  // Thêm giá trị 0 để tránh lỗi lower_bound
        sort(pos[i].begin(), pos[i].end());
        pos[i].erase(unique(pos[i].begin(), pos[i].end()), pos[i].end());
        BIT[i].assign(pos[i].size(), 0);
    }
}

// Cập nhật BIT tại (u, v) với giá trị x
void add(int u, int v, int x) {
    for (int i = u; i <= n; i += i & (-i)) {
      // cú pháp lower_bound - begin() là để trỏ đến index >= value đầu tiên
        int j = lower_bound(pos[i].begin(), pos[i].end(), v) - pos[i].begin();
        cout<<"j la: ";
        cout<<j<<endl;
        for (; j < BIT[i].size(); j += j & (-j)) {
            BIT[i][j] += x;
        }
    }
}
// Truy vấn tổng từ (1,1) đến (u,v)
int query(int u, int v) {
    int sum = 0;
    for (int i = u; i > 0; i -= i & (-i)) {
        int j = lower_bound(pos[i].begin(), pos[i].end(), v) - pos[i].begin();
        for (; j > 0; j -= j & (-j)) {
            sum += BIT[i][j];
        }
    }
    return sum;
}

// Truy vấn hình chữ nhật từ (x1, y1) đến (x2, y2)
int rangeQuery(int x1, int y1, int x2, int y2) {
    return query(x2, y2) - query(x1 - 1, y2) - query(x2, y1 - 1) + query(x1 - 1, y1 - 1);
}

// Bài này thực hiện khi mảng fill(0) nếu muốn nhập mảng thì phải compress nhiều lần sẽ gây tràn
int main() {

    // Nhập số hàng, cột và số truy vấn
    cout<<"Nhap n,m: ";
    cin >> n >> m;
    cout<<"Nhap so truy van: ";
    cin>>q;

    vector<tuple<int, int, int, int>> queries;  // Lưu truy vấn để xử lý sau

    for (int i = 0; i < q; i++) {
        int type, u, v, x = 0;
        cin >> type >> u >> v;
        if (type == 1) {
            cin >> x;  // Truy vấn cập nhật
            fakeAdd(u, v);
        }
        else{
            fakeQuery(u,v);
        }
        queries.push_back({type, u, v, x});
    }

    // Xử lý nén tọa độ
    compress();

    // Thực hiện truy vấn
    for (auto [type, u, v, x] : queries) {
        if (type == 1) {
            add(u, v, x);
        } else if (type == 2) {
            cout << query(u, v) << '\n';
        }
    }

    return 0;
}
