#include "MainWindow.h"
#include <QApplication>
#include <QMediaPlayer>
#include <QListWidget>
#include <iostream>
using namespace std;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    
    return a.exec();
}
