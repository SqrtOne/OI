// https://www.luogu.com.cn/problem/P3366
#include <bits/stdc++.h>
using namespace std;
#define int long long
#define endl '\n'
#define st first
#define nd second

const int N = 5e3 + 7;
const int M = 2e5 + 7;
struct Edge { int u, v, w; };
vector<Edge> edge(M);
vector<int> pre(N);
int n, m, ans = 0, cnt = 0;

int find (int x) {
	return x == pre[x] ? x : pre[x] = find(pre[x]);
}

signed main () {
	ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	cin >> n >> m;
	for (int i = 1; i <= m; ++i) {
		cin >> edge[i].u >> edge[i].v >> edge[i].w;
	}

	sort (edge.begin() + 1, edge.begin() + m + 1, \
		[](Edge x, Edge y) { return x.w < y.w; }); 
	
	for (int i = 1; i <= n; ++i) pre[i] = i;

	for (int i = 1; i <= m; ++i) {
        if (cnt == n - 1) break;
		int pu = find(edge[i].u);
		int pv = find(edge[i].v);
		if (pu == pv) continue;
		pre[pu] = pv;
		cnt ++;
		ans += edge[i].w;
	}

	if (cnt == n - 1) cout << ans << endl;
	else cout << "orz" << endl;
	return 0;
}