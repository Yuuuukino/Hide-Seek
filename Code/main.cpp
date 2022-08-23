#include "mainwindow.h"
#include <QApplication>
#include <bits/stdc++.h>
using namespace std;

// 修改 ui 文件后记得
// uic mainwindow.ui > ui_mainwindow.h
int main(int argc, char* argv[]) {
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
