// https://www.luogu.com.cn/problem/P3390
#include <bits/stdc++.h>
using namespace std;
#define int long long
#define endl '\n'
#define st first
#define nd second

int n, k;
const int N = 107;
const int mod = 1e9 + 7;
struct Mix { int v[N][N] = {}; } res, arr;

Mix operator * (Mix a, Mix b) {
    Mix ans;
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= n; ++j) {
            for (int k = 1; k <= n; ++k) {
                ans.v[i][j] = (a.v[i][k] * b.v[k][j] % mod + ans.v[i][j]) % mod;
            }
        }
    }
    return ans;
};

Mix operator ^ (Mix a, int n) {
    if (n == 0) return res;
    Mix x = a ^ (n / 2);
    Mix ans = x * x;
    if (n % 2) ans = ans * a;
    return ans;
}

signed main () {
    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    cin >> n >> k;
    for (int i = 1; i <= n; ++i) {
        res.v[i][i] = 1;
    }
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= n; ++j) {
            cin >> arr.v[i][j];
        }
    }
    arr = arr ^ k;
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= n; ++j) {
            cout << arr.v[i][j] << ' ';
        }
        cout << endl;
    }
    return 0;
}