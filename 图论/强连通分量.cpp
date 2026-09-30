// https://www.luogu.com.cn/problem/P3387
#include <bits/stdc++.h>
using namespace std;
#define int long long
#define endl '\n'
#define st first
#define nd second

const int N = 1e4 + 7;
vector<int> _map[N];
int point[N];

int dfn[N]; // dfs 序
int low[N]; // 强连通分块中最小 dfs 序编号
int timer = 1;
stack<int> st;  // 用于求强连通分量
bool in_stack[N] = {false};

int scc_timer = 1;  // 处理的强连通分量编号
vector<vector<int>> scc;
int ind_scc[N] = {};
int scc_point[N] = {};
int n, m;

void tarjan (int u) {
    dfn[u] = low[u] = timer++;
    st.push(u); in_stack[u] = true;
    for (auto v: _map[u]) {
        if (!dfn[v]) {  // unvisited
            tarjan(v);
            low[u] = min(low[u], low[v]);
        }
        else if (in_stack[v]) {
            low[u] = min(low[u], dfn[v]);
        }
        // else —— v 访问过且不在栈中忽略
		// 这说明了，v 处于其余的强连通分量中，不在这里
    }

    // 判断当前的 u 是否为某个强连通分量的根
    if (dfn[u] == low[u]) {
        vector<int> sc;
        int v;
        do {
            v = st.top();   st.pop();
            in_stack[v] = false;
            ind_scc[v] = scc_timer;
            scc_point[scc_timer] += point[v];
            sc.push_back(v);
        } while (v != u); // 一直出栈到栈顶元素是 u 为止
        scc.push_back(sc);
        scc_timer ++;
    }
}

int in[N];
set<pair<int, int>> _set;
vector<int> DAG[N];
void new_DAG () {
    for (int u = 1; u <= n; ++u) {
        for (auto v: _map[u]) {
            int su = ind_scc[u];
            int sv = ind_scc[v];
            if (su == sv) continue;
            if (_set.find({su, sv}) != _set.end()) 
                continue;
            _set.insert({su, sv});
            in[sv] ++;
            DAG[su].push_back(sv);
        }
    }
}

int dp[N];
int topo () {
    queue<int> q;
    int ans = 0;
    for (int i = 1; i < scc_timer; ++i) {
        if (in[i] == 0) {
            q.push(i);
            dp[i] = scc_point[i];
            ans = max(ans, dp[i]);
        }
    }

    while (!q.empty()) {
        int u = q.front();  q.pop();
        for (auto v: DAG[u]) {
            dp[v] = max(dp[v], dp[u] + scc_point[v]);
            ans = max(ans, dp[v]);
            if (--in[v] == 0) q.push(v);
        }
    }
    return ans;
}

signed main () {
    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    cin >> n >> m;
    for (int i = 1; i <= n; ++i) cin >> point[i];
    for (int i = 1; i <= m; ++i) {
        int u, v;   cin >> u >> v;
        _map[u].push_back(v);
    }

    scc.push_back(vector<int>());
    for (int i = 1; i <= n; ++i) {
        if (!dfn[i]) tarjan(i);
    }

    new_DAG();
    cout << topo() << endl;
    return 0;
}