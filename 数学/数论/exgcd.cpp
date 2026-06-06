// https://www.luogu.com.cn/problem/P5656

#include <bits/stdc++.h>
using namespace std;
#define int long long
#define endl '\n'
#define st first
#define nd second

int x, y;
void exgcd (int a, int b) {
	if (b == 0) {
		x = 1, y = 0;
		return;
	}
	exgcd(b, a % b);
	int t = x; x = y;
	y = t - a / b * y;
}

void solve () {
	int a, b, c;
	cin >> a >> b >> c;
	int d = __gcd(a, b);
	if (c % d != 0) {	// 裴蜀定理判断是否有解
		cout << -1 << endl;
		return;
	}

	exgcd(a, b);	// 求出 x0, y0 为 ax + by = d 的特解

	x *= c / d;		// ATTENTION!
	y *= c / d;		// 求出 x1, y1 为 ax + by = c 的特解

	int dx = b / d, dy = a / d;
	int kx = ceil(1.0 * (-x + 1) / dx), // kx 为满足 x > 0 的 k_min
		ky = floor(1.0 * (y - 1) / dy);	// ky 为满足 y > 0 的 k_max
			// ATTENTION! 可能存在负数运算，不能去掉 floor()

	int min_x = x + kx * dx,
		min_y = y - ky * dy,
		max_x = x + ky * dx,
		max_y = y - kx * dy;	// ATTENTION! 注意负数

	if (kx <= ky) {	
		cout << ky - kx + 1 << ' '
			 << min_x << ' ' <<	min_y << ' '
			 << max_x << ' ' << max_y << endl;
	} else {
		cout << min_x << ' ' << min_y << endl;
	}
}

signed main () {
	ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	int T;
	cin >> T;
	while (T--) {
		solve();
	}
	return 0;
}