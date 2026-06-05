#include <bits/stdc++.h>
using namespace std;
#define int long long
#define endl '\n'
#define st first
#define nd second

const int N = 1e5 + 7;
vector<vector<pair<int, int>>> adj(N); // st 节点，nd 距离
vector<int> dist(N, INT_MAX);
vector<int> vis(N);
priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> q; 
// nd 节点，st 距离
// ATTENTION HERE!

signed main () {
	ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	int n, m, s;
	cin >> n >> m >> s;
	while (m--) {
		int u, v, w;
		cin >> u >> v >> w;
		adj[u].push_back({v, w});
	}
	dist[s] = 0; q.push({0, s});

	while (!q.empty()) {
		pair<int, int> x = q.top(); q.pop();
		if (vis[x.nd]) continue;
		vis[x.nd] = 1;
		for (auto y: adj[x.nd]) {
			if (dist[y.st] > x.st + y.nd) {
				dist[y.st] = x.st + y.nd;
				q.push({dist[y.st], y.st});
			}
		}
	}

	for (int i = 1; i <= n; ++i) {
		cout << dist[i] << ' ';
	}
	cout << endl;
	return 0;
}