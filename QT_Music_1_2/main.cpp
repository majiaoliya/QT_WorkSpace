#include "mainwindow.h"
#include <QApplication>
#include <QVBoxLayout>

using namespace std;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.SONG_PATH = argv[1];
    w.show();

    return a.exec();
}

/**

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);


       QWidget *widget = new QWidget;
        widget->resize(400, 300);   //

        QVBoxLayout *layout = new QVBoxLayout;
        QMediaPlayer* player = new QMediaPlayer;

        widget->setLayout(layout);

        QFile file("123.mp4");
        if(!file.open(QIODevice::ReadOnly))
            qDebug() << "Could not open file";

        player->setMedia(QUrl::fromLocalFile("/home/majiao/majiao_workspace/Xubuntu_Work_Space/From_Windows/kugou/Tatsu不帕 - カワキヲアメク (家有女友OP).mp3"));
        player->play();
        widget->show();

    return a.exec();
}
*/
