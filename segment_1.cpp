#include <bits/stdc++.h>

using namespace std;

const int inf  = 1e9 + 7;
const int maxN = 1e5 + 7;

int n, q;
int a[maxN];
int st[4 * maxN]; // Lí do sử dụng kích thước mảng là 4 * maxN sẽ được giải thích ở phần sau

// Thủ tục xây dựng cây phân đoạn
void build(int id, int l, int r) {
    // Đoạn chỉ gồm 1 phần tử, không có nút con
    if (l == r) {
        st[id] = a[l];
        return;
    }

    // Gọi đệ quy để xử lý các nút con của nút id
    int mid = l + r >> 1; // (l + r) / 2
    build(2 * id, l, mid);
    build(2 * id + 1, mid + 1, r);

    // Cập nhật lại giá trị min của đoạn [l, r] theo 2 nút con
    st[id] = min(st[2 * id], st[2 * id + 1]);
}

// Thủ tục cập nhật
void update(int id, int l, int r, int i, int val) {
    // i nằm ngoài đoạn [l, r], ta bỏ qua nút id
    if (l > i || r < i) return;

    // Đoạn chỉ gồm 1 phần tử, không có nút con
    if (l == r) {
        st[id] = val;
        return;
    }

    // Gọi đệ quy để xử lý các nút con của nút id
    int mid = l + r >> 1; // (l + r) / 2
    update(2 * id, l, mid, i, val);
    update(2 * id + 1, mid + 1, r, i, val);

    // Cập nhật lại giá trị min của đoạn [l, r] theo 2 nút con
    st[id] = min(st[2 * id], st[2 * id + 1]);
}


// Hàm lấy giá trị
int get(int id, int l, int r, int u, int v) {
    // Đoạn [u, v] không giao với đoạn [l, r], ta bỏ qua đoạn này
    if (l >  v || r <  u) return inf;

    /* Đoạn [l, r] nằm hoàn toàn trong đoạn [u, v] mà ta đang truy vấn,
        ta trả lại thông tin lưu ở nút id */
    if (l >= u && r <= v) return st[id];

    // Gọi đệ quy với các nút con của nút id
    int mid = l + r >> 1; // (l + r) / 2
    int get1 = get(2 * id, l, mid, u, v);
    int get2 = get(2 * id + 1, mid + 1, r, u, v);

    // Trả ra giá trị nhỏ nhất theo 2 nút con
    return min(get1, get2);
}

int main() {
    cin >> n;
    for (int i = 1; i <= n; ++i) cin >> a[i];
    build(1, 1, n);

    cin >> q;
    while (q--) {
        int type, x, y;
        cin >> type >> x >> y;
        if (type == 1) update(1, 1, n, x, y); // Gán giá trị y cho phần tử ở vị trí x
        else cout << get(1, 1, n, x, y) << '\n'; // In ra giá trị nhỏ nhất trong đoạn [x, y]
    }
}
// #include <bits/stdc++.h>
// using namespace std;
// int n;
// int a[100];
// int st[100];
// void taoCay(int index,int l,int r){
//     if(l==r){
//         st[index]=a[l];
//         return;
//     }
//     int m = (l+r)>>1;
//     taoCay(index*2,l,m);
//     taoCay(index*2+1,m+1,r);
//     st[index]=min(st[index*2],st[index*2+1]);
// }
// void update(int index,int l,int r,int i,int value){
//     if(l>i || r<i){
//         return;
//     }
//     if(l==r){
//         st[index]=value;
//         return;
//     }
//     int m =(l+r)>>1;
//     update(index*2,l,m,i,value);
//     update(index*2+1,m+1,r,i,value);
//     st[index]=min(st[index*2],st[index*2+1]);
// }
// int giaTriNhoNhat(int index,int l,int r,int u,int v){
//     if(l>v || r<u){
//         return INT_MAX;
//     }
//     if(l>=u && r<=v){
//         return st[index];
//     }
//     int m = (l+r)>>1;
//     int get1 = giaTriNhoNhat(index*2,l,m,u,v);
//     int get2 = giaTriNhoNhat(index*2+1,m+1,r,u,v);
//     return min(get1,get2);
// }
// int main(){
//     cout<<"Nhap n: ";
//     cin>>n;
//     cout<<"Nhap gia tri a[i]: ";
//     for(int i=1;i<=n;i++){
//         cin>>a[i];
//     }
//     taoCay(1,1,n);
//     int q;
//     cout<<"Nhap so luong truy van: ";
//     cin>>q;
//     while(q--){
//         cout<<"1. Thay doi gia tri a[i]=value "<<endl;
//         cout<<"2. Gia tri min trong doan u -> v "<<endl;
//         cout<<"3. Xem mang "<<endl;
//         cout<<"4. Ket thuc "<<endl;
//         cout<<"Nhap lua chon: ";
//         int choose;
//         cin>>choose;
//         if(choose==1){
//             int i,value;
//             cout<<"Nhap i: ";
//             cin>>i;
//             cout<<"Nhap value: ";
//             cin>>value;
//             a[i]=value;
//             update(1,1,n,i,value);
//             cout<<"Da thay doi thanh cong";
//             cout<<endl;
//         }
//         if(choose==2){
//             int u,v;
//             cout<<"Nhap u,v: ";
//             cin>>u>>v;
//             cout<<"Gia tri min la: "<<giaTriNhoNhat(1,1,n,u,v)<<endl;
//         }
//         if(choose==3){
//             cout<<"Mang a[i]: ";
//             for(int i=1;i<=n;i++){
//                 cout<<a[i]<<" ";
//             }
//             cout<<endl;
//         }
//         if(choose==4){
//             break;
//         }
//     }
// }
