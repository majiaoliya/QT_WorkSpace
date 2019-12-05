#include <iostream>
#include <QtCore>
#include <QMediaPlayer>
#include <QUrl>
using namespace std;

int main()
{
    QMediaPlayer* player = new QMediaPlayer;
    player->setMedia(QUrl::fromLocalFile("/mnt/majiao_work/Xubuntu_Work_Space/From_Windows/kugou/纯音乐 - 夜的钢琴曲.mp3"));
    player->play();
    
    player = new QMediaPlayer;
//      connect(player, SIGNAL(positionChanged(qint64)), this, SLOT(positionChanged(qint64)));
      player->setMedia(QUrl::fromLocalFile("/mnt/majiao_work/Xubuntu_Work_Space/From_Windows/kugou/纯音乐 - 夜的钢琴曲.mp3"));
      player->setVolume(50);
      player->play();
    
    return 0;
}
