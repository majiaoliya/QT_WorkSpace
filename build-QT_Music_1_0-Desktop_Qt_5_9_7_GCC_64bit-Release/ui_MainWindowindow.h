/********************************************************************************
** Form generated from reading UI file 'MainWindowindow.ui'
**
** Created by: Qt User Interface Compiler version 5.9.7
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOWINDOW_H
#define UI_MAINWINDOWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QPushButton *play_button;
    QPushButton *stop_button;
    QListWidget *play_list_widget;
    QComboBox *struct_combo_box;
    QSlider *speed_hor_slider;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(400, 291);
        MainWindow->setMinimumSize(QSize(400, 0));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        play_button = new QPushButton(centralWidget);
        play_button->setObjectName(QStringLiteral("play_button"));
        play_button->setGeometry(QRect(0, 210, 101, 41));
        stop_button = new QPushButton(centralWidget);
        stop_button->setObjectName(QStringLiteral("stop_button"));
        stop_button->setGeometry(QRect(0, 250, 101, 41));
        play_list_widget = new QListWidget(centralWidget);
        play_list_widget->setObjectName(QStringLiteral("play_list_widget"));
        play_list_widget->setGeometry(QRect(0, 0, 401, 211));
        struct_combo_box = new QComboBox(centralWidget);
        struct_combo_box->setObjectName(QStringLiteral("struct_combo_box"));
        struct_combo_box->setGeometry(QRect(110, 210, 291, 41));
        speed_hor_slider = new QSlider(centralWidget);
        speed_hor_slider->setObjectName(QStringLiteral("speed_hor_slider"));
        speed_hor_slider->setGeometry(QRect(110, 260, 291, 16));
        speed_hor_slider->setOrientation(Qt::Horizontal);
        MainWindow->setCentralWidget(centralWidget);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "majiao_player_1_0", Q_NULLPTR));
        play_button->setText(QApplication::translate("MainWindow", "Play", Q_NULLPTR));
        stop_button->setText(QApplication::translate("MainWindow", "Stop", Q_NULLPTR));
        struct_combo_box->clear();
        struct_combo_box->insertItems(0, QStringList()
         << QApplication::translate("MainWindow", "\345\215\225\346\233\262\345\276\252\347\216\257", Q_NULLPTR)
         << QApplication::translate("MainWindow", "\345\215\225\346\233\262\346\222\255\346\224\276", Q_NULLPTR)
         << QApplication::translate("MainWindow", "\351\232\217\346\234\272\346\222\255\346\224\276", Q_NULLPTR)
         << QApplication::translate("MainWindow", "\351\241\272\345\272\217\346\222\255\346\224\276", Q_NULLPTR)
        );
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOWINDOW_H
