#include "mainwindow.h"
#include "ui_mainwindow.h"

QString MainWindow::SONG_PATH = "/home/majiao/my_mount/Xubuntu_Work_Space/From_Windows/kugou";

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    cur_state(0),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    srand(time(0));
    QDir dir(SONG_PATH);
    player = new QMediaPlayer;
    this->playlist = new QMediaPlaylist;
    QFileInfoList info = dir.entryInfoList(QDir::Files);
    QFileInfoList::iterator infoit = info.begin();
    int cnt = 0;
    while(infoit != info.end()) {
        QListWidgetItem* item = new QListWidgetItem(infoit->fileName(), ui->listWidget);
        QString tip = QString::number( ++cnt );
        tip.append(" ");
        tip.append(infoit->fileName());
        item->setToolTip(tip);
        this->playlist->addMedia(QUrl::fromLocalFile(infoit->absoluteFilePath()));
        infoit ++;
    }
//    playlist->setPlaybackMode(QMediaPlaylist::Random); // this random is shit !!!
    playlist->setPlaybackMode(QMediaPlaylist::CurrentItemOnce);
    player->setPlaylist(playlist);

    connect(this->player, SIGNAL(positionChanged(qint64)),
            this, SLOT(re_position(qint64)));

    connect(this->player, SIGNAL(stateChanged(QMediaPlayer::State)),
            this, SLOT(onStateChanged(QMediaPlayer::State)));
}

MainWindow::~MainWindow()
{
    delete ui;
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

void MainWindow::re_position(qint64 pos)
{
    double d = pos*1./this->player->duration();
    ui->horizontalSlider->setValue((int)(d*100));
}

void MainWindow::on_comboBox_currentIndexChanged(int idx)
{
    this->cur_state = idx;
}

void MainWindow::on_listWidget_clicked(const QModelIndex &idx)
{
    this->playlist->setCurrentIndex(idx.row());
    this->player->play();
}

void MainWindow::onStateChanged(QMediaPlayer::State s) {
//    cout << "get the state : " << s << endl; // 0=stop   1=playing   2=puase
    if(s == QMediaPlayer::State::StoppedState) { //finish a song
//        cout << "get change state stop " << this->playlist->currentIndex() << endl;
        int idx = -1;
        if(this->cur_state == MainWindow::_loop) { // loop play a song
            this->player->play();
        } else if(this->cur_state == MainWindow::_rand) { // random play a song
            idx = (rand()%playlist->mediaCount());
            this->ui->listWidget->setCurrentRow(idx);
            this->playlist->setCurrentIndex(idx);
            this->player->play();
        }
    }
}
