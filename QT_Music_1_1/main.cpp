#include "MainWindow.h"
#include <QApplication>
#include <QMediaPlayer>
#include <QListWidget>
#include <QLabel>
#include <QDir>
#include <iostream>
using namespace std;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
//    MainWindow w;
//    w.show();

    QWidget* w = new QWidget();
//    QLabel* l = new QLabel();
    QDir dir("/home/majiao/majiao_workspace/Xubuntu_Work_Space/From_Windows/kugou");
    QFileInfoList* list = dir.entryInfoList();
    for(int i=0; i<list->size(); i++) {
        qDebug() << list->at(i) << endl;
    }
    w->show();
    return a.exec();
}
