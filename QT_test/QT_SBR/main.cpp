#include "mainwindow.h"
#include <QApplication>
#include <QPainter>
#include <QWidget>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QWidget w;
    QPainter per(&w);
    QPen pen(QColor(50, 212, 50), 5);
    per.setPen(pen);
    per.drawLine(110, 110, 500, 500);
    per.drawText(100, 100, "fuck");
    w.show();
    
    return a.exec();
}
