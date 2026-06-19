// OwO
#include <bits/stdc++.h>
using namespace std;
#define int long long
#define endl '\n'
#define st first
#define nd second
#define nl nullptr

struct Node {
    int num = 0;
    Node *son[2];
    int size = 0;   // 以当前节点为根的子树结点个数
    int cnt = 0;    // 该数字出现次数
    int rk = 0;

    Node (int val) {
        num = val;
        son[0] = son[1] = nl;
        size = cnt = 1;
        rk = rand();
    }

    void up () {
        size = cnt;
        if (son[0] != nl) size += son[0]->size;
        if (son[1] != nl) size += son[1]->size;
    }
};
Node *root = nl;

pair<Node*, Node*> split (Node *p, int x) {
    if (p == nl) return {nl, nl};
    if (p->num <= x) {
        auto tmp = split(p->son[1], x);
        p->son[1] = tmp.st;
        p->up();
        return {p, tmp.nd};

    } else {
        auto tmp = split(p->son[0], x);
        p->son[0] = tmp.nd;
        p->up();
        return {tmp.st, p};
    }
}

array<Node*, 3> split_rk (Node* p, int rk) {
    if (p == nl) return {nl, nl, nl};
    int less = (p->son[0] == nl? 0: p->son[0]->size);

    if (rk <= less) {
        Node *l, *mid, *r;
        auto t = split_rk (p->son[0], rk);
        l = t[0], mid = t[1], r = t[2];
        p->son[0] = r;
        p->up();
        return {l, mid, p};

    } else if (rk <= less + p->cnt) {
        Node *l = p->son[0], *r = p->son[1];
        p->son[0] = p->son[1] = nl;
        p->up();
        return {l, p, r};

    } else {
        Node *l, *mid, *r;
        auto t = split_rk (p->son[1], rk - less - p->cnt);
        l = t[0], mid = t[1], r = t[2];
        p->son[1] = l;
        p->up();
        return {p, mid, r};
    }
}

Node* merge (Node* x, Node* y) {
    if (x == nl && y == nl) return nl;
    if (x != nl && y == nl) return x;
    if (x == nl && y != nl) return y; 

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
    } else {
        mid->size ++;
        mid->cnt ++;
    }
    root = merge(merge(l, mid), r);
}

void del (int x) {
    auto t1 = split(root, x);
    auto t2 = split(t1.st, x - 1);
    Node *l = t2.st, *mid = t2.nd, *r = t1.nd;
    if (mid == nl) {
        return;
    } else if (mid->cnt > 1) {
        mid->cnt --;
        mid->up();
        l = merge(l,mid);
    } else {
        if (t1.st == t2.nd) {
            t1.st = nl;
        }
        delete t2.nd;
        t2.nd = nl;
    }

    root = merge(l, r);
}

int find_rk (int x) {
    auto t1 = split(root, x - 1);
    int ans = (t1.st == nl ? 1 : t1.st->size + 1);
    root = merge(t1.first, t1.second);
    return ans;
}

int find_num (Node *root, int rk) {
    auto tmp = split_rk(root, rk);
    int ans = tmp[1]->num;
    root = merge(merge(tmp[0], tmp[1]), tmp[2]);
    return ans;
}

int find_pre (int x) {
    auto tmp = split(root, x - 1);
    int ans = find_num(tmp.st, tmp.st->size);
    root = merge(tmp.st, tmp.nd);
    return ans;
}

int find_nex (int x) {
    auto tmp = split(root, x);
    int ans = find_num(tmp.nd, 1);
    root = merge(tmp.st, tmp.nd);
    return ans;
}

signed main () {
    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    int n;
    cin >> n;
    while (n--) {
        int op, x;
        cin >> op >> x;
        switch (op) {
            case 1:
                insert(x);
                break;
            case 2:
                del(x);
                break;
            case 3:
                cout << find_rk(x) << endl;
                break;
            case 4:
                cout << find_num(root, x) << endl;
                break;
            case 5:
                cout << find_pre(x) << endl;
                break;
            case 6:
                cout << find_nex(x) << endl; 
                break;
        }
    }
    return 0;
}