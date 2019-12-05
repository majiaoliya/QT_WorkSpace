#include <QtGui>
#include <QtAV>
#include <QSlider>
using namespace QtAV;
class PlayerWindow : public OpenGLWindowRenderer
{
public:
    PlayerWindow(QWindow* parent = 0)
        : OpenGLWindowRenderer(NoPartialUpdate, parent)
    {
        slider = new QSlider;
        player.setRenderer(this);
    }
    void play(const QString& file) {
        setTitle(file);
        player.setFile(file);
        player.play();
    }
protected:
    QSlider* slider;
    virtual void keyPressEvent(QKeyEvent *e) {
        int key = e->key();
        if (key == Qt::Key_Space) {
            player.togglePause();
        } else if (key == Qt::Key_Left) {
            player.seekBackward();
        } else if (key == Qt::Key_Right) {
            player.seekForward();
        } else {
            qDebug() << player.duration() << " pos:" << player.position() << endl;
        }

    }
private:
    AVPlayer player;
};

int main(int argc, char *argv[])
{
    QGuiApplication a(argc, argv);
    PlayerWindow win;
    qDebug() << "sizeof() : " << sizeof(win) << endl;
    win.resize(400, 300);
    win.show();
//    win.play(a.arguments().at(1));
//    win.play("/home/majiao/桌面/ffmpeg_hello/12.mp4");
    return a.exec();
}
