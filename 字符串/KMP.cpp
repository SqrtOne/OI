// https://www.luogu.com.cn/problem/P3375
#include <bits/stdc++.h>
using namespace std;
#define int long long
#define endl '\n'
#define st first
#define nd second

const int N = 2e6 + 7;
vector<int> nex(N);

void KMP (string x) {
    int n = x.size();
    nex[0] = 0;
    for (int i = 1; i < n; ++i) {
        int j = nex[i - 1];
        while (x[j] != x[i] && j > 0) {
            j = nex[j - 1];
        }

        if (x[i] == x[j]) j += 1;
        nex[i] = j;
    }
}

signed main () {
    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    string S, T;
    cin >> S >> T;
    string x = T + "#" + S;
    KMP(x);
    int T_size = T.size();
    for (int i = T_size + 1; i < x.size(); ++i) {
        if (nex[i] == T_size) {
            cout << i - 2 * T.size() + 1 << endl;
        }
    }
    KMP(T);
    for (int i = 0; i < T_size; ++i) {
        cout << nex[i] << ' ';
    }
    cout << endl;
    return 0;
}