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
        QList<QPushButton*> btnPushlist;//��̬������ť���б�
        QPushButton* btnPush;//��̬������ťָ��
        GameModel * game; // ��Ϸָ��
        GameType game_type; // �洢��Ϸ����
        int clickPosRow, clickPosCol; // �洢�������λ��
        void init_Bot();

    private slots:
        // �����Ѷȵ��˻�
        void on_pushButton_clicked();
        void on_pushButton2_clicked();
        void on_pushButton3_clicked();
        // void on_pushButton4_clicked(); // PVPģʽ
        void slotButtonClicked();//��̬����QPushButton��ť�źŲۺ���
        // void lcdNumberDisplay();
        // int stepByDemon();
};

#endif // MAINWINDOW_H
