// https://www.luogu.com.cn/problem/P1495

#include <bits/stdc++.h>
using namespace std;
#define int __int128
#define ll long long
#define endl '\n'
#define st first
#define nd second

const int N = 17;
vector<ll> a(N), m(N);
ll n;

int x, y;
void exgcd (int a, int b) {
	if (b == 0) {
		x = 1, y = 0;
		return;
	}
	exgcd(b, a % b);
	int t = x;	x = y;
	y = t - a / b * y;
}

ll CRT () {
	int ans = 0;
	int M = 1;
	for (int i = 1; i <= n; ++i) {
		M *= m[i];
	}
	
	for (int i = 1; i <= n; ++i) {
		int Mi = M / m[i];
		exgcd(Mi, m[i]);
		int Mi_1 = x;
		ans = ((ans + a[i] * Mi * Mi_1) % M + M) % M;
	}
	return ans;
}

signed main () {
	ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	cin >> n;
	for (int i = 1; i <= n; ++i) {
		cin >> m[i] >> a[i];
	}
	cout << CRT() << endl;
	return 0;
}