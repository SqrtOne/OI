// https://www.luogu.com.cn/problem/P3391
#include <bits/stdc++.h>
using namespace std;
#define int long long
#define endl '\n'
#define st first
#define nd second
#define nl nullptr
#define siz(x) (x == nl? 0: x->size)

struct Node {
    int num;
    Node *son[2];
    int size;   // 以当前节点为根的子树结点个数
    int cnt;    // 该数字出现次数
    int rk;
    int lazy;

    Node (int val) {
        num = val;
        son[0] = son[1] = nl;
        size = cnt = 1;
        rk = rand();
        lazy = 0;
    }

    void up () {
        size = cnt;
        if (son[0] != nl) size += son[0]->size;
        if (son[1] != nl) size += son[1]->size;
    }

    void push_down () {
        swap (son[0], son[1]);
        if (son[0] != nl) son[0]->lazy ^= 1;
        if (son[1] != nl) son[1]->lazy ^= 1;
        lazy = 0;
    }

    void check () {
        if (lazy) push_down();
    }
};
Node *root = nl;

pair<Node*, Node*> split (Node *p, int rk) {
    if (p == nl) return {nl, nl};
    p->check();
    if (p->cnt + siz(p->son[0]) <= rk) {
        auto tmp = split(p->son[1], rk - p->cnt - siz(p->son[0]));
        p->son[1] = tmp.st;
        p->up();
        return {p, tmp.nd};
    } else {
        auto tmp = split(p->son[0], rk);
        p->son[0] = tmp.nd;
        p->up();
        return {tmp.st, p};
    }
}

Node* merge (Node *x, Node *y) {
    if (x == nl) return y;
    if (y == nl) return x;
    x->check(); y->check();
    if (x->rk < y->rk) {
        x->son[1] = merge(x->son[1], y);
        x->up(); 
        return x;
    } else {
        y->son[0] = merge(x, y->son[0]);
        y->up(); 
        return y;
    }
}

void insert (int x) {
    auto t1 = split(root, x);
    auto t2 = split(t1.st, x - 1);
    Node *l = t2.st, *mid = t2.nd, *r = t1.nd;
    if (mid == nl) {
        mid = new Node (x);
    } 
    root = merge(merge(l, mid), r);
}

void rev (int l, int r) {
    auto t1 = split(root, l - 1);
    auto t2 = split(t1.nd, r - l + 1);
    Node *L = t1.st, *mid = t2.st, *R = t2.nd;
    if (mid != nl) mid->lazy = 1;
    root = merge(L, merge(mid, R));
}

void dfs (Node *p) {
    if (p == nl) return;
    p->check();
    dfs (p->son[0]);
    cout << p->num << ' ';
    dfs (p->son[1]);
}

signed main () {
    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    int n, m;
    cin >> n >> m;
    for (int i = 1; i <= n; ++i) {
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