// https://www.luogu.com.cn/problem/P3369
#include <bits/stdc++.h>
using namespace std;
#define int long long
#define endl '\n'
#define st first
#define nd second
#define nl nullptr

const int INF = INT_MAX;
struct Node {
	int val = 0;
	Node *ls = nl, *rs = nl;
	int cnt = 0, size = 0;
	int rk = 0;

	Node (int val) {
		this->val = val;
		ls = rs = nl;
		cnt = size = 1;
		rk = rand();
	}

	void upd () {
		size = cnt;
		if (ls != nl) size += ls->size;
		if (rs != nl) size += rs->size;
	}
} *root;

array<Node*, 2> split_val (Node *p, int val) {
	if (p == nl) return {nl, nl};
	if (p->val <= val) {
		auto t = split_val(p->rs, val);
		p->rs = t[0];	p->upd();
		return {p, t[1]};
	}
	else {
		auto t = split_val(p->ls, val);
		p->ls = t[1];	p->upd();
		return {t[0], p};
	}
}

array<Node*, 3> split_rk (Node *p, int rk) {
	if (p == nl) return {nl, nl, nl};
	int less = (p->ls == nl ? 0 : p->ls->size);

	if (rk <= less) {
		auto t = split_rk(p->ls, rk);
		p->ls = t[2];	p->upd();
		return {t[0], t[1], p};
	}
	else if (rk <= less + p->cnt) {
		Node *l = p->ls, *r = p->rs;
		p->ls = p->rs = nl;		p->upd();
		return {l, p, r};
	}
	else {
		auto t = split_rk(p->rs, rk - less - p->cnt);
		p->rs = t[0];	p->upd();
		return {p, t[1], t[2]};
	}
}

Node* merge (Node *x, Node *y) {
	if (x == nl) return y;
	if (y == nl) return x;

	if (x->rk < y->rk) {
		x->rs = merge(x->rs, y);
		x->upd();
		return x;
	}
	else {
		y->ls = merge(x, y->ls);
		y->upd();
		return y;
	}
}

void insert (int val) {
	auto t1 = split_val(root, val);
	auto t2 = split_val(t1[0], val - 1);

	if (t2[1] == nl) 
		t2[1] = new Node(val);
	else 
		t2[1]->size ++, t2[1]->cnt ++;
	
	root = merge(merge(t2[0], t2[1]), t1[1]);
}

void _delete (int val) {
	auto t1 = split_val(root, val);
	auto t2 = split_val(t1[0], val - 1);

	if (t2[1] == nl || t2[1]->cnt <= 1) 
		root = merge(t2[0], t1[1]);
	else {
		t2[1]->size --, t2[1]->cnt --;
		root = merge(merge(t2[0], t2[1]), t1[1]);
	}
}

int find_rk (Node *p, int val) {
	auto t = split_val(p, val - 1);
	int res = (t[0] == nl ? 1 : t[0]->size + 1);
	p = merge(t[0], t[1]);
	return res;
}

int find_val (Node *p, int rk) {
	auto t = split_rk(p, rk);
	int res = t[1]->val;
	p = merge(merge(t[0], t[1]), t[2]);
	return res;
}

int find_pre (int val) {
	auto t = split_val(root, val - 1);
	int res = (t[0] == nl ? -INF : find_val(t[0], t[0]->size));
	root = merge(t[0], t[1]);
	return res;
}

int find_next (int val) {
	auto t = split_val(root, val);
	int res = (t[1] == nl ? INF : find_val(t[1], 1));
	root = merge(t[0], t[1]);
	return res;
}

signed main () {
	ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	srand(time(0));
	int n;	cin >> n;
	while (n--) {
		int op, x;
		cin >> op >> x;
		if (op == 1) insert(x);
		if (op == 2) _delete(x);
		if (op == 3) cout << find_rk(root, x) << endl;
		if (op == 4) cout << find_val(root, x) << endl;
		if (op == 5) cout << find_pre(x) << endl;
		if (op == 6) cout << find_next(x) << endl;
	}
	return 0;
}