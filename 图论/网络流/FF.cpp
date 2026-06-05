// https://www.luogu.com.cn/problem/P3376
#include <bits/stdc++.h>
using namespace std;
#define int long long
#define endl '\n'
#define st first
#define nd second

const int N = 207;
int arr[N][N] = {};
int brr[N][N] = {};
int vis[N] = {};
int n, m, s, t;

// 用于寻找目前图的堵塞流。
// 找到一条路径，减去最小权值，再建立反向边。
int dfs (int ind, int _min) {
	vis[ind] = 1;
	if (ind == t) {
		return _min;
	}
	for (int i = 1; i <= n; ++i) {
		if (arr[ind][i] && !vis[i] && ind != i) {
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

// 通过反复的寻找堵塞流和建立反向边（允许反悔操作），找到最大流。
int FF () {
	int ans = 0;
	while (true) {
		memset(vis, 0, sizeof(vis));
		int flow = dfs(s, INT_MAX);
		ans += flow;
		if (flow == 0) break;
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
		brr[u][v] += w;
	}

	// 时间复杂度：O(mF)（F为最大流）
	cout << FF() << endl;
	return 0;
}
