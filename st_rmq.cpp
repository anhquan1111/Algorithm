#include <bits/stdc++.h>
using namespace std;
int a[100];
int st[50][50];
int n;
void prepprocess(){
    for(int i=1;i<=n;i++){
        st[0][i]=a[i];
    }
    int tmp = (int)floor(log2(n));
    for(int j=1;j<=tmp;j++){
        for(int i=1;i<=n-(1<<j)+1;i++){
            st[j][i]=min(st[j-1][i],st[j-1][i+(1<<(j-1))]);
        }
    }
}
int process(int l,int r){
    int k = int(floor(log2(r-l+1)));
    return min(st[k][l],st[k][r-(1<<k)+1]);
}
void print(){
    int tmp = (int)floor(log2(n));
    for(int j=1;j<=tmp;j++){
        for(int i=1;i<=n-(1<<j)+1;i++){
            cout<<st[j][i]<<" ";
        }
        cout<<endl;
    }
}
// code này chạy từ 1 -> N
int main(){
    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>a[i];
    }
    prepprocess();
    print();
    int q;
    cin>>q;
    while(q--){
        int l,r;
        cin>>l>>r;
        cout<<process(l,r)<<endl;
    }
}
