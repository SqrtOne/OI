// https://www.luogu.com.cn/problem/P8306
#include <bits/stdc++.h>
using namespace std;
#define int long long
#define endl '\n'
#define st first
#define nd second

const int N = 3e6 + 7;
int Trie[N][62] = {};
int stop[N] = {};
int cnt = 0;

// 该死，利用ASCII开128直接爆CE了。。。
int get_index (char c) {
    if (c >= '0' && c <= '9') return c - '0';
    else if (c >= 'A' && c <= 'Z') return c - 'A' + 10;
    else if (c >= 'a' && c <= 'z') return c - 'a' + 36;
    else return -1;
}

void insert (string &s) {
    int ind = 0;
    for (int i = 0; i < s.size(); ++i) {
        int c = get_index(s[i]);
        if (!Trie[ind][c]) {
            cnt ++;
            Trie[ind][c] = cnt;
        } 
        ind = Trie[ind][c];
        // 查前缀
        stop[ind] ++;
    }
    // 查完整
    // stop[ind] ++;
}

int find (string &s) {
    int ind = 0;
    for (int i = 0; i < s.size(); ++i) {
        int c = get_index(s[i]);
        if (!Trie[ind][c]) {
            return 0;
        }
        ind = Trie[ind][c];
    }
    return stop[ind];
}

void reset () {
    for (int i = 0; i <= cnt; ++i) {
        memset(Trie[i], 0, sizeof(Trie[i]));
        stop[i] = 0;
    }
    cnt = 0;
}

signed main () {
    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    int T;
    cin >> T;
    while (T--) {
        reset();
        int n, q;
        cin >> n >> q;
        
        while (n--) {
            string s;
            cin >> s;
            insert(s);
        }

        while (q--) {
            string s;
            cin >> s;
            cout << find(s) << endl;
        }
    }
    return 0;
}