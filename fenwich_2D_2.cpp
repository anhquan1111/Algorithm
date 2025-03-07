#include <bits/stdc++.h>
using namespace std;
int n,m;
int BIT[4][10][10];
int a[10][10];
void Add(int u,int v,int value){
  for(int i=u;i<=n;i+=i&~(i-1)){
    for(int j=v;j<=m;j+=j&~(j-1)){
      BIT[0][i][j]+=value;
      BIT[1][i][j]+=value*u;
      BIT[2][i][j]+=value*v;
      BIT[3][i][j]+=value*u*v;
    }
  }
}
void rectAdd(int a,int b,int u,int v,int value){
    Add(a,b,value);
    Add(a,v+1,-value);
    Add(u+1,b,-value);
    Add(u+1,v+1,value);
}
int getSum(int u,int v){
  int sum[4]={0};
  for(int Bit=0;Bit<4;Bit++){
    for(int i=u;i>0;i-=i&~(i-1)){
      for(int j=v;j>0;j-=j&~(j-1)){
        sum[Bit]+=BIT[Bit][i][j];
      }
    }
  }
  return sum[0]*(u+1)*(v+1)-sum[1]*(v+1)-sum[2]*(u+1)+sum[3];
}
int main(){
  cout<<"Nhap n,m: ";
  cin>>n>>m;
  for(int i=1;i<=n;i++){
    cout<<"Nhap hang "<<i<<": ";
    for(int j=1;j<=m;j++){
      cin>>a[i][j];
      rectAdd(i,j,i,j,a[i][j]);
    }
  }
  cout<<"Nhap so truy van: ";
  int q;
  cin>>q;
  while(q--){
    cout<<"1.Them value vao mang[a->u][b->v]"<<endl;
    cout<<"2.Tong mang[1->u][1->v]"<<endl;
    cout<<"Nhap lua chon: ";
    int choose;
    cin>>choose;
    if(choose==1){
      int a,b,u,v,value;
      cout<<"Nhap a,b,u,v,value: ";
      cin>>a>>b>>u>>v>>value;
      rectAdd(a,b,u,v,value);
      cout<<"Da them thanh cong"<<endl;
    }
    if(choose==2){
      int u,v;
      cout<<"Nhap u,v: ";
      cin>>u>>v;
      cout<<"Tong: "<<getSum(u,v)<<endl;
    }
    if(choose==3){
      break;
    }
  }
}
