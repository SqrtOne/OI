// OwO
#include <bits/stdc++.h>
using namespace std;
#define int long long
#define endl '\n'
#define st first
#define nd second

int n, m;
int dp[2][1 << 12];

void solve () {
    // 确保 m 是较小维度，减少状态数（2^m）
    if (n < m) swap(n, m);
    
    memset(dp, 0, sizeof(dp));
    int now = 0, old = 1;
    
    // 初始状态：第0行之前的所有格子都已填充（虚拟边界）
    // 全1状态表示轮廓线上所有位置都被占用
    dp[now][(1 << m) - 1] = 1;
    
    // 逐行逐列遍历每个格子
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            // 滚动数组交换，old 是上一格状态，now 是当前格状态
            swap(now, old);
            memset(dp[now], 0, sizeof(dp[now]));
            
            // 枚举所有可能的轮廓线状态 k
            // 位表示：1=已被占用，0=空闲
            for (int k = 0; k < (1 << m); ++k) {
                // 转移1：当前格子不放骨牌（仅当上方格子已被占用时可行）
                // 条件：k的最高位（上方格子）为1
                // 操作：左移一位（移除最高位），最低位补0（当前格子不占用）
                if (k & 1 << (m - 1)) 
                    dp[now][(k << 1) & (~(1 << m))] += dp[old][k];
                
                // 转移2：竖放骨牌（覆盖当前格和上方格）
                // 条件：i > 0（不是第一行）且上方格子为空
                // 操作：左移一位，最低位补1（占用当前格）
                if (i && !(k & 1 << (m - 1))) 
                    dp[now][(k << 1) ^ 1] += dp[old][k];
                
                // 转移3：横放骨牌（覆盖当前格和左方格）
                // 条件：j > 0（不是第一列），左边格子为空（最低位为0），上方格子被占用
                // 操作：左移一位，最低两位都置1（占用当前格和左边格）
                if (j && (!(k & 1)) && (k & 1 << (m - 1)))
                    dp[now][((k << 1) | 3) & (~(1 << m))] += dp[old][k];
            }
        }
    }
    
    // 最终状态：所有格子填满，轮廓线全为1
    cout << dp[now][(1 << m) - 1] << endl;
}

signed main () {
    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    while (cin >> n >> m && n) {
        solve();
    }
    return 0;
}