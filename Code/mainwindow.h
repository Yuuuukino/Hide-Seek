#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QList>
#include <QDebug>
#include <QGroupBox>
#include <QMainWindow>
#include <QPushButton>
#include <QButtonGroup>
#include "GameModel.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
    Q_OBJECT
    public:
        MainWindow(QWidget* parent = nullptr);
        ~MainWindow();
        Ui::MainWindow* ui;
        QList<QPushButton*> btnPushlist;//动态创建按钮的列表
        QPushButton* btnPush;//动态创建按钮指针
        GameModel * game; // 游戏指针
        GameType game_type; // 存储游戏类型
        int clickPosRow, clickPosCol; // 存储将点击的位置
        void init_Bot();

    private slots:
        // 三个难度的人机
        void on_pushButton_clicked();
        void on_pushButton2_clicked();
        void on_pushButton3_clicked();
        // void on_pushButton4_clicked(); // PVP模式
        void slotButtonClicked();//动态创建QPushButton按钮信号槽函数
        // void lcdNumberDisplay();
        // int stepByDemon();
};

#endif // MAINWINDOW_H
