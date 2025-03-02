#include <bits/stdc++.h>
using namespace std;
int bit[100];
int n;
int a[100];
void tinhBit(){
    for(int i=1;i<=n;i++){
        int tmp = i & ~(i-1);
        if(tmp==i){
            for(int j=1;j<=i;j++){
                bit[i]+=a[j];
            }
        }
        else{
            for(int j=i-tmp+1;j<=i;j++){
                bit[i]+=a[j];
            }
        }
    }
}
// tổng từ 1 -> p
int tinhTong(int p){
    int index = p;
    int ans=0;
    while(index>0){
        ans+=bit[index];
        index-=(index & ~(index-1));
    }
    return ans;
}

// cộng giá trị a[u] thêm v
void congThem(int u,int v){
    int index = u;
    while(index<=n){
        bit[index]+=v;
        index+=(index & ~(index-1));
    }
}

int main(){
    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>a[i];
    }
    tinhBit();
    int t;
    cin>>t;
    while(t--){      
        cout<<"1. Tinh Tong Tu 1 -> P"<<endl;
        cout<<"2. Cong v vao u"<<endl;
        cout<<"Nhap lua chon: ";
        int choose;
        cin>>choose;
        if(choose==1){
            int p;
            cout<<"Nhap p: ";
            cin>>p;
            cout<<tinhTong(p)<<endl;
        }
        if(choose==2){
            int u,v;
            cout<<"Nhap u va v: ";
            cin>>u>>v;
            congThem(u,v);
            cout<<"Da cong thanh cong"<<endl;
        }
        if(choose==0){
            break;
        }
    }
}
