#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <bits/stdc++.h>
#include <QMenu>
#include <QTimer>
#include <QDebug>
#include <QAction>
#include <QPainter>
#include <QMenuBar>
#include <QSpinBox>
#include <QMouseEvent>
#include <QMessageBox>
using namespace std;

MainWindow::MainWindow(QWidget* parent) : 
    QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);
    on_pushButton_clicked();
}
MainWindow::~MainWindow() {
    delete ui;
    //ɾ��QListռ�õ��ڴ漰����б�
    qDeleteAll(btnPushlist);
    btnPushlist.clear();
}
void MainWindow::init_Bot() {
    qDeleteAll(btnPushlist);
    btnPushlist.clear();
    game->step = 0;
    ui->lcdNumber->display(game->step);

    int num = 0, row = game->maxn - 1, col = game->maxn - 1;
    for (int i = 1; i <= row; i++) {
        for (int j = 1; j <= col; j++) {
            btnPush = new QPushButton(this);
            btnPush->setParent(this);
            btnPush->show();
            btnPush->setGeometry(
                (500 / col) * j - 10,
                (500 / row) * i - 10,
                (500 / col) - 5,
                (500 / row) - 5);
            btnPush->setObjectName(QString::number(++num));

            // ���ð�ť��ʾ�ı�
            // change btnPush->setText(QString::number(num));
            // btnPush->setText(" ");
            //���ó�ʼ��ɫ
            if (i == game->angel_x && j == game->angel_y)
                btnPush->setStyleSheet("background-color:rgb(255, 182, 193)");
            else if (game->mp[i][j] == 1)
                btnPush->setStyleSheet("background-color:rgb(255, 255, 255)");
            else
                btnPush->setStyleSheet("background-color:rgb(153, 204, 255)");

            //��QList��ӳ�Ա��
            btnPushlist.append(btnPush);
            //�����źŲۺ���
            connect(btnPushlist.at((i - 1) * col + j - 1), SIGNAL(clicked()), this, SLOT(slotButtonClicked()));
            connect(btnPushlist.at((i - 1) * col + j - 1), SIGNAL(clicked()), this, SLOT(slotButtonClicked()));
        }
    }
}
void MainWindow::on_pushButton_clicked() {
    //���ɰ�ť����
    //row = ui->lineEdit->text().toInt();
    //col = ui->lineEdit_2->text().toInt()
    game = new GameModel;
    game->startGame(BOT1);
    init_Bot();
}
void MainWindow::on_pushButton2_clicked() {
    game = new GameModel;
    game->startGame(BOT2);
    init_Bot();
}
void MainWindow::on_pushButton3_clicked() {
    game = new GameModel;
    game->startGame(BOT3);
    init_Bot();
}
//void MainWindow::on_pushButton4_clicked() {
//    game = new GameModel;
//    game->startGame(PERSON);
//    init_Bot();
//}

void MainWindow::slotButtonClicked() {
    if (game->gameStatus != PLAYING){
        ui->lcdNumber->display(game->step);
        return;
    }
    //��̬����QPushButton��ť�źŲۺ���
    QPushButton* btn = qobject_cast<QPushButton*>(sender());
    //do something������������������
    btn->setStyleSheet("background-color:rgb(153, 204, 255)");
   //��ȡ��ť��������
    QString name = sender()->objectName();
    int index = name.toInt();
    int row = (index - 1) / (game->maxn - 1) + 1, col = (index - 1) % (game->maxn - 1) + 1;
    clickPosRow = row, clickPosCol = col;

    btnPush = btnPushlist.at((game->angel_x - 1) * (game->maxn - 1) + game->angel_y - 1);
    btnPush->setStyleSheet("background-color:rgb(255, 255, 255)");

    bool nxt = game->actionByPerson(clickPosRow, clickPosCol);
    btnPush = btnPushlist.at((game->angel_x - 1) * (game->maxn - 1) +  game->angel_y - 1);
    btnPush->setStyleSheet("background-color:rgb(255, 182, 193)");
    
    //game->print();
    //game->printmp();

    ui->lcdNumber->display(game->step);
    //update(); // �ػ�
}
