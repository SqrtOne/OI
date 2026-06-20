// https://www.luogu.com.cn/problem/P2482
#include <bits/stdc++.h>
using namespace std;
#define int long long
#define endl '\n'
#define st first
#define nd second

const int N = 17;
int n, m;
vector<char> input;
int tp = 0;
int FP_num = 0;

void init ();
void main_turn();
void end ();
int find_next(int id);
int find_target(int id);

struct PIG {
	string name;
	vector<char> card;
	int hp = 4;
	int id; // id == 下标

	bool have_bow = false;
	bool jumped = false;
	bool like_bad = false;
	bool used_kill = false;

	int find (char card);
	bool try_use (char &card);
	void turn ();
	void fetch (int i);
	void dead (int from);
	void get_hurt (int from);

	void K (int from);
	void F (int from);
	void N ();
	void W ();
	bool J_help (int from);
	bool J_fight (int from);
} pig[N];

signed main () {
	ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	init();
	main_turn();
	return 0;
}

void PIG::turn () {
	fetch(2);	used_kill = false;
	bool used = true;
	while (used) {
		used = false;
		for (int i = 0; i < card.size(); ++i) {
			if (card[i] == '/') continue;
			bool can_use = try_use(card[i]);
			if (can_use) { 
				used = true;
				break;
			}
		}
	}
}

void PIG::fetch (int i) {
	while (i--) {
		card.push_back(input[tp]);
		if (tp != m - 1) tp ++;
	}
}

void PIG::dead (int from) {
	while (true) {
		int x = find('P');
		if (x != -1) {
			card[x] = '/';
			hp ++;
			if (hp > 0) return;
		} else break;
	}

	card.clear();
	have_bow = false;

	if (name == "FP") {
		FP_num --; 
		if (FP_num == 0) end();
		pig[from].fetch(3);
	} else if (name == "MP") {
		end();
	} else {
		if (from == 0) {	// stand for MP
			pig[0].card.clear();
			pig[0].have_bow = false;
		}
	}

}

int PIG::find (char c) {
	for (int i = 0; i < card.size(); ++i) {
		if (card[i] == c) return i;
	}
	return -1;
}

bool PIG::try_use (char &card) {
	if (card == 'K') {
		if (used_kill && !have_bow) {
			return false;
		} 

		int x = find_next(id);
		if (x == -1) return false;

		card = '/';	used_kill = true;
		if (pig[x].jumped) jumped = true;
		pig[x].K (id);
		return true;
	} 
	
	else if (card == 'P') {
		if (hp != 4) {
			card = '/';
			hp ++;
			return true;
		}
		return false;
	} 
	
	else if (card == 'Z') {
		card = '/';
		have_bow = true;
		return true;
	} 
	
	else if (card == 'F') {
		int x = find_target(id);
		if (x == -1) return false;

		card = '/';	
		if (pig[x].jumped) jumped = true;
		pig[x].F (id);
		return true;
	} 

	else if (card == 'N') {
		card = '/';
		N (); 
		return true;
	}

	else if (card == 'W') {
		card = '/';
		W ();
		return true;
	}

	else return false; // D 和 J 为被动牌
}

void PIG::get_hurt (int from) {
	hp --;
	if (hp <= 0) dead(from);
}

void PIG::K (int from) {
	int x = find('D');
	if (x == -1) get_hurt(from);
	else card[x] = '/';
}

void PIG::F (int from) {
	if (J_help(from)) return;
	if (pig[from].name == "MP" && name == "ZP") {
		get_hurt(from);
		return;
	}
	while (true) {
		int x = find('K');
		if (x != -1) card[x] = '/';
		else {
			get_hurt(from);
			break;
		}

		x = pig[from].find('K');
		if (x != -1) pig[from].card[x] = '/';
		else {
			pig[from].get_hurt(id);
			break;
		}
	}
}

