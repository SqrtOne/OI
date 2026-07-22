// https://www.luogu.com.cn/problem/P1775
#include <bits/stdc++.h>
using namespace std;
#define int long long
#define endl '\n'
#define st first
#define nd second

const int N = 307;
vector<int> v(N);
vector<int> pre(N);
int dp[N][N];
int n;

signed main () {
	ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	cin >> n;
	for (int i = 1; i <= n; ++i) {
		cin >> v[i];
		pre[i] = pre[i - 1] + v[i];
	}
	for (int i = 1; i <= n; ++i) {
		for (int j = 1; j <= n; ++j) {
			dp[i][j] = (i == j) ? 0 : INT_MAX;
		}
	}

	for (int L = n; L >= 1; --L) {
		for (int R = L + 1; R <= n; ++R) {
			for (int k = L; k <= R; ++k) {
				dp[L][R] = min(dp[L][R], dp[L][k] + dp[k + 1][R] + pre[R] - pre[L - 1]);
			}
		}
	}

	cout << dp[1][n] << endl;
	return 0;
}