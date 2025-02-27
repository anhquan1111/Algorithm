#include <bits/stdc++.h>
using namespace std;

#define _(x) (x & (-(x)))  // Lấy bit phải nhất của x
vector< pair<int, int> > bit[4100][4100]; // Persistent 2D BIT

// Cập nhật giá trị tại (x, y) tại thời điểm time
void update(int x, int y, int val, int time) {
    for(int u = x; u <= 4096; u += _(u))
        for(int v = y; v <= 4096; v += _(v)) {
            if (bit[u][v].empty()) {
                bit[u][v].push_back(make_pair(time, val));
            }
            else {
                int cur = bit[u][v].back().second;
                bit[u][v].push_back(make_pair(time, cur + val));
            }
        }
}

// Lấy tổng từ (1,1) đến (x, y) tại thời điểm time
int get(int time, int x, int y) {
    int res = 0;
    for(int u = x; u > 0; u -= _(u))
        for(int v = y; v > 0; v -= _(v)) {
            if (!bit[u][v].empty()) {
                if (bit[u][v].back().first <= time) {
                    res += bit[u][v].back().second;
                }
                else {
                    int pos = upper_bound(bit[u][v].begin(), bit[u][v].end(), make_pair(time, 2000111000))
                            - bit[u][v].begin() - 1;
                    if (pos >= 0)
                        res += bit[u][v][pos].second;
                }
            }
        }
    return res;
}

// Chương trình chính
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    // Thêm giá trị vào ma trận
    update(2, 3, 5, 1);  // Thêm 5 vào (2, 3) tại thời điểm 1
    update(2, 3, 2, 2);  // Thêm 2 vào (2, 3) tại thời điểm 2
    update(4, 4, 10, 3); // Thêm 10 vào (4, 4) tại thời điểm 3

    // Truy vấn tổng tại các thời điểm khác nhau
    cout << "Sum (1,1) -> (4,4) at time 1: " << get(1, 4, 4) << endl;
    cout << "Sum (1,1) -> (4,4) at time 2: " << get(2, 4, 4) << endl;
    cout << "Sum (1,1) -> (4,4) at time 3: " << get(3, 4, 4) << endl;

    return 0;
}
