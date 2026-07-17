// https://www.luogu.com.cn/problem/P3384
#include <bits/stdc++.h>
using namespace std;
#define int long long
#define endl '\n'
#define st first
#define nd second

const int N = 1e5 + 7;
vector<int> input(N);   // 输入的初值数组
vector<int> v(N);       // 迁移后的初值数组
vector<int> Tree[N];
vector<int> depth(N);
vector<int> father(N);
vector<int> son(N);		// 重儿子（子树最大的儿子）
vector<int> size(N);	// 子树大小（含自己）
vector<int> top(N);		// 所在链的链顶
vector<int> dfn(N);     // 结点的 DFS 序 & 在线段树中的编号
vector<int> inv_dfn(N); // dfn[]的逆映射，有inv_dfn[dfn[x]] = x
int cnt = 0;
int n, m, S, mod;

namespace SegTree {
    struct Node {
        int num = 0;
        int lazy = 0;
    } Tree[N * 4];

    #define ls ind * 2
    #define rs ind * 2 + 1

    void init (int ind, int L, int R) {
        if (L == R) {
            Tree[ind].num = v[L] % mod;
            return;
        }

        int mid = (L + R) / 2;
        init (ls, L, mid);
        init (rs, mid + 1, R);

        Tree[ind].num = Tree[ls].num + Tree[rs].num;
        Tree[ind].num %= mod;
    }

    void push_down (int ind, int L, int R) {
        int mid = (L + R) / 2;
        Tree[ls].lazy += Tree[ind].lazy;
        Tree[ls].num += Tree[ind].lazy * (mid - L + 1);
        
        Tree[rs].lazy += Tree[ind].lazy;
        Tree[rs].num += Tree[ind].lazy * (R - mid);

        Tree[ls].num %= mod; Tree[ls].lazy %= mod;
        Tree[rs].num %= mod; Tree[rs].lazy %= mod;
        Tree[ind].lazy = 0;
    }

    int query (int ind, int L, int R, int l, int r) {
        if (l <= L && R <= r) {
            return Tree[ind].num % mod;
        }

        int mid = (L + R) / 2;
        if (Tree[ind].lazy) {
            push_down(ind, L, R);
        }
        
        int res = 0;
        if (l <= mid) 
            res += query(ls, L, mid, l, r);
        if (r >= mid + 1) 
            res += query(rs, mid + 1, R, l, r);

        return res % mod;
    }

    void update (int ind, int L, int R, int l, int r, int x) {
        if (l <= L && R <= r) {
            Tree[ind].num += x * (R - L + 1); Tree[ind].num %= mod;
            Tree[ind].lazy += x;    Tree[ind].lazy %= mod;
            return;
        }

        if (Tree[ind].lazy) {
            push_down(ind, L, R);
        }

        int mid = (L + R) / 2;
        if (l <= mid) 
            update(ls, L, mid, l, r, x);
        if (r >= mid + 1) 
            update(rs, mid + 1, R, l, r, x);

        Tree[ind].num = (Tree[ls].num + Tree[rs].num) % mod;
    }
}

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
    dfn[u] = ++cnt;
    v[cnt] = input[u];
    inv_dfn[cnt] = u;
	if (!son[u]) return;
	dfs2(son[u], ftop);     // 先处理重儿子

	for (auto v: Tree[u]) {
		if (v != father[u] && v != son[u]) {
			dfs2(v, v);		// 将轻孩子拆入新链
		}
	}
}

void update_path (int x, int y, int k) {
    while (top[x] != top[y]) {	                            // 不在同一条链上
		if (depth[top[x]] < depth[top[y]]) swap(x, y);      // 确保x所在的链更深
        SegTree::update(1, 1, n, dfn[top[x]], dfn[x], k);   // 更新从链顶到x的路径
		x = father[top[x]];		                            // 将x跳到链顶节点的父节点
	}

    if (depth[x] > depth[y]) swap(x, y);
    SegTree::update(1, 1, n, dfn[x], dfn[y], k);
}

int query_path (int x, int y) {
    int res = 0;
    while (top[x] != top[y]) {
        if (depth[top[x]] < depth[top[y]]) swap(x, y);
        res += SegTree::query(1, 1, n, dfn[top[x]], dfn[x]);
        res %= mod;
        x = father[top[x]];
    }

    if (depth[x] > depth[y]) swap(x, y);
    res += SegTree::query(1, 1, n, dfn[x], dfn[y]);
    res %= mod;     return res;
}

void update_son (int x, int k) {
    SegTree::update(1, 1, n, dfn[x], dfn[x] + size[x] - 1, k);
}

int query_son (int x) {
    return SegTree::query(1, 1, n, dfn[x], dfn[x] + size[x] - 1);
}

signed main () {
    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    cin >> n >> m >> S >> mod;
    for (int i = 1; i <= n; ++i) {
        cin >> input[i];
    }

    for (int i = 1; i <= n - 1; ++i) {
        int x, y;   cin >> x >> y;
        Tree[x].push_back(y);
        Tree[y].push_back(x);
    }

    dfs1(S, 0);
    dfs2(S, S);
    SegTree::init(1, 1, n);

    while (m--) {
        int op, x, y, k;
        cin >> op;
        switch (op) {
            case 1: 
                cin >> x >> y >> k;
                update_path(x, y, k % mod);
                break;

            case 2: 
                cin >> x >> y;
                cout << query_path(x, y) << endl;
                break;

            case 3: 
                cin >> x >> k;
                update_son(x, k % mod);
                break;

            case 4: 
                cin >> x;
                cout << query_son(x) << endl;
                break;
        }
    }
    return 0;
}