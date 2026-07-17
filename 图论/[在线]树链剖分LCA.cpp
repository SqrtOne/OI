// OwO
#include <bits/stdc++.h>
using namespace std;
#define int long long
#define endl '\n'
#define st first
#define nd second

const int N = 5e5 + 7;
vector<int> Tree[N];
vector<int> father(N);
vector<int> depth(N);
vector<int> son(N);		// 重儿子（子树最大的儿子）
vector<int> size(N);	// 子树大小
vector<int> top(N);		// 所在链的链顶
int n, m, S;

void dfs1 (int u, int fa) {
	size[u] = 1;
	father[u] = fa;
	depth[u] = depth[fa] + 1;

	for (auto v: Tree[u]) {
		if (v == fa) continue;
		dfs1(v, u);
		size[u] += size[v];
		if (size[v] > size[son[u]]) son[u] = v;
	}
}

// dfs (当前节点, 链顶)
void dfs2 (int u, int ftop) {
	top[u] = ftop;
	if (!son[u]) return;
	dfs2(son[u], ftop);		// 先处理重儿子

	for (auto v: Tree[u]) {
		if (v != father[u] && v != son[u]) {
			dfs2(v, v);		// 将轻孩子拆入新链
		}
	}
}

int LCA (int x, int y) {
	while (top[x] != top[y]) {	// 不在同一条链上
		if (depth[top[x]] < depth[top[y]]) {
			swap (x, y);		// 确保x所在的链更深
		}
		x = father[top[x]];		// 将x跳到链顶节点的父节点
	}

	return depth[x] < depth[y] ? x : y;	// 在同一条链上，深度更小的是父节点
}

signed main () {
	ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	cin >> n >> m >> S;
	for (int i = 1; i <= n - 1; ++i) {
		int x, y;	cin >> x >> y;
		Tree[x].push_back(y);
		Tree[y].push_back(x);
	}

	dfs1(S, 0);
	dfs2(S, S);

	for (int i = 1; i <= m; ++i) {
		int x, y;	cin >> x >> y;
		cout << LCA(x, y) << endl;
	}
	return 0;
}