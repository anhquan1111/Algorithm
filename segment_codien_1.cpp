#include <bits/stdc++.h>
using namespace std;
const int Maxn = 10001;
struct Node{
    int optimal;
    int open;
    int close;
    Node(int op,int o,int c){
        optimal = op;
        open = o;
        close = c;
    }
    Node(){

    }
};
Node st[Maxn*4];
string s;
Node operator + (const Node& a , const Node& b){
    Node res;
    int tmp = min(a.open,b.close);
    res.optimal = a.optimal + b.optimal + tmp*2;
    res.open = a.open + b.open - tmp;
    res.close = a.close + b.close - tmp;
    return res;
}
void build(int index,int l,int r){
    if(l==r){
        if(s[l-1]=='('){
            st[index] = Node(0,1,0);
        }
        else{
            st[index] = Node(0,0,1);
        }
        return;
    }
    int m = (l+r)>>1;
    build(index*2,l,m);
    build(index*2+1,m+1,r);
    st[index] = st[index*2] + st[index*2+1];
}
Node query(int index,int l,int r,int u,int v){
    if(l>v || r<u){
        return Node(0,0,0);
    }
    if(l>=u && r<=v){
        return st[index];
    }
    int m = (l+r)>>1;
    Node get_1 = query(index*2,l,m,u,v);
    Node get_2 = query(index*2+1,m+1,r,u,v);
    return get_1 + get_2;
}
int main(){
    cout<<"Nhap chuoi: ";
    cin>>s;
    build(1,1,s.length());
    int q;
    cout<<"Nhap so truy van: ";
    cin>>q;
    while(q--){
        int u,v;
        cout<<"Nhap khoang u->v: ";
        cin>>u>>v;
        cout<<"open :"<<query(1,1,s.length(),u,v).open<<endl;
        cout<<"close :"<<query(1,1,s.length(),u,v).close<<endl;
        cout<<"optimal :"<<query(1,1,s.length(),u,v).optimal<<endl;
    }
}
