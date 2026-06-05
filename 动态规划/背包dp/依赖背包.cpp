// https://www.luogu.com.cn/problem/P1064
#include <bits/stdc++.h>
using namespace std;
#define int long long
#define endl '\n'
#define st first
#define nd second

const int N = 3.2e4 + 7;
vector<vector<pair<int, int>>> t(N, vector<pair<int, int>>(10));
vector<vector<int>> v(N, vector<int>(10)), w(N, vector<int>(10));
vector<int> dp(N);

signed main () {
	ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	int n, m;
	cin >> n >> m;

	// 存储输入
	for (int i = 1; i <= m; ++i) {
		int x, p, q;
		cin >> x >> p >> q;
		if (q == 0) {
			t[i][0] = {x, p};		// 主件存在 t[编号][0]
		} else {
			if (t[q][1].nd == 0) {	// 子件存在 t[主件][1] 和 t[主件][2]
				t[q][1] = {x, p};
			} else t[q][2] = {x, p};
		}
	}

	// 转化为分组背包处理
	for (int i = 1; i <= m; ++i) {
		if (t[i][0].nd == 0) continue;
		// 展示石山代码qwq
		w[i][1] = t[i][0].st;
		w[i][2] = t[i][0].st + t[i][1].st;
		w[i][3] = t[i][0].st + t[i][2].st;
		w[i][4] = t[i][0].st + t[i][1].st + t[i][2].st;

		v[i][1] = t[i][0].st * t[i][0].nd;
		v[i][2] = t[i][0].st * t[i][0].nd + t[i][1].st * t[i][1].nd;
		v[i][3] = t[i][0].st * t[i][0].nd + t[i][2].st * t[i][2].nd;
		v[i][4] = t[i][0].st * t[i][0].nd + t[i][1].st * t[i][1].nd + t[i][2].st * t[i][2].nd;
	}

	// 直接分组背包秒了喵
	for (int k = 1; k <= m; ++k) {
		for (int i = n; i >= 0; --i) {
			for (int j = 0; j < v[k].size(); ++j) {
				if (i >= w[k][j]) {
					dp[i] = max(dp[i], dp[i - w[k][j]] + v[k][j]);
				}
			}
		}
	}
	cout << dp[n] << endl;
	return 0;
}