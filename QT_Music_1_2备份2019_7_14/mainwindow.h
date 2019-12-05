#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStringList>
#include <QListWidgetItem>
#include <QDir>
#include <QMediaPlayer>
#include <QUrl>
#include <stdlib.h>
#include <QList>
namespace Ui {
class MainWindow;
};

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    static QString SONG_PATH;
    QStringList song_list; //song names

    QMediaPlayer* player;
    static int cur_state;
    enum State {
        loop, _rand
    };

    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_listWidget_itemClicked(QListWidgetItem *item);

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_horizontalSlider_2_sliderMoved(int position);

    void re_play(QMediaPlayer::State);
    void re_position(qint64);

    void on_radioButton_clicked();

    void on_radioButton_2_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
