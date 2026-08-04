// https://www.luogu.com.cn/problem/P3378
#include <bits/stdc++.h>
using namespace std;
#define int long long
#define endl '\n'
#define st first
#define nd second

const int N = 1e6 + 7;
int arr[N];
int cnt = 0;

void push_up (int ind) {
    if (ind == 1 || arr[ind / 2] <= arr[ind]) // 小根堆
        return;
    swap(arr[ind], arr[ind / 2]);
    push_up(ind / 2);
}

void push_down (int ind) {
    int L = (ind * 2 <= cnt ? arr[ind * 2] : INT_MAX);
    int R = (ind * 2 + 1 <= cnt ? arr[ind * 2 + 1] : INT_MAX);
    int _min = min(min(L, R), arr[ind]);
    if (_min == arr[ind]) return;
    else if (_min == L) {
        swap(arr[ind * 2], arr[ind]);
        push_down(ind * 2);
    } else if (_min == R) {
        swap(arr[ind * 2 + 1], arr[ind]);
        push_down(ind * 2 + 1);
    }
}

void push (int x) {
    arr[++cnt] = x;
    push_up(cnt);
}

void pop () {
    swap(arr[1], arr[cnt]);
    cnt--;
    push_down(1);
}

int top () {
	if (cnt == 0) return INT_MIN;
	return arr[1];
}

signed main () {
    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    int n;	cin >> n;
	while (n --) {
		int op, x;
		cin >> op;
		if (op == 1) {
			cin >> x;
			push(x);
		} else if (op == 2) {
			cout << top() << endl;
		} else {
			pop();
		}
	}
    return 0;
}