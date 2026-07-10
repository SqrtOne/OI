// https://www.luogu.com.cn/problem/P3389
#include <bits/stdc++.h>
using namespace std;
#define int long long
#define db long double
#define endl '\n'
#define st first
#define nd second

const int N = 107;
const db eps = 1e-7;
db v[N][N];
int n;

signed main () {
    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    cin >> n;
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= n + 1; ++j) {
            cin >> v[i][j]; 
        }
    }

    for (int i = 1; i <= n; ++i) {
        // 1.找出 x_i 的系数最大的方程，交换到当前行处理
        int _max = i;
        for (int j = i + 1; j <= n; ++j) {  // 方程 (1) ~ (i) 完成了消元，不再处理
            if (fabs(v[j][i]) > fabs(v[_max][i])) {
                _max = j;
            }
        }
        for (int j = 1; j <= n + 1; ++j) {  // 注意将常数项 b 一同交换
            swap(v[i][j], v[_max][j]);
        }

        // 2.判断解的存在性
        if (fabs(v[i][i]) < eps) {  // 主元为 0
            cout << "No Solution" << endl;
            // (v[i][n + 1] == 0) -> 0*x==0, 有无穷解
            // 反之 -> 0*x!=0，无解
            return 0;
        }
        
        // 3.将主元系数化为 1
        db m = v[i][i];
        for (int j = i; j <= n + 1; ++j) {
            v[i][j] /= m;
        }

        // 4.用加减消元法消去其他所有行的主元
        for (int j = 1; j <= n; ++j) {
            if (i == j) continue;   // 不对自身消元
            db t = v[j][i];
            for (int k = i; k <= n + 1; ++k) {
                v[j][k] -= t * v[i][k];
            }
        }
    }

    for (int i = 1; i <= n; ++i) {
        cout << fixed << setprecision(2) << v[i][n + 1] << endl;
    }
    return 0;
}