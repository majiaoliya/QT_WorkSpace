TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        main.cpp
INCLUDEPATH += -I /home/majiao/ffmpeg/ffmpeg-4.2/ffmpeg-lib/inc
#LIBS += -L /home/majiao/ffmpeg/ffmpeg-4.2/ffmpeg-lib/lib

#PKGCONFIG += -std=c++11 -lavdevice -lavfilter -lavformat -lavcodec -lswresample -lswscale -lavutil
LIBS += -L /home/majiao/ffmpeg/ffmpeg-4.2/ffmpeg-lib/lib -lavdevice
LIBS += -L /home/majiao/ffmpeg/ffmpeg-4.2/ffmpeg-lib/lib -lavfilter
LIBS += -L /home/majiao/ffmpeg/ffmpeg-4.2/ffmpeg-lib/lib -lavformat
LIBS += -L /home/majiao/ffmpeg/ffmpeg-4.2/ffmpeg-lib/lib -lavcodec
LIBS += -L /home/majiao/ffmpeg/ffmpeg-4.2/ffmpeg-lib/lib -lswresample
LIBS += -L /home/majiao/ffmpeg/ffmpeg-4.2/ffmpeg-lib/lib -lswscale
LIBS += -L /home/majiao/ffmpeg/ffmpeg-4.2/ffmpeg-lib/lib -lavutil
CONFIG += -std=c++11
