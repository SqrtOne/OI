// https://www.luogu.com.cn/problem/P3805
#include <bits/stdc++.h>
using namespace std;
#define int long long
#define endl '\n'
#define st first
#define nd second

const int N = 2.2e7 + 7;
string s;
int dp[N];

int manacher (string s) {
    string t = "~#";    // `~`防止越界
    for (auto c: s) {
        t += c;
        t += "#";   // 不要写`t=t+c`!! 会TLE!!! QAQ
    }
    int n = t.size();
    int L = 0, R = -1;
    int ans = 0;

    for (int i = 1; i < n; ++i) {
        int j = R + L - i;
        if (i < R) dp[i] = min(dp[j], R - i);
        else dp[i] = 1; 

        while (t[i + dp[i]] == t[i - dp[i]]) 
            dp[i] ++;

        if (i + dp[i] > R) {
            L = i - dp[i];
            R = i + dp[i];
        }

        ans = max(ans, dp[i] - 1);
    }
    return ans;
}

signed main () {
    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    cin >> s;
    cout << manacher(s) << endl;
    return 0;
}