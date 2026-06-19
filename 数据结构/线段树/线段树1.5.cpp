// https://www.luogu.com.cn/problem/P13825
#include <bits/stdc++.h>
using namespace std;
#define int unsigned long long
#define endl '\n'
#define st first
#define nd second

const int N = 6e6 + 7e5;
struct Node {
	int num = 0;
	int lazy = 0;
    int ls, rs;
} Tree[N];

int root = 1;
int cnt = 1;

// 懒喵qwq
#define ls Tree[ind].ls
#define rs Tree[ind].rs

void push_down (int ind, int L, int R) {
    if (ls == 0) ls = ++cnt;
    if (rs == 0) rs = ++cnt;

	int mid = (L + R) / 2;
	Tree[ls].lazy += Tree[ind].lazy;
	Tree[ls].num += Tree[ind].lazy * (mid - L + 1);
	
	Tree[rs].lazy += Tree[ind].lazy;
	Tree[rs].num += Tree[ind].lazy * (R - mid);
	Tree[ind].lazy = 0;
}

int query (int ind, int L, int R, int l, int r) {
    if (ind == 0) {
        return 0;
    }

	if (l <= L && R <= r) {
		return Tree[ind].num;
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

	return res;
}

void update (int &ind, int L, int R, int l, int r, int x) {
    if (ind == 0) {
        ind = ++cnt;
    }

	if (l <= L && R <= r) {
		Tree[ind].num += x * (R - L + 1);
		Tree[ind].lazy += x;
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

	Tree[ind].num = Tree[ls].num + Tree[rs].num;
}

signed main () {
	ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	int n, m;
	cin >> n >> m;

	while (m--) {
		int op;
		cin >> op;
		if (op == 1) {
			int x, y, k;
			cin >> x >> y >> k;
			update(root, 1, n, x, y, k);
		} else if (op == 2) {
			int x, y;
			cin >> x >> y;
            int res = query(1, 1, n, x, y);
            res += (x + y) * (y - x + 1) / 2;
			cout << res << endl;
		}
	}
	return 0;
}