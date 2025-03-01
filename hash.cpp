#include <bits/stdc++.h>
using namespace std;
const int P = 103;
struct HashTable{
    vector<pair<int,int>>h[P];
private:
    int getKey(int key){
        return key%P;
    }

public:
    void insert(int key,int value){
        int hkey = getKey(key);
        for(auto &tmp : h[hkey]){
            if(tmp.first==key){
                return;
            }
        }
        h[hkey].emplace_back(key,value);
    }
    int find(int key){
        int hkey = getKey(key);
        for(auto &tmp:h[hkey]){
            if(tmp.first==key){
                return tmp.second;
            }
        }
        return 0;
    }
};
int main(){
    HashTable a;
    a.insert(10,20);
    a.insert(30,40);
    cout<<a.find(10);
}
