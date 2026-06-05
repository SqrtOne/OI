// https://www.luogu.com.cn/problem/P3808
#include <bits/stdc++.h>
using namespace std;
#define int long long
#define endl '\n'
#define st first
#define nd second

const int N = 2e6 + 7;
int Trie[N][26] = {};
int stop[N] = {};
int fail[N] = {};
int cnt = 0;

int get_index (char c) {
    return c - 'a';
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
    }
    stop[ind] ++;
}

void build () {
    queue<int> q;
    for (int i = 0; i < 26; ++i) {
        if (Trie[0][i]) {
            q.push(Trie[0][i]);
        }
    }

    while (!q.empty()) {
        int x = q.front();
        q.pop();
        for (int i = 0; i < 26; ++i) {
            if (Trie[x][i]) {
                fail[Trie[x][i]] = Trie[fail[x]][i];
                q.push(Trie[x][i]);
            } else Trie[x][i] = Trie[fail[x]][i];
        }
    }
}

int query (string &s) {
    int p = 0, ans = 0;
    for (int i = 0; i < s.size(); ++i) {
        p = Trie[p][get_index(s[i])];
        int j = p;
        while (j != 0 && stop[j] != -1) {
            ans += stop[j];
            stop[j] = -1;
            j = fail[j];
        }
    }
    return ans;
}

signed main () {
    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    int n;
    cin >> n;
    for (int i = 0; i < n; ++i) {
        string s;
        cin >> s;
        insert(s);
    }
    build();
    string t;
    cin >> t;
    cout << query(t) << endl;
    return 0;
}