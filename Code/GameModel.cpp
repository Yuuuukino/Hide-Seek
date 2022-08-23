#include <bits/stdc++.h>
#include "GameModel.h"
using namespace std;


GameModel::GameModel() {}

bool GameModel::check(int x, int y) {
    //检查是否在图中合理位置
    if (x >= maxn || x < 1 || y >= maxn || y < 1) return false;
    //和天使位置冲突
    if (x == angel_x && y == angel_y) return false;
    return true;
}
void GameModel::init_mp(int n) {
    srand((int)time(0));
    for (int i = 1; i < maxn; i++)
        for (int j = 1; j < maxn; j++)
            rc[i][j] = run, mp[i][j] = 1;
    // 对于最外圈特判
    for (int i = 1; i < maxn; i++)
        rc[1][i] = rc[i][1] = rc[maxn - 1][i] = rc[i][maxn - 1] = (run + 2) / 2;
    // 对于四个顶点特判
    rc[1][1] = rc[1][maxn - 1] = rc[maxn - 1][1] = rc[maxn - 1][maxn - 1] = (run + 1) / 3;
    while (n) {
        int tmp = rand() % (maxn * maxn);
        int x = tmp / maxn, y = tmp % maxn;
        if (check(x, y)) put_block(x, y), n--;
    }
}
void GameModel::startGame(GameType type) {
    if (type == BOT1) {
        maxn = max1;
        angel_pre = 4;
    }
    else if (type == BOT2) {
        maxn = max2;
        angel_pre = 5;
    }
    else if(type == BOT3) {
        maxn = max3;
        angel_pre = 6;
    }
    step = 0, run = 4;
    angel_x = maxn / 2, angel_y = maxn / 2;

    vector<int> tmp(maxn + 1);
    rc.resize(maxn + 1, tmp);
    mp.resize(maxn + 1, tmp);

    gameType = type;
    gameStatus = PLAYING;
    init_mp(maxn);
}
bool GameModel::angel_move() {
    //cout << "angel_x: " << angel_x << " angel_y: " << angel_y << endl;
    // AI根据贪心进行移动，根据最坏情况的最好结果进行博弈，但是局部最优解
    vector<Node> nxt;
    for (int i = 0; i < run; i++) {
        int angel_x2 = angel_x + dir[i][0], angel_y2 = angel_y + dir[i][1];
        if (!mp[angel_x2][angel_y2]) continue;
        if (check(angel_x2, angel_y2)) {
            Node p = dfs(angel_x2, angel_y2, angel_pre, 0);
            p.i = i;
            nxt.push_back(p);
        }
    }
    // 不可移动，返回1
    if (nxt.empty()) return 1;
    // 根据重载的运算符进行排序，选取贪心解
    sort(nxt.begin(), nxt.end());
    //cout << "nxt: " << endl;
    //for (auto i : nxt) {
    //	cout << "i.len: " << i.len << " i.road: " << i.road << endl;
    //}
    //cout << endl;
    // 根据最优策略进行移动，返回0
    angel_x += dir[nxt[0].i][0];
    angel_y += dir[nxt[0].i][1];
    return 0;
}
bool GameModel::put_block(int x, int y) {
    if (gameStatus != PLAYING) return false;
    // 读取放置障碍的信息，并进行一系列判断
    if (!check(x, y)) return false;
    if (mp[x][y]) mp[x][y] = rc[x][y] = 0;
    else return false;
    // 成功放置障碍，会使地图中相邻砖块的可走路径减少一
    for (int i = 0; i < run; i++) {
        int tmp_x = x + dir[i][0];
        int tmp_y = y + dir[i][1];
        if (!check(tmp_x, tmp_y)) continue;
        rc[tmp_x][tmp_y]--;
    }
    return true;
}
bool GameModel::isWin() {
    if (!angel_move()) {
        return true;
    }
    gameStatus = WIN;
    return false;
}
bool GameModel::actionByPerson(int row, int col) {
    if (gameStatus != PLAYING) return false;
    if (!put_block(row, col)) return false;
    step++;
    if (!isWin()) { 
        //cout << "Game Over!!!" << endl;
    }
    //else cout << "Game Continue!!!" << endl;
    return true;
}