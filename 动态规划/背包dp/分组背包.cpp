// https://www.luogu.com.cn/problem/P1757
#include <bits/stdc++.h>
using namespace std;
#define int long long
#define endl '\n'
#define st first
#define nd second

const int N = 1007;
vector<vector<int>> v(N), w(N);
vector<int> dp(N);

signed main () {
	ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	int n, V;
	cin >> V >> n;

	int id_max = 0;
	for (int i = 1; i <= n; ++i) {
		int a, b, c;
		cin >> a >> b >> c;
		w[c].push_back(a);
		v[c].push_back(b);
		id_max = max(id_max, c);
	}

	for (int k = 1; k <= id_max; ++k) {				// 组数
		if (v[k].empty()) continue;	/* qwq */
		
		// 按照 0-1 背包处理
		for (int i = V; i >= 0; --i) {				// 背包容量
			for (int j = 0; j < v[k].size(); ++j) {	// 每个物品
				if (i >= w[k][j]) { 				// 能放下
					dp[i] = max(dp[i], dp[i - w[k][j]] + v[k][j]);
				}
			}
		}
	}

	cout << dp[V] << endl;
	return 0;
}