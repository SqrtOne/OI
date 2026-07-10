// OwO
#include <bits/stdc++.h>
using namespace std;
#define int long long
#define endl '\n'
#define st first
#define nd second

int n;
const int N = 1e5 + 7;
vector<int> v(N);
vector<int> Tree[N];
vector<int> sum(N);
vector<int> ans(N);

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

void dfs (int s) {
    // 总节点数 - 权值 ≤ p[x] 的节点数 = 权值 > p[x] 的节点数
    ans[s] = 0 - (get(n) - get(v[s]));  // 不加子树满足条件的数量
    for (auto &i: Tree[s]) dfs(i);
    ans[s] += get(n) - get(v[s]);       // 加子树后满足条件的数量
    add(v[s], 1);
}

signed main () {
    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    cin >> n;
    vector<pair<int, int>> tmp(n + 7);
    for (int i = 1; i <= n; ++i) {
        cin >> tmp[i].st;   tmp[i].nd = i;
    }
    sort (tmp.begin() + 1, tmp.begin() + 1 + n);
    for (int i = 1; i <= n; ++i) {
        v[tmp[i].nd] = i;
    }

    for (int i = 2; i <= n; ++i) {
        int u;  cin >> u;
        Tree[u].push_back(i);
    }

    dfs(1);
    for (int i = 1; i <= n; ++i) {
        cout << ans[i] << endl;
    }
    return 0;
}