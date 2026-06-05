// https://www.luogu.com.cn/problem/P3372
#include <bits/stdc++.h>
using namespace std;
#define int long long
#define endl '\n'
#define st first
#define nd second

const int N = 1e6 + 7;
int arr[N];
int L[N], R[N];
int belong[N];
int len, n;

int lazy[N] = {}; // 块内每一个元素加了多少？
int num[N] = {}; // 单一的数值加了多少？ 单一的真实数值为 num[i] + lazy[belong[i]];
int sum[N] = {}; // 第i块的总和，用于跳块

void update (int L, int R, int x) {
    if (belong[L] == belong[R]) {
        for (int i = L; i <= R; ++i) {
            num[i] += x;
            sum[belong[i]] += x;
        }
        return;
    }

    for (int i = L; i <= ::R[belong[L]]; ++i) {
        num[i] += x;
        sum[belong[i]] += x;
    }

    for (int i = ::L[belong[R]]; i <= R; ++i) {
        num[i] += x;
        sum[belong[i]] += x;
    }

    for (int i = belong[L] + 1; i <= belong[R] - 1; ++i) {
        lazy[i] += x;
        sum[i] += x * (::R[i] - ::L[i] + 1);
    }
}

int query (int L, int R) {
    int ans = arr[R] - arr[L - 1];
    int x = belong[L], y = belong[R];

    if (x == y) {
        for (int i = L; i <= R; ++i) {
            ans += num[i] + lazy[x];
        } 
        return ans;
    }

    for (int i = L; i <= ::R[belong[L]]; ++i) {
        ans += num[i] + lazy[x];
    }

    for (int i = ::L[belong[R]]; i <= R; ++i) {
        ans += num[i] + lazy[y];
    }

    for (int i = belong[L] + 1; i <= belong[R] - 1; ++i) {
        ans += sum[i];
    }
    return ans;
}

signed main () {
    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    cin >> n;

    int m;
    cin >> m;

    for (int i = 1; i <= n; ++i) {
        cin >> arr[i];
        arr[i] += arr[i - 1];
    }
    len = sqrt(n);

    for (int i = 1; i <= len; ++i) {
        L[i] = (i - 1) * len + 1;
        R[i] = i * len;
    }
    R[len] = n;

    for (int i = 1; i <= len; ++i) {
        for (int j = L[i]; j <= R[i]; ++j) {
            belong[j] = i;
        }
    }

    while (m--) {
        int op;
        cin >> op;
        if (op == 1) {
            int x, y, k;
            cin >> x >> y >> k;
            update(x, y, k);
        } else {
            int x, y;
            cin >> x >> y;
            cout << query(x, y) << endl;
        }
    }
    return 0;
}