// https://www.luogu.com.cn/problem/P3376
#include <bits/stdc++.h>
using namespace std;
#define int long long
#define endl '\n'
#define st first
#define nd second

const int N = 207;
int arr[N][N] = {};
int pre[N] = {};
int n, m, s, t;

int bfs () {
    memset(pre, -1, sizeof(pre));
    queue<int> q;
    q.push(s); pre[s] = 0;
    while (!q.empty()) {
        int x = q.front();
        q.pop(); 
        for (int i = 1; i <= n; ++i) {
            if (arr[x][i] && pre[i] == -1) {
                q.push(i);
                pre[i] = x;

                if (i == t) {
                    int flow = INT_MAX;
                    for (int p = t; p != s; p = pre[p]) {
                        flow = min(flow, arr[pre[p]][p]);
                    }
                    return flow;
                }
            }
        }
    }
    return 0;
}

int EK () {
    int ans = 0;
    while (true) {
        int flow = bfs();
        ans += flow;
        if (flow == 0) return ans;
        int x = t;

        while (x != s) {
            arr[pre[x]][x] -= flow;
            arr[x][pre[x]] += flow;
            x = pre[x];
        }
    }
    return -1;
}

signed main () {
    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	cin >> n >> m >> s >> t;
	for (int i = 1; i <= m; ++i) {
		int u, v, w;
		cin >> u >> v >> w;
		arr[u][v] += w;
	}
    
    // 时间复杂度：O(n * m^2)
    cout << EK() << endl;
    return 0;
}