void PIG::N () {
	for (int i = (id + 1) % n; i != id; i = (i + 1) % n) {
		if (pig[i].hp <= 0) continue;
		if (pig[i].J_help(id)) continue;
		int x = pig[i].find('K');
		if (x == -1) {
			pig[i].get_hurt(id);
			if (i == 0 && !jumped) like_bad = true;
		}
		else {
			pig[i].card[x] = '/';
		}
	}
}

void PIG::W () {
	for (int i = (id + 1) % n; i != id; i = (i + 1) % n) {
		if (pig[i].hp <= 0) continue;
		if (pig[i].J_help(id)) continue;
		int x = pig[i].find('D');
		if (x == -1) {
			pig[i].get_hurt(id);
			if (i == 0 && !jumped) like_bad = true;
		}
		else {
			pig[i].card[x] = '/';
		}
	}
}

bool PIG::J_help (int from) {
	if (!jumped) return false;
	bool started = false;
	for (int i = from; i != from || !started; i = (i + 1) % n) {
		if (pig[i].hp <= 0) continue;
		started = true;
		if ((name != "FP" && pig[i].name == "FP") || 
			(name == "FP" && pig[i].name != "FP")) continue;
		int x = pig[i].find('J');
		if (x != -1) {
			pig[i].card[x] = '/';
			pig[i].jumped = true;
			return !pig[i].J_fight(id);
		}
	}
	return false;
}

bool PIG::J_fight(int from) {
	for (int i = (id + 1) % n; i != id; i = (i + 1) % n) {
		if (pig[i].hp <= 0) continue;
		if ((name == "FP" && pig[i].name == "FP") || 
			(name != "FP" && pig[i].name != "FP")) continue;
		int x = pig[i].find('J');
		if (x != -1) {
			pig[i].card[x] = '/';
			pig[i].jumped = true;
			return !pig[from].J_help(i);
		}
	}
	return false;
}

void init () {
	cin >> n >> m;
	for (int i = 0; i < n; ++i) {
		cin >> pig[i].name;
		pig[i].id = i;
		if (pig[i].name == "FP") FP_num ++;
		for (int j = 0; j < 4; ++j) {
			char tmp;	cin >> tmp;
			pig[i].card.push_back(tmp);
		}
	}
	pig[0].jumped = true;
	for (int i = 0; i < m; ++i) {
		char tmp;	cin >> tmp;
		input.push_back(tmp);
	}
}

void end () {
	if (FP_num == 0) cout << "MP" << endl;
	else cout << "FP" << endl;
	for (int i = 0; i < n; ++i) {
		if (pig[i].hp <= 0) cout << "DEAD" << endl;
		else {
			bool is_first = true;
			for (int j = 0; j < pig[i].card.size(); ++j) {
				if (pig[i].card[j] != '/') {
					if (!is_first) cout << ' ';
					cout << pig[i].card[j];
					is_first = false;
				}
			}
			cout << endl;
		}
	}
	exit(0);
}

void main_turn () {
	for (int i = 0; ; i = (i + 1) % n) {
		if (pig[i].hp > 0) pig[i].turn();
	}
}

int find_next (int id) {
	int next = (id + 1) % n;
	while (pig[next].hp <= 0 && next != id) {
		next = (next + 1) % n;	
	}
	if ((pig[id].name == "MP" && ((pig[next].name == "FP" && pig[next].jumped) || 
				(pig[next].like_bad && !pig[next].jumped))) ||
			(pig[id].name == "ZP" && pig[next].name == "FP" && pig[next].jumped) ||
			(pig[id].name == "FP" && (next == 0 || (pig[next].name == "ZP" && pig[next].jumped)))
		) return next;
	else return -1;
}

int find_target (int id) {
	if (pig[id].name == "FP") return 0;
	else {
		for (int i = (id + 1) % n; i != id; i = (i + 1) % n) {
			if (pig[i].hp <= 0) continue;
			if ((pig[id].name == "MP" && ((pig[i].name == "FP" && pig[i].jumped) || 
						(pig[i].like_bad && !pig[i].jumped))) ||
					(pig[id].name == "ZP" && pig[i].name == "FP" && pig[i].jumped)
				) return i;
		}
	}
	return -1;
}