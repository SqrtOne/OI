// https://www.luogu.com.cn/problem/P4514
#include <bits/stdc++.h>
using namespace std;
#define int long long
#define endl '\n'
#define st first
#define nd second

const int N = 2048 + 7;
int n, m;

struct Tree {
	int sum[N][N];
	int lowbit (int x) {
		return x & -x;
	}

	void add (int x, int y, int k) {
		for (int i = x; i <= n; i += lowbit(i)) {
			for (int j = y; j <= m; j += lowbit(j)) {
				sum[i][j] += k;
			}
		}
	}

	int get (int x, int y) {
		int res = 0;
		for (int i = x; i > 0; i -= lowbit(i)) {
			for (int j = y; j > 0; j -= lowbit(j)) {
				res += sum[i][j];
			}
		}
		return res;
	}
} t1, t2, t3, t4;

// S(x,y) = (x+1)(y+1)*sum(D) - (y+1)*sum(p*D) - (x+1)*sum(q*D) + sum(p*q*D)
void add (int x, int y, int k) {
	t1.add(x, y, k);
	t2.add(x, y, x * k);
	t3.add(x, y, y * k);
	t4.add(x, y, x * y * k);
}

int get (int x, int y) {
	return t1.get(x, y) * (x + 1) * (y + 1) \
		 - t2.get(x, y) * (y + 1) \
		 - t3.get(x, y) * (x + 1) \
		 + t4.get(x, y);
}

signed main () {
	ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	char op;
	cin >> op >> n >> m;
	while (cin >> op) {
		int a, b, c, d, val;
		cin >> a >> b >> c >> d;
		if (op == 'L') {
			cin >> val;
			add(a, b, val);
			add(a, d + 1, -val);
			add(c + 1, b, -val);
			add(c + 1, d + 1, val);
		} else {
			cout << get(c, d) - get(a - 1, d) \
				- get(c, b - 1) + get(a - 1, b - 1) << endl;
		}
	}
	return 0;
}