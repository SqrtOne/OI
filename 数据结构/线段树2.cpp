// https://www.luogu.com.cn/problem/P3373
#include <bits/stdc++.h>
using namespace std;
#define int long long
#define endl '\n'
#define st first
#define nd second

const int N = 4e5 + 7;
int mod;
struct Node {
	int num = 0;
	int lazy_plus = 0;
	int lazy_mul = 1;
} Tree[N];

void init (int ind, int L, int R) {
	if (L == R) {
		cin >> Tree[ind].num;
		return;
	}

	int mid = (L + R) / 2;
	init (ind * 2, L, mid);
	init (ind * 2 + 1, mid + 1, R);

	Tree[ind].num = (Tree[ind * 2].num + Tree[ind * 2 + 1].num) % mod;
}

void push_down (int ind, int L, int R) {
	int mid = (L + R) / 2;

	Tree[ind * 2].lazy_mul *= Tree[ind].lazy_mul;
	Tree[ind * 2].lazy_plus *= Tree[ind].lazy_mul;
	Tree[ind * 2].lazy_plus += Tree[ind].lazy_plus;

	Tree[ind * 2].num *= Tree[ind].lazy_mul;
	Tree[ind * 2].num += Tree[ind].lazy_plus * (mid - L + 1);

	Tree[ind * 2 + 1].lazy_mul *= Tree[ind].lazy_mul;
	Tree[ind * 2 + 1].lazy_plus *= Tree[ind].lazy_mul;
	Tree[ind * 2 + 1].lazy_plus += Tree[ind].lazy_plus;

	Tree[ind * 2 + 1].num *= Tree[ind].lazy_mul;
	Tree[ind * 2 + 1].num += Tree[ind].lazy_plus * (R - mid);

	Tree[ind * 2].lazy_mul %= mod;
	Tree[ind * 2].lazy_plus %= mod;
	Tree[ind * 2].num %= mod;

	Tree[ind * 2 + 1].lazy_mul %= mod;
	Tree[ind * 2 + 1].lazy_plus %= mod;
	Tree[ind * 2 + 1].num %= mod;

	Tree[ind].lazy_plus = 0;
	Tree[ind].lazy_mul = 1;
}

int query (int ind, int L, int R, int l, int r) {
	if (l <= L && R <= r) {
		return Tree[ind].num;
	}

	int mid = (L + R) / 2;

	push_down(ind, L, R);
	
	int res = 0;
	if (l <= mid) 
		res += query(ind * 2, L, mid, l, r);
	if (r >= mid + 1) 
		res += query(ind * 2 + 1, mid + 1, R, l, r);

	return res % mod;
}

void update_plus (int ind, int L, int R, int l, int r, int x) {
	if (l <= L && R <= r) {
		Tree[ind].num += x * (R - L + 1);
		Tree[ind].lazy_plus += x;

		Tree[ind].num %= mod;
		Tree[ind].lazy_plus %= mod;
		return;
	}

	push_down(ind, L, R);

	int mid = (L + R) / 2;
	if (l <= mid) 
		update_plus(ind * 2, L, mid, l, r, x);
	if (r >= mid + 1) 
		update_plus(ind * 2 + 1, mid + 1, R, l, r, x);

	Tree[ind].num = (Tree[ind * 2].num + Tree[ind * 2 + 1].num) % mod;
}

void update_mul (int ind, int L, int R, int l, int r, int x) {
	if (l <= L && R <= r) {
		Tree[ind].num *= x;
		Tree[ind].lazy_plus *= x;
		Tree[ind].lazy_mul *= x;

		Tree[ind].num %= mod;
		Tree[ind].lazy_plus %= mod;
		Tree[ind].lazy_mul %= mod;
		return;
	}

	push_down(ind, L, R);

	int mid = (L + R) / 2;
	if (l <= mid) 
		update_mul(ind * 2, L, mid, l, r, x);
	if (r >= mid + 1) 
		update_mul(ind * 2 + 1, mid + 1, R, l, r, x);

	Tree[ind].num = (Tree[ind * 2].num + Tree[ind * 2 + 1].num) % mod;
}

signed main () {
	ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	int n, m;
	cin >> n >> m >> mod;
	init(1, 1, n);

	while (m--) {
		int op;
		cin >> op;
		if (op == 1) {
			int x, y, k;
			cin >> x >> y >> k;
			update_mul(1, 1, n, x, y, k);

		} else if (op == 2) {
			int x, y, k;
			cin >> x >> y >> k;
			update_plus(1, 1, n, x, y, k);

		} else if (op == 3) {
			int x, y;
			cin >> x >> y;
			cout << query(1, 1, n, x, y) << endl;
		}
	}
	return 0;
}