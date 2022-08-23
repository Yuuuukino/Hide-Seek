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
		GameType gameType; // ��Ϸģʽ
		GameStatus gameStatus;
		struct Node {
			//�ִ�ĵ�Ĳ����ṹ��
			int i, len, road;
			//���������
			friend bool operator < (const Node& x, const Node& y) {
				if (x.len != y.len) return x.len > y.len;
				return x.road > y.road;
			}
			// ���캯��������
			Node() {};
			Node(int a, int b) { i = 0, len = a, road = b; }
			Node(int a, int b, int c) { i = a, len = b, road = c; }
		};
		Node dfs(int x, int y, int dep, int len) {
			if (!dep) return Node(len, rc[x][y]);
			//�ɴ���ͳ��
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
			cout << " * �Ŵ�����ʹ�� # �Ŵ����ħ���õ��ϰ��� - �ű�ʾ�յ�" << endl;
			cout << "ÿ����ʹ��������" << run << "����һ����������Ϊ��ħ������ڵ�ͼ�������һ���ϰ�" << endl;
			cout << "����ʹΧ������" << "\n\n";
			cout << "��ʹ���ϰ����� " << step << endl;
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
			cout << "��������ϰ������� x �� y�� " << endl;
		}
		bool put_block(int x, int y);
		bool angel_move();
		void init_mp(int n);
		void startGame(GameType type);
		bool actionByPerson(int row, int col);
		bool isWin(); // �ж���Ϸ�Ƿ�ʤ��
		//void updateGameMap(int row, int col);
};
#endif // GameModel_H
