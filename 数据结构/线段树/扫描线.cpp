// OwO
#include <bits/stdc++.h>
using namespace std;
#define int long long
#define endl '\n'
#define st first
#define nd second

#define ls ((ind) << 1)
#define rs ((ind) << 1 | 1)

struct Edge { int x1, x2, y, val; };
vector<Edge> edge;
vector<int> v;
int f (int x) { return lower_bound(v.begin(), v.end(), x) - v.begin(); }

const int N = 8e5 + 7;
vector<int> xcnt(N), len(N);

void push_up (int ind, int L, int R) {
	if (xcnt[ind]) {
		len[ind] = v[R] - v[L];
	}
	else if (L + 1 == R) {
		len[ind] = 0;
	}
	else {
		len[ind] = len[ls] + len[rs];
	}
}

void update (int L, int R, int val, int ind = 1, int l = 0, int r = v.size() - 1) {
	if (L == l && R == r) {
		xcnt[ind] += val;
		push_up(ind, l, r);
		return;
	}

	int mid = (l + r) >> 1;
	if (L < mid) update(L, min(mid, R), val, ls, l, mid);
	if (mid < R) update(max(mid, L), R, val, rs, mid, r);
	push_up(ind, l, r);
}

signed main () {
	ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	int n;	cin >> n;

	for (int i = 1; i <= n; ++i) {
		int x1, x2, y1, y2;
		cin >> x1 >> y1 >> x2 >> y2;
		v.push_back(x1); v.push_back(x2);
		edge.push_back({x1, x2, y1, 1});
		edge.push_back({x1, x2, y2, -1});
	}

	sort (v.begin(), v.end());
	v.erase(unique(v.begin(), v.end()), v.end());
	sort (edge.begin(), edge.end(), [] (Edge x, Edge y) {
		if (x.y != y.y) return x.y < y.y;
		return x.val > y.val;
	});

	int sum = 0;
	update(f(edge[0].x1), f(edge[0].x2), edge[0].val);
	for (int i = 1; i < edge.size(); ++i) {
		int h = edge[i].y - edge[i - 1].y;
		sum += h * len[1];
		update(f(edge[i].x1), f(edge[i].x2), edge[i].val);
	}
	cout << sum << endl;
	return 0;
}