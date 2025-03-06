#include <bits/stdc++.h>
using namespace std;
const int N = 1e5;  // giới hạn của mảng
int n;  // kích thước mảng
int t[2 * N];

void build() {  // khởi tạo cây
  for (int i = n - 1; i > 0; --i)
    t[i] = t[i<<1] + t[i<<1|1];
}

void modify(int p, int value) {  // gán giá trị tại vị trí p
  for (t[p += n] = value; p > 1; p >>= 1)
    cout<<p<<endl;
    t[p>>1] = t[p] + t[p^1];
}
// bắt đầu từ 0
int query(int l, int r) {  // tính tổng đoạn [l, r)
  int res = 0;
  for (l += n, r += n; l < r; l >>= 1, r >>= 1) {
    if (l&1) res += t[l++];
    if (r&1) res += t[--r];
  }
  return res;
}

int main() {
  scanf("%d", &n);
  for (int i = 0; i < n; ++i) scanf("%d", t + n + i);
  build();
  for(int i = 0;i<n*2;i++){
    cout<<t[i]<<" ";
  }
  modify(0, 1);
  cout<<endl;
  for(int i = 0;i<n*2;i++){
    cout<<t[i]<<" ";
  }
  cout<<endl;
  int q;
  cin>>q;
  while(q--){
    int l,r;
    cin>>l>>r;
    cout<<query(l,r)<<endl;
  }
  return 0;
}
