#include <bits/stdc++.h>
using namespace std;
#define int long long
#define endl '\n'
#define st first
#define nd second

const int N = 1e6 + 7;
int n, m;
int ST[N][57];
int log_n[N] = {0, 0};

signed main () {
    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    cin >> n >> m;
    for (int i = 1; i <= n; ++i) {
        cin >> ST[i][0];
    }
    for (int i = 2; i <= n; ++i) {
        log_n[i] = log_n[i / 2] + 1;
    }
    for (int j = 1; j <= log_n[n]; ++j) {
        for (int i = 1; i + (1LL << j) - 1 <= n; ++i) {
            ST[i][j] = max(ST[i][j - 1], ST[i + (1LL << (j - 1))][j - 1]);
        }
    }
    while (m--) {
        int l, r;
        cin >> l >> r;
        int s = log_n[r - l + 1];
        cout << max(ST[l][s], ST[r - (1LL << s) + 1][s]) << endl;
    }
    return 0;
}