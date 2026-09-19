// https://www.luogu.com.cn/problem/P5055
#include <bits/stdc++.h>
using namespace std;
#define int long long
#define endl '\n'
#define st first
#define nd second
#define nl nullptr
#define siz(x) ((x) == nl ? 0 : (x)->size)
#define sum(x) ((x) == nl ? 0 : (x)->sum)

struct Node {
	Node *ls, *rs;
	int val, size, sum, rk, lazy;

	Node (int val) {
		this->val = sum = val;
		ls = rs = nl;
		size = 1;
		lazy = 0;
		rk = rand();
	}

	void upd () {
		size = siz(ls) + siz(rs) + 1;
		sum = val + sum(ls) + sum(rs);
	}

	void push_down ();
};
vector<Node*> vers;

Node* clone (Node *p) {
	Node *q = new Node(p->val); 
	q->sum = p->sum;
	q->ls = p->ls;	q->rs = p->rs;
	q->size = p->size;
	q->lazy = p->lazy;	
	q->rk = p->rk;
	return q;
}

void Node::push_down () {
	if (lazy == 0) return;
	swap(ls, rs);
	if (ls != nl) {
		ls = clone(ls);
		ls->lazy ^= 1;
	}
	if (rs != nl) {
		rs = clone(rs);
		rs->lazy ^= 1;
	}
	lazy = 0;
}

pair<Node*, Node*> split (Node *p, int rk) {
	if (p == nl) return {nl, nl};
	p = clone(p);
	p->push_down();
	if (siz(p->ls) + 1 <= rk) {
		auto t = split(p->rs, rk - siz(p->ls) - 1);
		p->rs = t.st;	p->upd();
		return {p, t.nd};
	}
	else {
		auto t = split(p->ls, rk);
		p->ls = t.nd;	p->upd();
		return {t.st, p};
	}
}

Node* merge (Node *p, Node *q) {
	if (p == nl) return q;
	if (q == nl) return p;

	if (p->rk <= q->rk) {
		p = clone(p);
		p->push_down();
		p->rs = merge(p->rs, q);
		p->upd();	return p;
	}
	else {
		q = clone(q);
		q->push_down();
		q->ls = merge(p, q->ls);
		q->upd();	return q;
	}
}

void insert (int ver, int rk, int val) {
	Node *root = vers[ver];
	auto t = split(root, rk);
	root = merge(merge(t.st, new Node(val)), t.nd);
	vers.push_back(root);
}

void _delete (int ver, int rk) {
	Node *root = vers[ver];
	auto t1 = split(root, rk);
	auto t2 = split(t1.st, rk - 1);
	root = merge(t2.st, t1.nd);
	vers.push_back(root);
}

void rev (int ver, int l, int r) {
	Node *root = vers[ver];
	auto t1 = split(root, r);
	auto t2 = split(t1.st, l - 1);
	if (t2.nd != nl) t2.nd->lazy ^= 1;
	root = merge(merge(t2.st, t2.nd), t1.nd);
	vers.push_back(root);
}

int get_sum (int ver, int l, int r) {
	Node *root = vers[ver];
	auto t1 = split(root, r);
	auto t2 = split(t1.st, l - 1);
	int res = sum(t2.nd);
	root = merge(merge(t2.st, t2.nd), t1.nd);
	vers.push_back(root);
	return res;
}

signed main () {
	ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	int n, last = 0;
	cin >> n;
	vers.push_back(nl);
	while (n--) {
		int ver, op;
		cin >> ver >> op;
		if (op == 1) {
			int p, x;
			cin >> p >> x;
			p ^= last;	x ^= last;
			insert(ver, p, x);
		}
		if (op == 2) {
			int p;
			cin >> p;
			p ^= last;
			_delete(ver, p);
		}
		if (op == 3) {
			int l, r;
			cin >> l >> r;
			l ^= last;	r ^= last;
			rev(ver, l, r);
		}
		if (op == 4) {
			int l, r;
			cin >> l >> r;
			l ^= last;	r ^= last;
			last = get_sum(ver, l, r);
			cout << last << endl;
		}
	}
	return 0;
}