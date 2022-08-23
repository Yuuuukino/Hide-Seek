#ifndef GAMEMODEL_H
#define GAMEMODEL_H
#include <bits/stdc++.h>
using namespace std;
const int max1 = 9, max2 = 11, max3 = 13;
const int dir[4][2] = { {0, 1}, {0, -1}, {1, 0}, {-1, 0} };
enum GameType {BOT1, BOT2, BOT3 };
enum GameStatus {PLAYING, WIN};
class GameModel {
	public:
		int maxn;
		int angel_pre, step, run;
		int angel_x, angel_y;
		GameModel();
		vector<vector<int>> mp, rc;
		GameType gameType; // 游戏模式
		GameStatus gameStatus;
		struct Node {
			//抵达的点的参数结构体
			int i, len, road;
			//运算符重载
			friend bool operator < (const Node& x, const Node& y) {
				if (x.len != y.len) return x.len > y.len;
				return x.road > y.road;
			}
			// 构造函数，重载
			Node() {};
			Node(int a, int b) { i = 0, len = a, road = b; }
			Node(int a, int b, int c) { i = a, len = b, road = c; }
		};
		Node dfs(int x, int y, int dep, int len) {
			if (!dep) return Node(len, rc[x][y]);
			//可达点的统计
			vector<Node> nxt;
			for (int i = 0; i < run; i++) {
				int nxt_x = x + dir[i][0], nxt_y = y + dir[i][1];
				if (!check(nxt_x, nxt_y) || !mp[nxt_x][nxt_y]) continue;
				Node tmp = dfs(nxt_x, nxt_y, dep - 1, len + 1);
				tmp.i = i;
				nxt.push_back(tmp);
			}
			//for (auto i : nxt) cout << "i.len: " << i.len << " i.road: " << i.road << endl;
			//cout << endl;
			if (nxt.size() <= 1) return Node(-1, len + nxt.size(), 0);
			sort(nxt.begin(), nxt.end());
			return nxt[1];
		}
		bool check(int x, int y);
		void printmp() {
			cout << "mp: " << endl;
			for (int i = 1; i < maxn - 1; i++) {
				for (int j = 1; j < maxn - 1; j++) {
					cout << mp[i][j] << " ";
				}
				cout << endl;
			}
		}
		void print() {
			cout << " * 号代表天使， # 号代表恶魔放置的障碍， - 号表示空地" << endl;
			cout << "每轮天使可向相邻" << run << "格走一步，而你作为恶魔则可以在地图任意放置一个障碍" << endl;
			cout << "将天使围起来！" << "\n\n";
			cout << "已使用障碍数： " << step << endl;
			cout << "   ";
			for (int i = 1; i < maxn; i++) cout << setw(2) << i << " ";
			cout << endl;
			for (int i = 1; i < maxn; i++) {
				cout << setw(2) << i << " ";
				for (int j = 1; j < maxn; j++) {
					if (i == angel_x && j == angel_y) cout << setw(2) << " * ";
					else cout << setw(2) << (char)('#' + mp[i][j] * 10) << " ";
				}
				cout << endl;
			}
			cout << "输入放置障碍的坐标 x 和 y： " << endl;
		}
		bool put_block(int x, int y);
		bool angel_move();
		void init_mp(int n);
		void startGame(GameType type);
		bool actionByPerson(int row, int col);
		bool isWin(); // 判断游戏是否胜利
		//void updateGameMap(int row, int col);
};
#endif // GameModel_H
