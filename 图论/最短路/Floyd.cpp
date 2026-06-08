// https://www.luogu.com.cn/problem/B3647
#include <bits/stdc++.h>
using namespace std;
#define int long long
#define endl '\n'
#define st first
#define nd second

const int N = 107;
// dp[k][x][y]，表示只允许经过结点 1 到 k 时，x 到 y 的最短路长度
// （第一维优化）
int dp[N][N];
int n, m;

void floyd () {
	for (int k = 1; k <= n; ++k) {
		for (int i = 1; i <= n; ++i) {
			for (int j = 1; j <= n; ++j) {
				// dp[k][i][j] = min(dp[k - 1][i][j], 
				// 	dp[k - 1][i][k] + dp[k - 1][k][j]);
				dp[i][j] = min(dp[i][j], dp[i][k] + dp[k][j]);
			}
		}
	}
}

signed main () {
	ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	memset(dp, 0x3f, sizeof(dp));

	cin >> n >> m;
	for (int i = 1; i <= n; ++i) dp[i][i] = 0;
	for (int i = 1; i <= m; ++i) {
		int u, v, w;
		cin >> u >> v >> w;
		dp[u][v] = min(dp[u][v], w);
		dp[v][u] = min(dp[v][u], w);
	}
	floyd();
	
	for (int i = 1; i <= n; ++i) {
		for (int j = 1; j <= n; ++j) {
			cout << dp[i][j] << ' ';
		}
		cout << endl;
	}
	return 0;
}