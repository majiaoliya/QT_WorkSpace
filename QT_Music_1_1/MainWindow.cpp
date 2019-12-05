#include "MainWindow.h"
#include "ui_MainWindowindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->m_player = new QMediaPlayer(this);
    this->m_list = new QMediaPlaylist(this);
//    connect(this->ui->speed_hor_slider, SIGNAL(valueChanged(int)),
//            this, SLOT(on_speed_slider_changed(int))); //不能拖动改变播放的话 slider就是个摆设...
    connect(this->m_player, SIGNAL(positionChanged(qlonglong)),
            this, SLOT(on_position_changed(qlonglong)));
    connect(this->m_player, SIGNAL(stateChanged(QMediaPlayer::State)),
            this, SLOT(re_play(QMediaPlayer::State)));
    load_from_xml();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_play_button_clicked()
{
    if(this->m_player) this->play();
}

void MainWindow::on_stop_button_clicked()
{
    if(this->m_player) qDebug() << m_player->position(), m_player->pause();
}

/**
 * @brief MainWindow::load_from_xml
 * 
 * xml格式
 * <Config>
 *      <MediaListPath>...</MediaListPath> #文件目录
 *      <LrcListPath>...</LrcListPath>
 * </Config>
 * 
 */
bool MainWindow::load_from_xml(QString xmlPath) {
    bool ret = false;
    QDir path(xmlPath);
    TiXmlDocument doc(xmlPath.toStdString().data());
    doc.LoadFile();
    QString config("Config"), mediaListPath("MediaListPath"), lrcListPath("LrcListPath");
    do {
        TiXmlNode* cfg = doc.FirstChild(config.toStdString().data());
        if(!cfg) { ret = false; break; }
        TiXmlNode* mlp = cfg->ToElement()->FirstChild(mediaListPath.toStdString().data()); //歌曲目录
        if(!mlp) { ret = false; break; }
        qDebug() << "try load : " << mlp->ToElement()->GetText() << endl;
        
        QString tPath = mlp->ToElement()->GetText();
        path.setPath(tPath);
        this->pre_path = tPath;
        int count = path.count();
        for(int i=0,k=0; i<count; i++) {
            if(path[i] != "." && path[i] !="..") {
                this->m_play_list_name.append(path[i]);
                this->ui->play_list_widget->addItem(m_play_list_name[k++]);
            }
        }
        connect(this->ui->play_list_widget, SIGNAL(itemClicked(QListWidgetItem*)),
                this, SLOT(on_list_item_clicked(QListWidgetItem*)));
    } while(0);
    return false;
}

void MainWindow::on_list_item_clicked(QListWidgetItem* item) {
//    if(item) qDebug() << item->text() << endl;
    if(item && this->m_player) {
        this->m_cur_playing = item->text();
        this->m_player->setMedia(QUrl::fromLocalFile(pre_path + item->text()));
        this->play();
    }
}

void MainWindow::on_speed_slider_changed(int value) {
    this->m_player->setPosition(value*.01*this->m_player->duration());
}

void MainWindow::on_position_changed(qlonglong value) {
//    double start = 0, end = this->m_player->
//    qDebug() << value << " " << this->m_player->duration();
    this->ui->speed_hor_slider->setValue(100*((float)value/(float)m_player->duration()));
}

void MainWindow::on_struct_combo_box_activated(const QString &tag)
{
    if(tag == "单曲循环") {
        this->m_cur_play_tag = PLAY_TAG::ONE_LOOP;
    } else if(tag == "随机播放") {
        this->m_cur_play_tag = PLAY_TAG::RANDOM;
    } else if(tag == "顺序播放") {
        this->m_cur_play_tag = PLAY_TAG::LIST_ORDER;
    }
}

void MainWindow::re_play(QMediaPlayer::State state) { //重新播放歌曲 视情况而定 单曲循环...
    if(state == QMediaPlayer::State::StoppedState) { //播放停止 依照当前cur_tag判断如何播放
        
        if(this->m_cur_play_tag == MainWindow::PLAY_TAG::ONE_LOOP) { //单曲循环
            this->play();
        } else if(this->m_cur_play_tag == MainWindow::PLAY_TAG::LIST_ORDER) { //列表播放
            for(int i=0; i<this->m_play_list_name.size(); i++) {
                if(m_play_list_name[i] == this->m_cur_playing) {
                    i++; break;
                }
            }
            this->m_player->setMedia(QUrl::fromLocalFile(this->pre_path+m_cur_playing));
            this->play();
        } else if(this->m_cur_play_tag == MainWindow::PLAY_TAG::RANDOM) {
            int a = 0, b = this->m_play_list_name.size();
            this->m_cur_playing = m_play_list_name[(rand()%(b-a))+ a]; //[a,b)
            this->m_player->setMedia(QUrl::fromLocalFile(this->pre_path+m_cur_playing));
            this->play();
        }
        
    }
} 
