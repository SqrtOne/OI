// https://www.luogu.com.cn/problem/P3369
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

void rotate (Node* &p, int dir) {
/* 左旋：也就是让右子节点变成根节点 (dir == 1)
   *         A                 C
   *        / \               / \
   *       B  C    ---->     A   E
   *         / \            / \
   *        D   E          B   D
   */
    Node *tmp = p->son[dir];
    p->son[dir] = tmp->son[1-dir];
    tmp->son[1-dir] = p;
    p->up();    tmp->up();
    p = tmp;
}

void insert (Node* &p, int x) {
    if (p == nl) {
        p = new Node(x); 
        return;
    }

    if (p->num == x) {
        p->cnt ++;
        p->size ++;

    } else if (p->num > x) {
        insert(p->son[0], x);
        if (p->son[0]->rk < p->rk) {
            rotate(p, 0); 
        }
        p->up();

    } else {
        insert(p->son[1], x);
        if (p->son[1]->rk < p->rk) {
            rotate(p, 1); 
        }
        p->up();
    }
}

void del (Node* &p, int x) {
    if (p == nl) return;
    if (p->num > x) {
        del(p->son[0], x);
        p->up();
    } else if (p->num < x) {
        del(p->son[1], x);
        p->up();

    } else {
        if (p->cnt > 1) {
            p->cnt --;
            p->size --;
            return;
        }

        Node *tmp = p;
        if (p->son[0] == nl && p->son[1] == nl) {
            delete p; p = nl;
            return;
        } else if (p->son[0] != nl && p->son[1] == nl) {
            p = p->son[0];
            delete tmp;
            return;
        } else if (p->son[0] == nl && p->son[1] != nl) {
            p = p->son[1];
            delete tmp ;
            return;

        } else {
            int dir = 0;
            if (p->son[1]->rk < p->son[0]->rk) {
                dir = 1;
            } 
            rotate(p, dir);
            del(p->son[1-dir], x);
            p->up();
            return;
        }
    }
}

int find_rk (Node *p, int x) {
    if (p == nl) return 0;
    int lsize = (p->son[0] == nl? 0: p->son[0]->size);
    if (p->num == x) {
        return lsize;
    }

    if (p->num > x) {
        if (p->son[0] == nl) return 0;
        return find_rk(p->son[0], x);
    } else {
        if (p->son[1] == nl) return lsize + p->cnt;
        return lsize + p->cnt + find_rk(p->son[1], x);
    }
}

int find_num (Node *p, int rk) {
    if (p == nl) return -1;
    if (p->size < rk) return -1;
    int less = (p->son[0] == nl)? 0: p->son[0]->size;
    if (rk <= less) return find_num (p->son[0], rk);
    if (rk <= less + p->cnt) return p->num; 
    return find_num (p->son[1], rk - less - p->cnt);
}

int ans = 0;
void find_pre (Node *p, int x) {
    if (p == nl) return;
    if (p->num < x) {
        ans = max(ans, p->num);
        if (p->son[1] != nl)
            find_pre(p->son[1], x);
    } else {
        if (p->son[0] != nl)
            find_pre(p->son[0], x);
    }
}

void find_nex (Node *p, int x) {
    if (p == nl) return;
    if (p->num > x) {
        ans = min(ans, p->num);
        if (p->son[0] != nl) 
            find_nex(p->son[0], x);
    } else {
        if (p->son[1] != nl)
            find_nex(p->son[1], x);
    }
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
                insert(root, x);
                break;
            case 2:
                del(root, x);
                break;
            case 3:
                cout << find_rk(root, x) + 1 << endl;
                break;
            case 4:
                cout << find_num(root, x) << endl;
                break;
            case 5:
                ans = INT_MIN;
                find_pre(root, x);
                cout << ans << endl;
                break;
            case 6:
                ans = INT_MAX;
                find_nex(root, x);
                cout << ans << endl; 
                break;
        }
    }
    return 0;
}
