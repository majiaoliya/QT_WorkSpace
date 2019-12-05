//#include <QApplication>
//#include <QWindow>
//#include <QGridLayout>
//#include <QWidget>
//#include <QVBoxLayout>
//#include <QHBoxLayout>
//#include <QPushButton>
//#include <QListWidget>
//#include <QListWidgetItem>
//#include <QDebug>
//using namespace std;
//int win_w = 400, win_h = 300;

//int main(int argc, char *argv[])
//{
//    QApplication app(argc, argv);
//    QWindow win;
//    QWidget w;
//    QVBoxLayout cent;
//    QHBoxLayout hbox[2];
//    for(int i=0; i<2; i++) cent.addLayout(hbox+i), hbox[i].setMargin(0), hbox[i].setSpacing(0);
//    QPushButton button[10];
//    QWidget wid[2];
//    for(int k=2; k--; )
//        wid[k].setContentsMargins(0, 0, 0, 0);
//    int tmp = 0;
//    for(int i=0; i<5; i++) {
//        button[i].setText(std::to_string(i).data());
//        QObject::connect(button+i, &QPushButton::clicked, [&](bool flag)->void{
//            tmp = !tmp;
//            qDebug()<< "pres  " << flag << endl;
//        });
//        hbox[0].addWidget(button+i);
//    }
//    for(int i=5; i<5+3; i++) {
//        button[i].setText(std::to_string(i).data());
//        hbox[1].addWidget(button+i);
//    }

//    QListWidget list_wid;
//    QListWidgetItem item[100];
//    for(int i=0; i<100; i++) {
//        item[i].setText(std::to_string(i).data());
//        list_wid.addItem(item+i);
//    }
//    cent.addWidget(&list_wid);

//    cent.addWidget(wid);
//    cent.setMargin(0);

//    w.setLayout(&cent);

//    win.resize(win_w, win_h);
//    w.show();
//    return app.exec();
//}


















#include <QApplication>
#include <QWindow>
#include <QGridLayout>
#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QListWidget>
#include <QListWidgetItem>
#include <QComboBox>
#include <QDebug>
#include <iostream>
#include <QDir>
#include <QKeyEvent>
#include <QLineEdit>
#include <QMediaPlayer>
#include <QModelIndex>
#include <stdlib.h>

#include <QtGui>
#include <QtAV>

#include <QPropertyAnimation>

#include <playerwindow.h>

#define random(x) (rand()%x)

#define MAXN (2048)
using namespace std;
int win_w = 400, win_h = 300;
int cur = 0; //当前选择的
int item_size; //歌曲个数
int cur_state; //当前播放状态 0暂停   1播放
int cur_tag; //当前选择的状态 0单曲循环    1列表循环     2随机播放

QVBoxLayout* vbox_main; //主窗口的layout
QHBoxLayout* hbox[2]; //hbox[0]放列表, hbox[1]放播放窗口和进度条

QListWidget* list_wid; //列表
QListWidgetItem* list_items[MAXN]; //歌曲item
QPushButton* btn_play; //播放按钮
const char PLAYING[] = "▢";
const char STOPING[] = "▷";
QString btn_play_text = PLAYING;

QSlider* sld_play; //播放进度条
QComboBox* btn_select; //下拉选择单曲循环,随机播放,列表播放

QString song_path = "/home/majiao/my_mount/Xubuntu_Work_Space/From_Windows/kugou/";

QLineEdit* input; //输入框

QMediaPlayer* music_player; //音乐播放

using namespace QtAV;

PlayerWindow* movie_wid;

QPropertyAnimation *show_play; //显示动画
QPropertyAnimation *hide_play; //隐藏动画

