#include <iostream>
#include <QFile>
#include <QStringList>
#include <QDebug>
#include <regex>
#include <string>

using namespace std;

int main()
{
    QFile file("/mnt/majiao_work/Xubuntu_Work_Space/From_Windows/lrc歌词/绯村柯北&灰老板-东流.lrc");
    file.open(QIODevice::ReadOnly);
    
    char buf[1024];
//    regex rgx("\\[.*?\\].*+");
    regex rgx("[0-9]+\.[0-9]+\.[0-9]+");
    QString time, lrc;
    QMap<int, QString> m;
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
                m[int_time] += lrc;
            } else {
                m[0] += line;
            }
        }
        
    }
    
    QMap<int, QString>::iterator iter = m.begin();
    for(; iter!=m.end(); iter++) {
        qDebug() << iter.key() << " : " << iter.value();
    }
    
    return 0;
}
