#include <bits/stdc++.h>
using namespace std;

// Tránh xung đột với biến y1 trong C++
#define y1 y11  

const long long infty = 1e18 + 7;
const int MAXN = 3e3 + 5;

// Kích thước bảng
int N, M;

int a[MAXN][MAXN];

vector<pair<int, long long>> updates[MAXN][MAXN];

// Mảng tính tổng prefix sum
long long pref[MAXN][MAXN];
int range[MAXN];

void init() {
    // Xác định khoảng mà vị trí i quản lý trong BIT
    for (int i = 1; i <= max(N, M); i++) {
        range[i] = (i & (i - 1)) + 1;
    }

    // Sử dụng prefix sum để khởi tạo giá trị ban đầu
    for (int i = 1; i <= N; i++) {
        for (int j = 1; j <= M; j++) {
            pref[i][j] = a[i][j] + pref[i - 1][j] + pref[i][j - 1] - pref[i - 1][j - 1];
        }
    }

    // Đưa giá trị ban đầu vào updates
    // Startval = tổng từ a[x1->x2][y1->y2]
    for (int i = 1; i <= N; i++) {
        for (int j = 1; j <= M; j++) {
            int x1 = range[i], y1 = range[j], x2 = i, y2 = j;
            long long startval = pref[x2][y2] - pref[x1 - 1][y2] - pref[x2][y1 - 1] + pref[x1 - 1][y1 - 1];
            updates[i][j].push_back({0, startval});
            // cout<<startval<<" ";
        }
        // cout<<endl;
    }
    // updates tương tự như BIT 2D
}
// a[x][y]+=val
void upd(int x, int y, int k, long long val) {
    for (int i = x; i <= N; i += i & -i) {
        for (int j = y; j <= M; j += j & -j) {
            long long lst = updates[i][j].back().second;
            lst += val;
            updates[i][j].push_back({k, lst});
        }
    }
}

// Truy vấn tổng từ (1,1) đến (x,y) tại thời điểm k
long long get(int x, int y, int k) {
    long long ans = 0;
    for (int i = x; i; i -= i & -i) {
        for (int j = y; j; j -= j & -j) {
            int pos = lower_bound(updates[i][j].begin(), updates[i][j].end(), make_pair(k, infty)) - updates[i][j].begin() - 1;
            ans += updates[i][j][pos].second;
        }
    }
    return ans;
}

// Truy vấn tổng giá trị của hình chữ nhật từ (x1, y1) đến (x2, y2) tại thời điểm k
long long ans(int x1, int y1, int x2, int y2, int k) {
    return get(x2, y2, k) - get(x1 - 1, y2, k) - get(x2, y1 - 1, k) + get(x1 - 1, y1 - 1, k);
}

int main() {
    // Nhập kích thước bảng và số truy vấn
    int Q;
    cout<<"Nhap n,m: ";
    cin >> N >> M;
  
    // Nhập mảng ban đầu
    for (int i = 1; i <= N; i++) {
        cout<<"Nhap hang "<<i<<": ";
        for (int j = 1; j <= M; j++) {
            cin >> a[i][j];
        }
    }

    // Khởi tạo BIT
    init();
    cout<<"Nhap so truy van: ";
    cin>>Q;

    // Xử lý các truy vấn
    for (int i = 0; i < Q; i++) {
        int type;
        cout<<"1. Cap nhat a[x][y]+=value"<<endl;
        cout<<"2.Truy van tong a[x1->x2][y1->y2]"<<endl;
        cout<<"Nhap lua chon: ";
        cin >> type;

        if (type == 1) { // Cập nhật giá trị tại (x, y) với giá trị val tại thời điểm k
            cout<<"Nhap x,y,value: ";
            int x, y,k;
            long long val;
            cin >> x >> y >> val;
            cout<<"Nhap k";
            cin>>k;
            upd(x, y, k, val);
        } else if (type == 2) { // Truy vấn hình chữ nhật (x1, y1) đến (x2, y2) tại thời điểm k
            cout<<"Nhap x1,y1,x2,y2: ";
            int x1, y1, x2, y2,k;
            cin >> x1 >> y1 >> x2 >> y2;
            cout<<"Nhap k: ";
            cin>>k;
            cout<<"Tong: ";
            cout << ans(x1, y1, x2, y2, k) << '\n';
        }
    }

    return 0;
}
