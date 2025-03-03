#include <bits/stdc++.h>

using namespace std;

const int maxN = 1e5 + 7;

int n, q;
string s;
int cnt[30];
int st[30][4 * maxN], lazy[30][4 * maxN];

void build(int id, int l, int r) {
    // Khởi tạo giá trị mảng lazy ban đầu bằng -1
    for (int ch = 0; ch <= 25; ++ch) lazy[ch][id] = -1;

    if (l == r) {
        st[s[l - 1] - 'a'][id] = 1;
        return;
    }
    int mid = l + r >> 1;
    build(2 * id, l, mid);
    build(2 * id + 1, mid + 1, r);
    for (int ch = 0; ch <= 25; ++ch)
        st[ch][id] = st[ch][2 * id] + st[ch][2 * id + 1];
}

void fix(int id, int l, int r, int ch) {
    if (lazy[ch][id] == -1) return;
    st[ch][id] = lazy[ch][id] * (r - l + 1);
    if (l != r){

        /* Vì là thao tác gán giá trị chứ KHÔNG phải là tăng thêm một lượng
        nên lazy của nút con sẽ gán bằng lazy của nút cha */
        lazy[ch][2 * id] = lazy[ch][id];
        lazy[ch][2 * id + 1] = lazy[ch][id];
    }
    lazy[ch][id] = -1;
}

void update(int id, int l, int r, int u, int v, int val, int ch) {
    fix(id, l, r, ch);
    if (l >  v || r <  u) return;
    if (l >= u && r <= v) {
        lazy[ch][id] = val;
        fix(id, l, r, ch);
        return;
    }
    int mid = l + r >> 1;
    update(2 * id, l, mid, u, v, val, ch);
    update(2 * id + 1, mid + 1, r, u, v, val, ch);
    st[ch][id] = st[ch][2 * id] + st[ch][2 * id + 1];
}

int get(int id, int l, int r, int u, int v, int ch) {
    fix(id, l, r, ch);
    if (l >  v || r <  u) return 0;
    if (l >= u && r <= v) return st[ch][id];

    int mid  = l + r >> 1;
    int get1 = get(2 * id, l, mid, u, v, ch);
    int get2 = get(2 * id + 1, mid + 1, r, u, v, ch);
    return get1 + get2;
}

int main() {
    cin >> n >> q;
    cin >> s;
    build(1, 1, n);

    while (q--) {
        int i, j, k;
        cin >> i >> j >> k;

        for (int ch = 0; ch <= 25; ++ch) {
            cnt[ch] = get(1, 1, n, i, j, ch);
            update(1, 1, n, i, j, 0, ch);
        }

        int ch = (k ? 0 : 25), l = i;
        while (0 <= ch && ch <= 25) {
            if (cnt[ch]) {
                update(1, 1, n, l, l + cnt[ch] - 1, 1, ch);
                l += cnt[ch];
            }
            ch += (k ? 1 : -1);
        }
    }

    // In ra đáp án
    for (int i = 1; i <= n; ++i)
        for (int ch = 0; ch <= 25; ++ch)
            if (get(1, 1, n, i, i, ch)) {
                cout << (char)(ch + 'a');
                break;
            }
}
