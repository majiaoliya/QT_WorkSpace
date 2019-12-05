#include "mainwindow.h"
#include "ui_mainwindow.h"

QString MainWindow::SONG_PATH = "/home/majiao/my_mount/Xubuntu_Work_Space/From_Windows/kugou";
int MainWindow::cur_state = MainWindow::State::loop;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QDir dir(SONG_PATH);
    player = new QMediaPlayer;
    this->song_list = dir.entryList(QDir::Files);
    ui->listWidget->addItems(this->song_list);

    connect(this->player, SIGNAL(stateChanged(QMediaPlayer::State)),
            this, SLOT(re_play(QMediaPlayer::State)));
    connect(this->player, SIGNAL(positionChanged(qint64)),
            this, SLOT(re_position(qint64)));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_listWidget_itemClicked(QListWidgetItem *item)
{
//    printf("play : %s\n", item->text().toStdString().data());
    QString abs_path = MainWindow::SONG_PATH + "/" + item->text();
    MainWindow::player->setMedia(QUrl::fromLocalFile(abs_path));
    MainWindow::player->play();
}

void MainWindow::on_pushButton_clicked()
{
    MainWindow::player->play();
}

void MainWindow::on_pushButton_2_clicked()
{
    MainWindow::player->pause();
}

void MainWindow::on_horizontalSlider_2_sliderMoved(int position)
{
    MainWindow::player->setVolume(position);
}

void MainWindow::re_play(QMediaPlayer::State s) {
    if(s == QMediaPlayer::PausedState) return;

    if(MainWindow::cur_state == MainWindow::State::loop) {
        MainWindow::player->play();
    } else if(s == QMediaPlayer::State::StoppedState && MainWindow::cur_state == MainWindow::State::_rand) {
        int a = 0, b = song_list.size(), r = 0;
        if(b)
            r = (rand()%(b-a))+ a;
//        printf("%d %d\n", b, r);
        QString abs_path = SONG_PATH + "/" + song_list.at(r);
        MainWindow::player->setMedia(QUrl::fromLocalFile(abs_path));
        MainWindow::player->play();
    }
}

void MainWindow::re_position(qint64 pos)
{
    double d = pos*1./this->player->duration();
    ui->horizontalSlider->setValue((int)(d*100));
//    printf("%lld %lld %.2lf %d\n", pos, d, (int)(d*100));
}

void MainWindow::on_radioButton_clicked()
{
    this->cur_state = MainWindow::_rand;
}

void MainWindow::on_radioButton_2_clicked()
{
    this->cur_state = MainWindow::State::loop;
}
