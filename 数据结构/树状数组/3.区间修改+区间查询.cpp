// https://www.luogu.com.cn/problem/P3372
#include <bits/stdc++.h>
using namespace std;
#define int long long
#define endl '\n'
#define st first
#define nd second

const int N = 1e5 + 7;
int n, m;
struct Tree {
	int sum[N];
	int lowbit (int x) {
		return x & -x;
	}

	void add (int ind, int k) {
		while (ind <= n) {
			sum[ind] += k;
			ind += lowbit(ind);
		}
	}

	int get (int ind) {
		int res = 0;
		while (ind > 0) {
			res += sum[ind];
			ind -= lowbit(ind);
		}
		return res;
	}
} t1, t2;

signed main () {
	ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	cin >> n >> m;
	vector<int> v(n + 7);
	for (int i = 1; i <= n; ++i) {
		cin >> v[i];
		t1.add(i, v[i] - v[i - 1]);
		t2.add(i, (i - 1) * (v[i] - v[i - 1]));
	}

	while (m--) {
		int op, x, y, k;
		cin >> op >> x >> y;
		if (op == 1) {
			cin >> k;
			t1.add(x, k);
			t1.add(y + 1, -k);
			t2.add(x, (x - 1) * k);
			t2.add(y + 1, y * -k);
		} else {
			cout << (y * t1.get(y) - t2.get(y)) - 
				((x - 1) * t1.get(x - 1) - t2.get(x - 1)) << endl;
		}
	}
	return 0;
}