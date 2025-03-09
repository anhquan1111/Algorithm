
#include <bits/stdc++.h>
using namespace std;

// Hàm tính mảng tiền tố (prefix function) của KMP
vector<int> prefix_function(string s) {
    int n = (int)s.length();
    vector<int> pi(n);
    for (int i = 1; i < n; i++) {
        int j = pi[i - 1];
        while (j > 0 && s[i] != s[j])
            j = pi[j - 1];
        if (s[i] == s[j])
            j++;
        pi[i] = j;
    }
    return pi;
}

int main() {
    string s;
    cout << "Nhap chuoi: ";
    cin >> s;

    int n = s.length();
    
    // Tính mảng pi
    vector<int> pi = prefix_function(s);

    // Mảng đếm số lần truy cập của từng chỉ số trong pi
    vector<int> ans(n, 0);

    // Duyệt từng vị trí i
    for (int i = 0; i < n; i++) {
        for (int j = i; j>=0; j = pi[j] - 1) {
            ans[j]++;
            if (!pi[j]) {
                break;
            }
        }
    }

    // In kết quả
    cout << "Mảng pi: ";
    for (int x : pi) cout << x << " ";
    cout << endl;

    cout << "Số lần truy cập vào từng vị trí: ";
    for (int x : ans) cout << x << " ";
    cout << endl;

    return 0;
}

