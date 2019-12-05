#ifndef LRCDECODER_H
#define LRCDECODER_H
#include <QString>
#include <QDir>
#include <map>
#include <string>
#include <QDebug>
#include <QRegExp>
#include <QFile>
#include <regex>
using namespace std;
/**
 * 解码歌词
 */
class LrcDecoder 
{
public:
    std::map<int, QString>* p_lines; //保存歌词
    std::map<int, QString>::iterator cur_line;
    
    LrcDecoder();
    
    bool load_lrc(QString& path) { //加载歌词文件
        delete this->p_lines;
        this->p_lines = new std::map<int, QString>;
        QFile file(path);
        file.open(QIODevice::ReadOnly);
        
        char buf[1024];
    //    regex rgx("\\[.*?\\].*+");
        regex rgx("[0-9]+\.[0-9]+\.[0-9]+");
        QString time, lrc;
        while(-1 != file.readLine(buf, sizeof(buf))) {
            QString line(buf);
            QStringList list = line.split("\]");
            if(list.size()>=2) {
                time = QString(list[0].data()+1);
                lrc = list[1];
                int int_time = 0;
                if(regex_match(time.toStdString(), rgx)) {
                    int tag = 1;
                    for(int i=time.length()-1; i>=0; i--) {
                        if(time.at(i) == '.') {
                            tag = 1000;
                        } else if(time.at(i) == ':') {
                            tag = 60000;
                        } else {
                            int_time += tag*(time.toStdString()[i]-'0');
                            tag *= 10;
                        }
                    }
                    (*p_lines)[int_time] += lrc;
                } else {
                    (*p_lines)[0] += line;
                }
            }
            
        }
        
        return false;
    }
    
    QString next_line(qint64 time) {
        if(this->cur_line->first > time) {
            
        }
        
    }
};

#endif // LRCDECODER_H
