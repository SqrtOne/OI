// OwO
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

// SPFA
queue<int> q;
int cnt[N]; // cnt[i] 表示从起点 s 到节点 i 经过的边数
bool hx[N]; // hx[i] 表示节点 i 是否在队列中

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
                if (hx[v] == false) {
                    q.push(v);
                    hx[v] = true;
                } 

                if (cnt[v] >= n + 1) return false;
            }
        }
    }

    return true;
}

signed main () {
    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    cin >> n >> m;
    for (int i = 1; i <= m; ++i) {
        int u, v, w;
        cin >> u >> v >> w;
        arr[u].push_back({v, w});
        arr[v].push_back({u, w});
    }
    for (int i = 1; i <= n; ++i) {
        arr[0].push_back({i, 0});
        dist[i] = INT_MAX;
    }

    SPFA();
    return 0;
}

// p.s. Bellman–Ford

bool if_relax = false;

bool BF () {
    for (int i = 1; i <= n; ++i) {
        if_relax = false;
        for (int j = 0; j < arr[n].size(); ++j) {
            int u = i, v = arr[i][j].st, w = arr[i][j].nd;
            if (dist[u] == INT_MAX) continue;
            if (dist[u] + w < dist[v]) {
                dist[v] = dist[u] + w;
                if_relax = true;
            }
        }
        if (if_relax == false) return true;
    }
    return false;
}