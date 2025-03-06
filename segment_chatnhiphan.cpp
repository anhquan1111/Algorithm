#include <bits/stdc++.h>
using namespace std;
int n;
int a[100];
int st[100];
void build(int index,int l,int r){
    if(l==r){
        st[index] = a[l];
        return;
    }
    int m = (l+r)>>1;
    build(index*2,l,m);
    build(index*2+1,m+1,r);
    st[index] = min(a[index*2],a[index*2+1]);
}
void update(int index,int l,int r,int i,int k){
    if(l>i || r<i){
        return;
    }
    if(l==r){
        st[index] = k;
        return;
    }
    int m = (l+r)>>1;
    update(index*2,l,m,i,k);
    update(index*2+1,m+1,r,i,k);
    st[index] = min(st[index*2],st[index*2+1]);
}
int timKiem(int index,int l,int r,int k){
    if(l==r){
        return l;
    }
    int m = (l+r)>>1;
    if(st[index*2]<=k){
        return timKiem(index*2,l,m,k);
    }
    else{
        return timKiem(index*2+1,m+1,r,k);
    }
}
int main(){
    cout<<"Nhap n: ";
    cin>>n;
    cout<<"Nhap a[i]: ";
    for(int i=1;i<=n;i++){
        cin>>a[i];
    }
    build(1,1,n);
    cout<<"Nhap so truy van: ";
    int q;
    cin>>q;
    while(q--){
        cout<<"1. Gan a[i] = k "<<endl;
        cout<<"2. i nho nhat sao cho a[i] <= k"<<endl;
        cout<<"3. In mang"<<endl;
        cout<<"4. Thoat"<<endl;
        cout<<"Nhap lua chon: ";
        int choose;
        cin>>choose;
        if(choose==1){
            int i,k;
            cout<<"Nhap i,k: ";
            cin>>i>>k;
            a[i]=k;
            update(1,1,n,i,k);
        }
        if(choose==2){
            int k;
            cout<<"Nhap k: ";
            cin>>k;
            cout<<"i la: "<<timKiem(1,1,n,k)<<endl;
        }
        if(choose==3){
            for(int i=1;i<=n;i++){
                cout<<a[i]<<" ";
            }
            cout<<endl;
        }
        if(choose==4){
            break;
        }
    }
}
