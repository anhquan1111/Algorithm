#include <bits/stdc++.h>
using namespace std;

bool check(int Max,int w[],int n,int day){
    int current = 0;
    day--;
    for(int i=0;i<n;i++){
        if(current + w[i]<=Max){
            current += w[i];
        }
        else{
            day--;
            current = w[i];
        }
    }
    return day>=0;
}

int binarys(int w[],int n,int day){
    int l=0;
    int r=0;
    for(int i=0;i<n;i++){
        l = max(l,w[i]);
        r += w[i];
    }
    while(l<r){
        int m = (l+r)/2;
        if(check(m,w,n,day)){
            r=m;
        }
        else{
            l=m+1;
        }
    }
    return l;
}

int main(){
    int n;
    cout<<"Nhap so luong: ";
    cin>>n;
    int w[n];
    cout<<"Nhap khoi luong can chuyen: ";
    for(int i=0;i<n;i++){
        cin>>w[i];
    }
    int day;
    cout<<"Nhap so ngay can chuyen: ";
    cin>>day;
    cout<<"Khoi luong toi thieu: "<<binarys(w,n,day);
}   
