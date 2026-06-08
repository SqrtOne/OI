// https://www.luogu.com.cn/problem/P4779
#include <bits/stdc++.h>
using namespace std;
#define int long long
#define endl '\n'
#define st first
#define nd second

struct Node {
	int id;
	int dist;
};
bool operator < (Node x, Node y) {
	return x.dist > y.dist;	// 大根堆优先队列
}

const int N = 1e5 + 7;
int n, m, s;
vector<pair<int, int>> v[N];
int dist[N];
bool vis[N];
priority_queue<Node> q;

signed main () {
	ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	cin >> n >> m >> s;
	for (int i = 1; i <= m; ++i) {
		int u, p, w;
		cin >> u >> p >> w;
		v[u].push_back({p, w});
	}

	for (int i = 1; i <= n; ++i) {
		dist[i] = INT_MAX;
	}

	q.push({s, 0});	dist[s] = 0;
	while (!q.empty()) {
		int x = q.top().id; q.pop();

		if (vis[x]) continue;
		vis[x] = true;

		for (int i = 0; i < v[x].size(); ++i) {
			int y = v[x][i].st, w = v[x][i].nd;
			if (dist[y] > dist[x] + w) {
				dist[y] = dist[x] + w;
				q.push({y, dist[y]});
			}
		}
	}

	for (int i = 1; i <= n; ++i) {
		cout << dist[i] << ' ';
	}
	return 0;
}