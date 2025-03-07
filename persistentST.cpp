#include <bits/stdc++.h>
using namespace std;

const long long infty = 1e18 + 7;
const int MAXN = 3e5 + 5;

int n;
int a[MAXN];

// val: giá trị của node i
// le, ri: các node con của node i
long long val[MAXN * 20];
int le[MAXN * 20], ri[MAXN * 20];

// root_idx[i]: node gốc được tạo ra ở query thứ i
int root_idx[MAXN];

// cur[id]: node chứa version mới nhất của node id trong segment tree ban đầu
int cur[MAXN * 20];

// tol_node lưu tổng số node hiện tại
int tolnode;

long long init(int id, int l, int r){
    tolnode++;
    cur[id] = id;
    if(l == r){
        val[id] = a[l];
        return a[l];
    }
    le[id] = (id << 1), ri[id] = (id << 1 | 1);
    int mid = (l + r) >> 1;
    long long sum = init(id << 1, l, mid) + init(id << 1 | 1, mid + 1, r);
    val[id] = sum;
    return sum;
}

void upd(int id, int l, int r, int pos, long long v){
    if(l == r){
        tolnode++;
        val[tolnode] = v;
        cur[id] = tolnode;
        return;
    }
    tolnode++;
    int nw_id = tolnode;
    cur[id] = nw_id;
    cout<<"cur "<<id<<": "<< cur[id]<<endl;
    int mid = (l + r) >> 1;
    if(pos <= mid){
        upd(id << 1, l, mid, pos, v);
        le[nw_id] = nw_id + 1;
        ri[nw_id] = cur[id << 1 | 1];
        val[nw_id] = val[le[nw_id]] + val[ri[nw_id]];
    }
    else{
        upd(id << 1 | 1, mid + 1, r, pos, v);
        le[nw_id] = cur[id << 1];
        ri[nw_id] = nw_id + 1;
        val[nw_id] = val[le[nw_id]] + val[ri[nw_id]];
    }
}

long long get(int id, int l, int r, int L, int R){
    if(R < l || r < L) return 0;
    if(l >= L && r <= R) return val[id];
    int mid = (l + r) >> 1;
    return get(le[id], l, mid, L, R) + get(ri[id], mid + 1, r, L, R);
}

int cnt_que;

void update(int p, long long v){
    cnt_que++;
    root_idx[cnt_que] = tolnode + 1;
    upd(1, 1, n, p, v);
}

long long ans(int l, int r, int k){
    return get(root_idx[k], 1, n, l, r);
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    // Nhập số phần tử
    cin >> n;
    for(int i = 1; i <= n; i++) cin >> a[i];

    // Khởi tạo segment tree ban đầu
    root_idx[0] = 1;
    tolnode = 1;
    init(1, 1, n);
    cout<<"tolnode: "<<tolnode<<endl;

    int q;
    cin >> q; // Số truy vấn

    while(q--) {
        int type;
        cin >> type;
        if(type == 1) { // Cập nhật a[pos] = v
            int pos;
            long long v;
            cin >> pos >> v;
            update(pos, v);
            cout<<"tolnode: "<<tolnode<<endl;
        }
        else if(type == 2) { // Truy vấn tổng đoạn [l, r] tại thời điểm k
            int l, r, k;
            cin >> l >> r >> k;
            cout << ans(l, r, k) << "\n";
            cout<<"tolnode: "<<tolnode<<endl;
        }
    }

    return 0;
}
