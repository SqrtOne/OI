// https://www.luogu.com.cn/problem/P3367
#include <bits/stdc++.h>
using namespace std;
#define int long long
#define endl '\n'
#define st first
#define nd second

const int N = 2e5 + 7;
vector<int> pre(N);
    
int find (int x) {
    if (x == pre[x]) return x;
    // 该死……写成`find(x)`直接MLE，调试了好久XwX
    return pre[x] = find(pre[x]);
}

void unite (int x, int y) {
    pre[find(x)] = find(y);
}

bool check (int x, int y) {
    return find(x) == find(y);
}

signed main () {
    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    int n, m;
    cin >> n >> m;
    for (int i = 1; i <= n; ++i) {
        pre[i] = i;
    }

    while (m--) {
        int z, x, y;
        cin >> z >> x >> y;
        if (z == 1) {
            unite(x, y);
        } else {
            cout << (check(x, y) ?'Y': 'N') << endl;
        }
    }
    return 0;
}