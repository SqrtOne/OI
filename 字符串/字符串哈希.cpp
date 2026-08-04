// https://www.luogu.com.cn/problem/P3370
#include <bits/stdc++.h>
using namespace std;
#define int long long
#define endl '\n'
#define st first
#define nd second

const int N = 1e6 + 7;
const int Mod1 = 998244353, Mod2 = 1e9 + 7;
const int base = 131;
vector<int> hash1(N), hash2(N);
vector<int> base1(N), base2(N);

void get_hash (string s) {
    base1[0] = 1;
    base2[0] = 1;
    for (int i = 1; i < s.size(); ++i) {
        base1[i] = base1[i - 1] * base % Mod1;
        base2[i] = base2[i - 1] * base % Mod2;
    }

    hash1[0] = s[0];
    hash2[0] = s[0];
    for (int i = 1; i < s.size(); ++i) {
        hash1[i] = (hash1[i - 1] * base % Mod1 + s[i]) % Mod1;
        hash2[i] = (hash2[i - 1] * base % Mod2 + s[i]) % Mod2;
    }
}

int func1 (int l, int r) {
    return (hash1[r] - hash1[l - 1] * base1[r - l + 1] % Mod1 + Mod1) % Mod1;
}

int func2 (int l, int r) {
    return (hash2[r] - hash2[l - 1] * base2[r - l + 1] % Mod2 + Mod2) % Mod2;
}

signed main () {
    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    int n, cnt = 0;
    cin >> n;
    map<pair<int, int>, int> _map;
    while (n--) {
        string s;
        cin >> s;
        s = ' ' + s;
        get_hash(s);
        int res1 = func1(1, s.size() - 1);
        int res2 = func2(1, s.size() - 1);
        if (!_map[{res1, res2}]) cnt ++;
        _map[{res1, res2}] = 1;
    }
    cout << cnt << endl;
    return 0;
}