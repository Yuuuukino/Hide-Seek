#include "mainwindow.h"
#include <QApplication>
#include <bits/stdc++.h>
using namespace std;

// �޸� ui �ļ���ǵ�
// uic mainwindow.ui > ui_mainwindow.h
int main(int argc, char* argv[]) {
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}