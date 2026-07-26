// https://www.luogu.com.cn/problem/P10447
#include <bits/stdc++.h>
using namespace std;
#define int long long
#define endl '\n'
#define st first
#define nd second

// dp[点集映射][终点]
int dp[(1 << 20) + 7][27];
int w[27][27];
int n;

signed main () {
	ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	cin >> n;
	for (int i = 0; i < n; ++i) 
		for (int j = 0; j < n; ++j) 
			cin >> w[i][j];
	
	memset(dp, 0x3f, sizeof(dp));
	dp[1][0] = 0;

	for (int S = 1; S < (1 << n); S++)	// 枚举点集 S
		for (int j = 0; j < n; ++j) 	// 枚举要加入集合的点 j
			if ((S >> j) & 1) 			// 判断 j 是否在集合 S 内
				for (int k = 0; k < n; ++k) 	 	// 枚举集合 S 中与 j 相连的点 k
					//  (S ^ (1 << j)): 从 S 中删去 j, 等价于 (S - (1 << j)) 
					if ((S ^ (1 << j)) >> k & 1) 	// 判断 k 是否在集合内且与 j 相异
						dp[S][j] = min(dp[S][j], dp[S ^ (1 << j)][k] + w[k][j]);

	cout << dp[(1 << n) - 1][n - 1] << endl;
	return 0;
}