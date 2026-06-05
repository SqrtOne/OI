// https://www.luogu.com.cn/problem/P3376
#include <bits/stdc++.h>
using namespace std;
#define int long long
#define endl '\n'
#define st first
#define nd second

const int N = 207;
int arr[N][N] = {};
int level[N] = {};
int cur[N] = {};
int n, m, s, t;

bool bfs () {
    memset(level, -1, sizeof(level));
    queue<int> q;
    q.push(s); level[s] = 0;
    while (!q.empty()) {
        int x = q.front(); 
        q.pop();
        for (int i = 1; i <= n; ++i) {
            if (arr[x][i] && level[i] == -1) {
                q.push(i);
                level[i] = level[x] + 1;
            }
        }
    }
    return (level[t] != -1);
}

int dfs (int ind, int _min) {
	if (ind == t) {
		return _min;
	}
	for (int i = cur[ind]; i <= n; ++i) {
        cur[ind] = i;
		if (arr[ind][i] && level[ind] + 1 == level[i]) {
			int flow = dfs(i, min(_min, arr[ind][i]));
            
			if (flow) {
				arr[ind][i] -= flow;
				arr[i][ind] += flow;
				return flow;
			}
		}
	}
	return 0;
}

int dinic () {
	int ans = 0;
	while (bfs()) {
        for(int i = 1; i <= n; ++i)
            cur[i] = 1;
        while(true) {
            int flow = dfs(s, INT_MAX);
            if (flow == 0) break;
            ans += flow;
        }
    }
	return ans;
}

signed main () {
    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    cin >> n >> m >> s >> t;
	for (int i = 1; i <= m; ++i) {
		int u, v, w;
		cin >> u >> v >> w;
		arr[u][v] += w;
	}

    // 时间复杂度：O(n^2 * m)
    cout << dinic() << endl;
    return 0;
}