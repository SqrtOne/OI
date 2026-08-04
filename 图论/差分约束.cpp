// https://www.luogu.com.cn/problem/P1260
#include <bits/stdc++.h>
using namespace std;
#define int long long
#define endl '\n'
#define st first
#define nd second

int n, m, s = 0;
const int N = 1007;
vector<pair<int, int>> _map[N];
vector<int> dist(N);
vector<int> cnt(N);
bool in[N];
queue<int> q;

bool SPFA () {
	q.push(s);
	dist[s] = 0;

	while (!q.empty()) {
		int u = q.front();	q.pop(); in[u] = false;

		for (auto i: _map[u]) {
			int v = i.st, w = i.nd;
			if (dist[u] == INT_MAX) continue;
			if (dist[u] + w < dist[v]) {
				dist[v] = dist[u] + w;
				cnt[v] = cnt[u] + 1;
				if (!in[v]) {
					q.push(v);
					in[v] = true;
				}

				if (cnt[v] >= n + 1) return false;
			}
		}
	}
	return true;
}

signed main () {
	ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	cin >> n >> m;
	for (int i = 1; i <= m; ++i) {
		int u, v, w;
		cin >> u >> v >> w;
		_map[v].push_back({u, w});
	}
	for (int i = 1; i <= n; ++i) {
		_map[s].push_back({i, 0});
		dist[i] = INT_MAX;
	}

	if (!SPFA()) {
		cout << "NO SOLUTION" << endl;
		return 0;
	}
	
	int _min = INT_MAX;
	for (int i = 1; i <= n; ++i) _min = min(dist[i], _min);
	for (int i = 1; i <= n; ++i) cout << dist[i] - _min << endl;
	return 0;
}