// https://www.luogu.com.cn/problem/P3379
#include <bits/stdc++.h>
using namespace std;
#define int long long
#define endl '\n'
#define st first
#define nd second

const int N = 5e5 + 7;
int n, m, s;
vector<int> pre(N);
vector<vector<int>> tree(N);
vector<vector<pair<int, int>>> ques(N);
vector<int> ans(N);
vector<int> vis(N);

int find(int i) {
	if (pre[i] == i) return i;
	return pre[i] = find(pre[i]);
}

void LCA(int s) {
	vis[s] = 1;
	for (int i = 0; i < tree[s].size(); ++i) {
		if (!vis[tree[s][i]]) {
			LCA(tree[s][i]);
			pre[tree[s][i]] = s;
		}
	}

	for (auto &i: ques[s]) {
		int v = i.st, id = i.nd;
		if (vis[v]) {
			ans[id] = find(v);
		}
	}
}

signed main () {
	ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	cin >> n >> m >> s;
	for (int i = 1; i <= n - 1; ++i) {
		int u, v;
		cin >> u >> v;
		tree[u].push_back(v);
		tree[v].push_back(u);
	}

	for (int i = 1; i <= m; ++i) {
		int a, b;
		cin >> a >> b;
		ques[a].push_back({b, i});
		ques[b].push_back({a, i});
	}

	for (int i = 1; i <= n; ++i) {
		pre[i] = i;
	}

	LCA(s);

	for (int i = 1; i <= m; ++i) {
		cout << ans[i] << endl;
	}
	return 0;
}