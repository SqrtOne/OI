// https://www.luogu.com.cn/problem/P3368
#include <bits/stdc++.h>
using namespace std;
#define int long long
#define endl '\n'
#define st first
#define nd second

int n, m;
vector<int> sum(5e5 + 7, 0);

int lowbit(int x) {
	return x & -x;
}

void add(int ind, int x) {
	while (ind <= n) {
		sum[ind] += x;
		ind += lowbit(ind);
	}
}

int get(int ind) {
	int res = 0;
	while (ind > 0) {
		res += sum[ind];
		ind -= lowbit(ind);
	}
	return res;
}

signed main () {
	ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	// 通过操作差分数组实现
	cin >> n >> m;
	vector<int> v(n + 7);
	for (int i = 1; i <= n; ++i) {
		cin >> v[i];
		add(i, v[i] - v[i - 1]);
	}
	
	while (m--) {
		int op, x, y, k;
		cin >> op;
		if (op == 1) {
			cin >> x >> y >> k;
			add(x, k);
			add(y + 1, -k);
		} else if (op == 2) {
			cin >> x;
			cout << get(x) << endl;
		} else cerr << "QAQ" << endl;
	}
	return 0;
}