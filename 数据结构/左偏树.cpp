// https://www.luogu.com.cn/problem/P3377
#include <bits/stdc++.h>
using namespace std;
#define int long long
#define endl '\n'
#define st first
#define nd second

const int N = 1e6 + 7;
int Tree[N];
int dist[N];
int ls[N], rs[N];

int pre[N];
int hx[N];

int merge (int x, int y) {
	if (x == 0 || y == 0) return x + y;	// 返回不为0的点
	if (Tree[x] > Tree[y]) swap(x, y);	// 取较小的值为根，作为x
	rs[x] = merge(rs[x], y);
	if (dist[ls[x]] < dist[rs[x]]) {
		swap(ls[x], rs[x]);
	}
	dist[x] = dist[rs[x]] + 1;
	return x;
}

int find (int x) {
	if (x == pre[x]) return x;
	return pre[x] = find(pre[x]);
}

signed main () {
	ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	int n, m;
	cin >> n >> m;
	for (int i = 1; i <= n; ++i) {
		cin >> Tree[i];
		dist[i] = 0;
		pre[i] = i;
	}

	while (m--) {
		int op;
		cin >> op;
		if (op == 1) {
			int x, y;
			cin >> x >> y;
			if (hx[x] || hx[y]) continue;
			x = find(x); y = find(y);
			if (x != y) pre[x] = pre[y] = merge(x, y);
		} else {
			int x;
			cin >> x;
			if (hx[x]) {
				cout << -1 << endl;
				continue;
			}
			x = find(x); hx[x] = 1; 
			pre[ls[x]] = pre[rs[x]] = merge(ls[x], rs[x]);
			pre[x] = pre[ls[x]];
			cout << Tree[x] << endl;
		}
	}
	return 0;
}