void play(QString& str) {
    int n = str.length();
    //弱智级别的用if else过滤视频格式mp4, avi, rmvb ...
    if(str[n-1]=='4' && str[n-2]=='p' && str[n-3]=='m') { //mp4
        qDebug() << "play mp4" << endl;
    } else { //播放音频
        if(!cur_state) { //当前状态try stop
            music_player->pause();
        } else {
            if(music_player->state() == QMediaPlayer::State::StoppedState || cur_state == 2)
                music_player->setMedia(QUrl::fromLocalFile(song_path+str));
            music_player->play();
        }
        list_wid->setCurrentRow(cur);
    }
}

class MyWidget : public QWidget {
public :
    MyWidget(QWidget* parent=nullptr) : QWidget(parent) { }
    virtual ~MyWidget() { }
    virtual void keyPressEvent(QKeyEvent* event) {
        int page = 5;
        if(event->key() == Qt::Key_J) {
            cur = (cur+1) % item_size; //j下
        } else if(event->key() == Qt::Key_K) {
            cur = cur ? cur-1 : item_size; //k上
        } else if ((event->modifiers() == Qt::ControlModifier) && (event->key() == Qt::Key_F)) {
            cur = (cur+page) % item_size; //ctrl+f下翻页
        } else if ((event->modifiers() == Qt::ControlModifier) && (event->key() == Qt::Key_B)) {
            cur = (cur-page+item_size) % item_size; //ctrl+b上翻页
        } else if(event->key() == 47) {
            input->show();
            input->setFocus();
        } else if(event->key() == 16777216) { //ESC隐藏input
            input->hide();
            this->setFocus();
            input->setText("");
        } else if(event->key() == 16777220) { //Enter选择cur
            if(!input->text().isEmpty()) {
                int tmp = input->text().toInt();
                if(tmp >=0 && tmp <= item_size) cur = tmp;
            }
            input->hide();
            input->setText("");
            this->setFocus();
        } else if(event->key() == 32) { //Space 播放当前
            qDebug() << "try paly " << cur << endl;
            QString s = list_items[cur]->toolTip();
            play(s);
        } else if(event->key() == 43) { // +音量增加5
            music_player->setVolume(music_player->volume()+5);
        } else if(event->key() == 45) { // -音量减少5
            music_player->setVolume(music_player->volume()-5);
        }

        list_wid->setCurrentRow(cur);
        qDebug() << event->key() << endl;
    }

//    virtual void enterEvent(QEvent *event) {
//        void init_player();
//        init_player();
//        show_play->start();
//    }
//    virtual void leaveEvent(QEvent *event) {
//        void init_player();
//        hide_play->start();
//    }

public slots:
    void change_tag(int idx) {
        qDebug() << "change idx " << idx << endl;
    }
};
MyWidget* wid_main; //主窗口

#define debug

