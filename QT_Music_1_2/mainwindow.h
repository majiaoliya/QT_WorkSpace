#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStringList>
#include <QListWidgetItem>
#include <QDir>
#include <QMediaPlayer>
#include <QMediaPlaylist>
#include <QUrl>
#include <map>
#include <stdlib.h>
#include <QList>

using namespace std;

#ifdef debug
#include <QDebug>
#include <iostream>
using namespace std;
#endif

namespace Ui {
class MainWindow;
};

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    static QString SONG_PATH;
    QMediaPlayer* player;
    QMediaPlaylist* playlist;

    int cur_state;

    enum state {
        _rand, _loop
    };

    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_horizontalSlider_2_sliderMoved(int position);

    void re_position(qint64);

    void on_comboBox_currentIndexChanged(int index);

    void on_listWidget_clicked(const QModelIndex &index);

    void onStateChanged(QMediaPlayer::State);

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
