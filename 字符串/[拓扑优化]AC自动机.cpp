// https://www.luogu.com.cn/problem/P5357
#include <bits/stdc++.h>
using namespace std;
#define int long long
#define endl '\n'
#define st first
#define nd second

const int N = 2e6 + 7;
int Trie[N][26] = {};
vector<int> fail(N);
vector<int> stop(N);
int cnt = 0;

void insert (string &s) {
	int ind = 0;
	for (int i = 0; i < s.size(); ++i) {
		int c = s[i] - 'a';
		if (!Trie[ind][c]) 
			Trie[ind][c] = ++cnt;
		ind = Trie[ind][c];
	}
	stop[ind] ++;
}

void build () {
	queue<int> q;
	for (int i = 0; i < 26; ++i) 
		if (Trie[0][i]) 
			q.push(Trie[0][i]);
	
	while (!q.empty()) {
		int u = q.front();	q.pop();
		for (int i = 0; i < 26; ++i) {
			if (Trie[u][i]) {
				fail[Trie[u][i]] = Trie[fail[u]][i]; // 设置fail指针
				q.push(Trie[u][i]);
			} else {
				Trie[u][i] = Trie[fail[u]][i]; // 压缩路径
			}
		}
	}
}

int query (string &s) {
	int p = 0, res = 0;
	for (int i = 0; i < s.size(); ++i) {
		p = Trie[p][s[i] - 'a'];
		int j = p;
		while (j != 0 && stop[j] != -1) {
			res += stop[j];
			stop[j] = -1;
			j = fail[j];
		}
	}
	return res;
}

signed main () {
	ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	int n;
	cin >> n;
	for (int i = 1; i <= n; ++i) {
		string s;	cin >> s;
		insert(s);
	}
	build();
	string T;	cin >> T;
	cout << query(T) << endl;
	return 0;
}