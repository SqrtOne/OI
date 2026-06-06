// https://www.luogu.com.cn/problem/P4777

#include <bits/stdc++.h>
using namespace std;
#define int long long
#define endl '\n'
#define st first
#define nd second

const int N = 1e5 + 7;
int n;
vector<int> a(N), m(N);

int x, y;
int exgcd (int a, int b) {
    if (b == 0) {
        x = 1, y = 0;
        return a;
    } 
    int d = exgcd(b, a % b);
    int t = x;  x = y;
    y = t - a / b * y;
    return d;
}

bool merge (int a1, int m1, int a2, int m2, int& a3, int& m3) {
    int d = exgcd(m1, m2);

    m3 = ((__int128)m1 / d) * m2;               
    // m3 = m1 * m2 / d;

    int k1 = ((__int128)x * (a2 - a1) / d) % m3;
    // int k1 = x * (a2 - a1) / d;

    a3 = (((__int128)k1 % m3) * m1) % m3 + a1;  
    // a3 = k1 * m1 + a1;
    
    a3 = (a3 % m3 + m3) % m3;
    if ((a2 - a1) % d) return false;
    return true;
}

int exCRT () {
    int now_a = a[0], now_m = m[0];
    for (int i = 1; i < n; ++i) {
        int a3, m3;
        if (!merge (now_a, now_m, a[i], m[i], a3, m3)) {
            return -1;
        }
        now_a = a3, now_m = m3;
    }
    return now_a % now_m;
}

signed main () {
    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    cin >> n;
    for (int i = 0; i < n; ++i) {
        cin >> m[i] >> a[i];
    }
    cout << exCRT() << endl;
    return 0;
}