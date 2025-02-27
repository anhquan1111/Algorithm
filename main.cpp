#include <iostream>
#include <vector>
using namespace std;

int n;
vector<int> bit1, bit2, A;

/*
    Các hàm update và sum cần làm việc trên một trong hai BIT riêng biệt.
    Sử dụng vector cho phép truyền BIT vào làm việc trực tiếp dễ dàng hơn.
*/

void updatePoint(vector<int>& b, int u, int v) {
    int idx = u;
    while (idx <= n) {
        b[idx] += v;
        idx += (idx & (-idx));
    }
}

void updateRange(int l, int r, int v) {
    updatePoint(bit1, l, (n - l + 1) * v);
    updatePoint(bit1, r + 1, -(n - r) * v);
    updatePoint(bit2, l, v);
    updatePoint(bit2, r + 1, -v);
}

int getSumOnBIT(vector<int>& b, int u) {
    int idx = u, ans = 0;
    while (idx > 0) {
        ans += b[idx];
        idx -= (idx & (-idx));
    }
    return ans;
}

int prefixSum(int u) {
    return getSumOnBIT(bit1, u) - getSumOnBIT(bit2, u) * (n - u);
}

int rangeSum(int l, int r) {
    return prefixSum(r) - prefixSum(l - 1);
}

int main() {
    // Nhập số phần tử của mảng
    cout << "Nhap so phan tu n: ";
    cin >> n;

    A.resize(n + 1);
    bit1.resize(n + 1, 0);
    bit2.resize(n + 1, 0);

    // Nhập mảng A (chỉ số bắt đầu từ 1)
    cout << "Nhap mang A voi " << n << " phan tu: ";
    for (int i = 1; i <= n; i++) {
        cin >> A[i];
    }

    // Khởi tạo BIT bằng cách cập nhật từng phần tử của A
    for (int i = 1; i <= n; i++) {
        updateRange(i, i, A[i]);
    }

    int q;
    for(int x:bit1){
        cout<<x<<" ";
    }
    cout<<endl;
    for(int x:bit2){
        cout<<x<<" ";
    }
    cout<<endl;
    cout << "Nhap so luong truy van: ";
    cin >> q;
    while (q--) {
        int type;
        cout << "Nhap truy van: ";
        cin >> type;
        if (type == 1) { // Query range sum
            int l, r;
            cin >> l >> r;
            cout << "Tong doan [" << l << ", " << r << "] = " << rangeSum(l, r) << endl;
        } else if (type == 2) { // Update range
            int l, r, v;
            cin >> l >> r >> v;
            updateRange(l, r, v);
            cout << "Da cap nhat doan [" << l << ", " << r << "] voi gia tri cong them " << v << endl;
        } else {
            cout << "Loai truy van khong hop le!" << endl;
        }
    }

    return 0;
}
