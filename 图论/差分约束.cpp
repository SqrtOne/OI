// https://www.luogu.com.cn/problem/P1993
#include <bits/stdc++.h>
using namespace std;
#define int long long
#define endl '\n'
#define st first
#define nd second

const int N = 5e3 + 7;
vector<pair<int, int>> arr[N];
int n, m, s = 0;

int dist[N];
queue<int> q;
int cnt[N];
bool hx[N];

bool SPFA () {
    dist[s] = 0;
    q.push(s);
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        hx[u] = false;

        for (int i = 0; i < arr[u].size(); ++i) {
            int v = arr[u][i].st, w = arr[u][i].nd;
            if (dist[u] == INT_MAX) continue;
            if (dist[u] + w < dist[v]) {
                dist[v] = dist[u] + w;
                cnt[v] = cnt[u] + 1;
                if (!hx[v]) {
                    q.push(v);
                    hx[v] = true;
                }

                if (cnt[v] >= n + 1) {
                    return false;
                }
            }
        }
    }
    return true;
}

signed main () {
    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    cin >> n >> m;
    for (int i = 1; i <= m; ++i) {
        int op, a, b, c;
        cin >> op >> a >> b;

        // d[v] <= d[u] + w
        if (op == 3) {      // a <= b + 0 && b <= a + 0
            arr[a].push_back({b, 0});
            arr[b].push_back({a, 0});
        } else if (op == 1) {   // b <= a - c
            cin >> c;
            arr[a].push_back({b, -c});
        } else if (op == 2) {   // a <= b + c
            cin >> c;
            arr[b].push_back({a, c});
        } else cout << "XwX" << endl;
    }

    for (int i = 1; i <= n; ++i) {
        arr[0].push_back({i, 0});
        dist[i] = INT_MAX;
    }

    cout << (SPFA()? "Yes": "No") << endl;
    /*
    for (int i = 1; i <= n; ++i) {
        cout << dist[i] << ' ';
    }
    */
    return 0;
}