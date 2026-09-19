// ============================================================
#define REV 
// ifdef: 文艺平衡树 https://www.luogu.com.cn/problem/P3391
// else : 普通平衡树 https://www.luogu.com.cn/problem/P3369
// ============================================================ 

#include <bits/stdc++.h>
using namespace std;
#define int long long
#define endl '\n'
#define st first
#define nd second
#define siz(x) ((x) == nl ? 0 : (x)->size)
#define nl nullptr

struct Node {
    int val;
    Node *ls, *rs;
    int size, cnt;
    int rk;
    int lazy;

    Node (int val) {
        this->val = val;
        ls = rs = nl;
        cnt = size = 1;
        rk = rand();
        lazy = 0;
    }

    void upd () {
        size = cnt + siz(ls) + siz(rs);
    }

#ifdef REV
    void push_down () {
        if (lazy == 0) return;
        swap(ls, rs);
        if (ls != nl) ls->lazy ^= 1;
        if (rs != nl) rs->lazy ^= 1;
        lazy = 0;
    }
#else
	void push_down () {}
#endif
} *root = nl;

Node* merge (Node *p, Node *q) {
    if (p == nl) return q;
    if (q == nl) return p;
    p->push_down();
    q->push_down();
    if (p->rk < q->rk) {
        p->rs = merge(p->rs, q);
        p->upd();  return p;
    }
    else {
        q->ls = merge(p, q->ls);
        q->upd();  return q;
    }
}

// ============================================================
//  P3369 普通平衡树
// ============================================================
#ifndef REV

pair<Node*, Node*> split_val (Node *p, int val) {
    if (p == nl) return {nl, nl};
    p->push_down();
    if (p->val <= val) {
        auto t = split_val(p->rs, val);
        p->rs = t.st;  p->upd();
        return {p, t.nd};
    }
    else {
        auto t = split_val(p->ls, val);
        p->ls = t.nd;  p->upd();
        return {t.st, p};
    }
}

void insert (int val) {
    auto t1 = split_val(root, val);
    auto t2 = split_val(t1.st, val - 1);
    if (t2.nd == nl)
        t2.nd = new Node(val);
    else
        t2.nd->size ++, t2.nd->cnt ++;
    root = merge(merge(t2.st, t2.nd), t1.nd);
}

void _delete (int val) {
    auto t1 = split_val(root, val);
    auto t2 = split_val(t1.st, val - 1);
    if (t2.nd == nl || t2.nd->cnt <= 1)
        root = merge(t2.st, t1.nd);
    else {
        t2.nd->size --, t2.nd->cnt --;
        root = merge(merge(t2.st, t2.nd), t1.nd);
    }
}

int get_rk (Node *p, int val) {
    if (p == nl) return 1;
    p->push_down();
    if (val <= p->val) return get_rk(p->ls, val);
    return siz(p->ls) + p->cnt + get_rk(p->rs, val);
}

int kth (Node *p, int rk) {
    if (p == nl) return -1;
    p->push_down();
    if (rk <= siz(p->ls)) return kth(p->ls, rk);
    if (rk <= siz(p->ls) + p->cnt) return p->val;
    return kth(p->rs, rk - siz(p->ls) - p->cnt);
}

int find_pre (int val) {
    int rk = get_rk(root, val);
    if (rk == 1) return INT_MIN;
    return kth(root, rk - 1);
}

int find_next (int val) {
    int rk = get_rk(root, val + 1);
    if (rk > siz(root)) return INT_MAX;
    return kth(root, rk);
}

signed main () {
    srand(time(0));
	int n;	cin >> n;
	while (n--) {
		int op, x;
		cin >> op >> x;
		if (op == 1) insert(x);
		if (op == 2) _delete(x);
		if (op == 3) cout << get_rk(root, x) << endl;
		if (op == 4) cout << kth(root, x) << endl;
		if (op == 5) cout << find_pre(x) << endl;
		if (op == 6) cout << find_next(x) << endl;
	}
    return 0;
}

// ============================================================
//  P3391 文艺平衡树
// ============================================================
#else

pair<Node*, Node*> split_rk (Node *p, int rk) {
    if (p == nl) return {nl, nl};
    p->push_down();
    if (siz(p->ls) + p->cnt <= rk) {
        auto t = split_rk(p->rs, rk - p->cnt - siz(p->ls));
        p->rs = t.st;  p->upd();
        return {p, t.nd};
    }
    else {
        auto t = split_rk(p->ls, rk);
        p->ls = t.nd;  p->upd();
        return {t.st, p};
    }
}

void insert (int val) {
    root = merge(root, new Node(val));
}

void rev (int l, int r) {
    auto t1 = split_rk(root, l - 1);
    auto t2 = split_rk(t1.nd, r - l + 1);
    if (t2.st != nl) t2.st->lazy ^= 1;
    root = merge(merge(t1.st, t2.st), t2.nd);
}

void dfs (Node *p) {
    if (p == nl) return;
    p->push_down();
    dfs(p->ls);
    for (int i = 0; i < p->cnt; i++)    
        cout << p->val << ' ';
    dfs(p->rs);
}

signed main () {
    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    srand(time(0));
    int n, m;
	cin >> n >> m;
    for (int i = 1; i <= n; i++) {
		insert(i);
	}

    while (m--) {
        int l, r;
		cin >> l >> r;
        rev(l, r);
    }
    dfs(root);
    return 0;
}
#endif