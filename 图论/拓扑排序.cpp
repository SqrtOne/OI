// https://www.luogu.com.cn/problem/B3644
#include <bits/stdc++.h>
using namespace std;
#define int long long
#define endl '\n'
#define st first
#define nd second

const int N = 107;
int n;
vector<int> _map[N];
vector<int> in(N);
queue<int> q;

signed main () {
	ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	cin >> n;
	for (int i = 1; i <= n; ++i) {
		int u;
		while (cin >> u) {
			if (u == 0) break;
			in[u] ++;
			_map[i].push_back(u);
		}
	}

	for (int i = 1; i <= n; ++i) {
		if (in[i] == 0) q.push(i);
	}

	while (!q.empty()) {
		int x = q.front();	q.pop();
		cout << x << ' ';
		for (auto &i: _map[x]) {
			in[i] --;
			if (in[i] == 0) q.push(i);
		}
	}
	return 0;
}