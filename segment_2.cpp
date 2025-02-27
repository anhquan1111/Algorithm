#include <bits/stdc++.h>

using namespace std;

const int maxN = 1e5 + 7;

int n, q;
int a[maxN];
long long st[4 * maxN];

// Thủ tục cập nhật
void update(int id, int l, int r, int i, int val) {
    if (l > i || r < i) return;
    if (l == r) {
        st[id] = val;
        return;
    }
    int mid = l + r >> 1;
    update(2 * id, l, mid, i, val);
    update(2 * id + 1, mid + 1, r, i, val);
    st[id] = st[2 * id] + st[2 * id + 1];
}

// Hàm lấy tổng giá trị
long long get(int id, int l, int r, int u, int v) {
    if (l >  v || r <  u) return 0;
    if (l >= u && r <= v) return st[id];

    int mid = l + r >> 1;
    long long get1 = get(2 * id, l, mid, u, v);
    long long get2 = get(2 * id + 1, mid + 1, r, u, v);
    return get1 + get2;
}

int main() {
    cin >> n >> q;
    while (q--){
        int type, x, y;
        cin >> type >> x >> y;
        if (type == 1) update(1, 1, n, x, y);
        else cout << get(1, 1, n, x, y) << '\n';
    }
}
