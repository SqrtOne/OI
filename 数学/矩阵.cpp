// https://www.luogu.com.cn/problem/P3390
#include <bits/stdc++.h>
using namespace std;
#define int long long
#define endl '\n'
#define st first
#define nd second

const int mod = 1e9 + 7;
const int N = 107;

struct Mix {
	int n;
	int v[N][N] = {};

	Mix () {
		n = 1;
		v[1][1] = 0;
	}

	Mix (const Mix& x) {
		n = x.n;
		for (int i = 1; i <= n; ++i) {
			for (int j = 1; j <= n; ++j) {
				v[i][j] = x.v[i][j];
			}
		}
	}

	Mix (int x, int y, int w[][N]) {
		n = x; 
		for (int i = 1; i <= n; ++i) {
			for (int j = 1; j <= n; ++j) {
				v[i][j] = w[i][j];
			}
		}
	}
} res, arr;

Mix mul (Mix a, Mix b) {
	Mix c; c.n = a.n; 
	for (int i = 1; i <= a.n; ++i) {
		for (int j = 1; j <= b.n; ++j) {
			for (int k = 1; k <= a.n; ++k) {
				c.v[i][j] += a.v[i][k] * b.v[k][j] % mod;
				c.v[i][j] %= mod;
			}
		}
	}
	return c;
}

Mix fpow (Mix n, int k) {
	Mix num(res);
	if (k == 1) return n;
	if (k == 0) return res;
	Mix fnext = fpow(n, k / 2);
	Mix ans = mul(fnext, fnext);
	if (k % 2) ans = mul(ans, n);
	return ans;
}

signed main () {
	ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	int n, k;
	cin >> n >> k;
	res.n = n; arr.n = n;
	for (int i = 1; i <= n; ++i) res.v[i][i] = 1; 
	for (int i = 1; i <= n; ++i) {
		for (int j = 1; j <= n; ++j) {
			cin >> arr.v[i][j];
		}
	}
	arr = fpow(arr, k);
	for (int i = 1; i <= n; ++i) {
		for (int j = 1; j <= n; ++j) {
			cout << arr.v[i][j] << ' ';
		}
		cout << endl;
	}
	return 0;
}
