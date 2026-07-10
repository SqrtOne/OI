// https://www.luogu.com.cn/problem/P4113
#include <bits/stdc++.h>
using namespace std;
#define int long long
#define endl '\n'
#define st first
#define nd second

int n, c, m;    // 但是 c 没用哇
const int N = 2e6 + 7;

struct Ques {
    int l, r, id;
    bool operator < (const Ques& y) {
        return r < y.r;
    }
};
vector<Ques> q(N);
vector<int> ans(N);
vector<int> sum(N);
vector<int> v(N);
vector<int> pre(N), cur(N);

int lowbit (int x) {
    return x & -x;
}

void add (int ind, int k) {
    while (ind <= n) {
        sum[ind] += k;
        ind += lowbit(ind);
    }
}

int get (int ind) {
    int res = 0;
    while (ind > 0) {
        res += sum[ind];
        ind -= lowbit(ind);
    }
    return res;
}

signed main () {
    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    cin >> n >> c >> m;     // P1972 输入有差别
    for (int i = 1; i <= n; ++i) {
        cin >> v[i];
    }

    for (int i = 1; i <= m; ++i) {
        cin >> q[i].l >> q[i].r;
        q[i].id = i;
    }
    sort(q.begin() + 1, q.begin() + m + 1);

    int tp = 1;
    for (int i = 1; i <= m; ++i) {
        for (int j = tp; j <= q[i].r; ++j) {
            // [处理全部种类数](https://www.luogu.com.cn/problem/P1972)
            // if (vis[v[j]]) add(vis[v[j]], -1);
            // add(j, 1);  vis[v[j]] = j;

            if (!pre[v[j]]) {   // 第一次出现
                pre[v[j]] = j;
                continue;
            } 

            if (!cur[v[j]]) {   // 第二次出现
                add(pre[v[j]], 1);
                cur[v[j]] = j;
                continue;
            }

            // 第三次出现
            add(pre[v[j]], -1); 
            pre[v[j]] = cur[v[j]];
            add(pre[v[j]], 1);
            cur[v[j]] = j;
        }
        tp = q[i].r + 1;
        ans[q[i].id] = get(q[i].r) - get(q[i].l - 1);
    }

    for (int i = 1; i <= m; ++i) {
        cout << ans[i] << endl;
    }
    return 0;
}