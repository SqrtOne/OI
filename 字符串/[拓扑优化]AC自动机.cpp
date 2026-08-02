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
vector<int> in(N);
vector<int> sum(N);
vector<int> id(N);
int cnt = 0;

void insert (string &s, int ind) {
	int u = 0;
	for (int i = 0; i < s.size(); ++i) {
		int c = s[i] - 'a';
		if (!Trie[u][c]) 
			Trie[u][c] = ++cnt;
		u = Trie[u][c];
	}
	stop[u] ++;
	id[ind] = u;
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
				in[Trie[fail[u]][i]] ++;
				q.push(Trie[u][i]);
			} else {
				Trie[u][i] = Trie[fail[u]][i]; // 压缩路径
			}
		}
	}
}

void query (string &s) {
	int p = 0;
	for (int i = 0; i < s.size(); ++i) {
		p = Trie[p][s[i] - 'a'];
		sum[p] ++;
	}
}

void topu () {
	queue<int> q;
	for (int i = 0; i <= cnt; ++i) {
		if (!in[i])	q.push(i);
	}

	while (!q.empty()) {
		int u = q.front();	q.pop();
		int v = fail[u];
		sum[v] += sum[u];
		if (!(--in[v])) q.push(v);
	}
}

signed main () {
	ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	int n;	cin >> n;
	for (int i = 1; i <= n; ++i) {
		string S;	cin >> S;
		insert(S, i);
	}
	string T;	cin >> T;
	build();	query(T);	topu();
	for (int i = 1; i <= n; ++i) {
		cout << sum[id[i]] << endl;
	}
	return 0;
}