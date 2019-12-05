#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMediaPlayer>
#include <QMediaPlaylist>
#include <QDir>
#include <QVector>
#include <tinyxml.h>
#include <tinystr.h>
#include <QDebug>
#include <QListWidgetItem>
#include "LrcDecoder.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    QMediaPlayer* m_player;
    QMediaPlaylist* m_list;
    QVector<QString> m_play_list_name; //播放的名字
    QString pre_path;
    QString m_cur_playing; //当前播放的name
    QString m_pre_lrc_path; //歌词前缀
    
    LrcDecoder m_lrc; //歌词解析类    
    
    int m_cur_play_tag = 0; //当前播放选项 单曲循环....
    enum PLAY_TAG {
        ONE_LOOP, //单曲循环
        LIST_ORDER, //顺序播放
        RANDOM //随机播放
    };
    
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    
private slots:
    
    void on_play_button_clicked();
    
    void on_stop_button_clicked();
    
    bool load_from_xml(QString xmlPath = QString("./config.xml")); //从xml读取播放列表路径
    
    void on_struct_combo_box_activated(const QString &arg1);
    
public slots:
    void on_list_item_clicked(QListWidgetItem* item); //点击列表时播放音乐
    void on_speed_slider_changed(int);
    void on_position_changed(qlonglong); //播放到的位置改变 修改进度条
    void re_play(QMediaPlayer::State state); //重新播放歌曲 视情况而定 单曲循环....
    inline void play() {
//        QString path = m_pre_lrc_path + m_cur_playing;
//        this->m_lrc.load_lrc(path);
        this->m_player->play();
    }
private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
