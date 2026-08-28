// https://www.luogu.com.cn/problem/P3835
#include <bits/stdc++.h>
using namespace std;
#define int long long
#define endl '\n'
#define st first
#define nd second

#define nl nullptr
#define less (p->ls == nl ? 0 : p->ls->size)

inline int read () {
	int x = 0, f = 1;
	char ch = getchar();
	while (ch < '0' || ch > '9') {
		if (ch == '-') f = -1;
		ch = getchar();
	}

	while (ch >= '0' && ch <= '9') {
		x = (x << 3) + (x << 1) + ch - '0';
		ch = getchar();
	}

	return x * f;
}

inline void write (int x) {
	if (x < 0) {
		putchar('-');
		x = -x;
	}
	if (x > 9) write(x / 10);
	putchar(x % 10 + '0');
}

const int INF = INT_MAX;
struct Node {
	int val, cnt, size, rk = 0;
	Node *ls, *rs;

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
};
vector<Node*> vers;

Node* clone (Node *p) {
	if (p == nl) return nl;
	Node *q = new Node(p->val);
	q->ls = p->ls; q->rs = p->rs;
	q->cnt = p->cnt; q->size = p->size;
	q->rk = p->rk;
	return q;
}

array<Node*, 2> split_val (Node *p, int val) {
	if (p == nl) return {nl, nl};
	p = clone(p);
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
	p = clone(p);

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
		// split() 中必然已经 clone，无需重复
		// x = clone(x);
		x->rs = merge(x->rs, y);
		x->upd();
		return x;
	}
	else {
		// y = clone(y);
		y->ls = merge(x, y->ls);
		y->upd();
		return y;
	}
}

void insert (int ver, int val) {
	Node *root = vers[ver];
	auto t1 = split_val(root, val);
	auto t2 = split_val(t1[0], val - 1);

	if (t2[1] == nl) 
		t2[1] = new Node(val);
	else 
		t2[1]->size ++, t2[1]->cnt ++;
	
	root = merge(merge(t2[0], t2[1]), t1[1]);
	vers.push_back(root);
}

void _delete (int ver, int val) {
	Node *root = vers[ver];
	auto t1 = split_val(root, val);
	auto t2 = split_val(t1[0], val - 1);

	if (t2[1] == nl || t2[1]->cnt <= 1) 
		root = merge(t2[0], t1[1]);
	else {
		t2[1]->size --, t2[1]->cnt --;
		root = merge(merge(t2[0], t2[1]), t1[1]);
	}
	vers.push_back(root);
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

int find_pre (Node *p, int val) {
	auto t = split_val(p, val - 1);
	int res = (t[0] == nl ? -INF : find_val(t[0], t[0]->size));
	p = merge(t[0], t[1]);
	return res;
}

int find_next (Node *p, int val) {
	auto t = split_val(p, val);
	int res = (t[1] == nl ? INF : find_val(t[1], 1));
	p = merge(t[0], t[1]);
	return res;
}

signed main () {
	// ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	srand(time(0));
	int n = read();
	vers.reserve(n + 1);
	vers.push_back(nl);
	while (n--) {
		int ver, op, x;
		ver = read(), op = read(), x = read();
		if (op == 1) insert(ver, x);
		if (op == 2) _delete(ver, x);
		if (op == 3) {
			write(find_rk(vers[ver], x));
			putchar('\n');
			vers.push_back(vers[ver]);
		}
		if (op == 4) {
			write(find_val(vers[ver], x));
			putchar('\n');
			vers.push_back(vers[ver]);
		}
		if (op == 5) {
			write(find_pre(vers[ver], x));
			putchar('\n');
			vers.push_back(vers[ver]);
		}
		if (op == 6) {
			write(find_next(vers[ver], x));
			putchar('\n');
			vers.push_back(vers[ver]);
		}
	}
	return 0;
}