void init_player() {
//    show_play = new QPropertyAnimation(btn_play, "geometry");
//    show_play->setDuration(200);
//    QRect now = btn_play->geometry();
//    QRect nxt = now;
//    nxt.setWidth(0);
//    show_play->setStartValue(now);
//    show_play->setEndValue(nxt);

//    hide_play = new QPropertyAnimation(btn_play, "geometry");
//    hide_play->setStartValue(nxt);
//    hide_play->setEndValue(now);
}

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    srand(time(0));
    cur_state = 2;
    { //初始化所有组件 和窗口大小
        wid_main = new MyWidget;
//        wid_main->setFocusPolicy(Qt::StrongFocus); //主窗口获取焦点
        wid_main->setFocus();
        vbox_main = new QVBoxLayout;
        for(int i=0; i<2; i++) hbox[i] = new QHBoxLayout;
        list_wid = new QListWidget;
        QDir dir(song_path);
        QFileInfoList info = dir.entryInfoList(QDir::Files);
        QFileInfoList::iterator infoit = info.begin();
        while(infoit != info.end()) { //读入文件名 到列表
            QString tip = QString::number(item_size);
            tip.append(" ");
            tip.append(infoit->fileName());
            list_items[item_size] = new QListWidgetItem(tip);
            list_items[item_size]->setToolTip(infoit->fileName());
            infoit ++;
            item_size ++;
        }
        btn_play = new QPushButton(btn_play_text);
        wid_main->resize(win_w, win_h);
        sld_play = new QSlider(Qt::Orientation::Horizontal);
        sld_play->setContentsMargins(0, 0, 0, 0);
        input = new QLineEdit;

        btn_select = new QComboBox;
        btn_select->addItem("单曲循环");
        btn_select->addItem("列表循环");
        btn_select->addItem("随机播放");

        music_player = new QMediaPlayer;
        music_player->setVolume(100);

//        movie_wid = new PlayerWindow(); //播放窗口初始化
    }


    { //连接信号槽
        QObject::connect(btn_play, &QPushButton::clicked, [&](){ //播放按钮
            QString str = list_items[cur]->toolTip();
//            cout << btn_play->geometry().x() << " " << btn_play->geometry().y() << " "
//                 << btn_play->geometry().width() << " " << btn_play->geometry().height() << endl;
            cur_state = !cur_state;
            btn_play->setText(cur_state ? PLAYING : STOPING);
            play(str);
            //init_player();
            //show_play->start();
            wid_main->setFocus();
        });
        QObject::connect(list_wid, &QListWidget::clicked, [](const QModelIndex &index){ //单击选择
            cur = index.row();
            int tmp = cur_tag;
            cur_tag = 0;
            cur_state = 2;
            QString str = list_items[cur]->toolTip();
            play(str);
            cout << "click try play " << cur << endl;
            wid_main->setFocus();
            cur_tag = tmp;
        });
        QObject::connect(music_player, &QMediaPlayer::stateChanged, [](QMediaPlayer::State state){
            cur_tag = btn_select->currentIndex();
            if(state == QMediaPlayer::State::StoppedState && cur_tag == 2) { //随机播放
                cur = random(item_size);
                QString str = list_items[cur]->toolTip();
                play(str);
            } else if(state == QMediaPlayer::State::StoppedState && cur_tag == 1) { //列表循环
                cur = (cur+1) % item_size;
                QString str = list_items[cur]->toolTip();
                play(str);
            } else if(state == QMediaPlayer::State::StoppedState && cur_tag == 0) {
                music_player->play();
            }
            wid_main->setFocus();
        });
        QObject::connect(music_player, &QMediaPlayer::positionChanged, [&](qint64 pos){
            sld_play->setValue((qint64)(pos*1./music_player->duration() * 100));
            cout << "set pos " << (qint64)(pos*1./music_player->duration() * 100) << endl;
        });
    }

    { //set margin 0
        wid_main->setContentsMargins(0, 0, 0, 0);
        vbox_main->setMargin(0);
        vbox_main->setSpacing(0);
        for(int i=0; i<2; i++)
            hbox[i]->setMargin(0), hbox[i]->setSpacing(0);
    }

    { // add layout to wid_main
        wid_main->setLayout(vbox_main);
        for(int i=0; i<2; i++)
            vbox_main->addLayout(hbox[i]);
    }

    {
        hbox[0]->addWidget(list_wid);
        for(int i=0; i<item_size; i++) {
            list_wid->addItem(list_items[i]);
        }
        hbox[1]->addWidget(btn_play);
        hbox[1]->addWidget(btn_select);
        hbox[1]->addWidget(sld_play);
        // 播放按钮 : 进度条 = 1 : 2
        hbox[1]->setStretchFactor(btn_play, 1);
        hbox[1]->setStretchFactor(btn_select, 1);
        hbox[1]->setStretchFactor(sld_play, 2);

        vbox_main->addWidget(input);
        input->hide();
#ifdef debug
//        movie_wid->resize(400, 300);
////        vbox_main->addWidget(movie_wid);
//        QString file = "/home/majiao/桌面/ffmpeg_hello/12.mp4";
//        movie_wid->m_player->play(file);
//        movie_wid->show();
#endif
//        vbox_main->addWidget(movie_wid->output.widget());
    }

    wid_main->show();
    return app.exec();
}














