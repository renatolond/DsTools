/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created: Thu Jul 22 16:01:08 2010
**      by: Qt User Interface Compiler version 4.6.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QFrame>
#include <QtGui/QHeaderView>
#include <QtGui/QMainWindow>
#include <QtGui/QMenu>
#include <QtGui/QMenuBar>
#include <QtGui/QPushButton>
#include <QtGui/QStatusBar>
#include <QtGui/QToolButton>
#include <QtGui/QWidget>
#include "mousegraphicsview.h"
#include "visualizationgraphicsview.h"

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *action_Open_Project;
    QAction *action_Save_Project;
    QWidget *centralWidget;
    VisualizationGraphicsView *visualizationView;
    QFrame *lnHz1;
    QFrame *lnVr1;
    QPushButton *btConvert;
    MouseGraphicsView *spritesView;
    QToolButton *btPaint;
    QToolButton *btDump;
    QMenuBar *menuBar;
    QMenu *menu_File;
    QMenu *menu_Edit;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(353, 372);
        action_Open_Project = new QAction(MainWindow);
        action_Open_Project->setObjectName(QString::fromUtf8("action_Open_Project"));
        action_Save_Project = new QAction(MainWindow);
        action_Save_Project->setObjectName(QString::fromUtf8("action_Save_Project"));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        visualizationView = new VisualizationGraphicsView(centralWidget);
        visualizationView->setObjectName(QString::fromUtf8("visualizationView"));
        visualizationView->setGeometry(QRect(0, 0, 261, 245));
        visualizationView->setAlignment(Qt::AlignHCenter|Qt::AlignTop);
        lnHz1 = new QFrame(centralWidget);
        lnHz1->setObjectName(QString::fromUtf8("lnHz1"));
        lnHz1->setGeometry(QRect(0, 250, 271, 16));
        lnHz1->setFrameShape(QFrame::HLine);
        lnHz1->setFrameShadow(QFrame::Sunken);
        lnVr1 = new QFrame(centralWidget);
        lnVr1->setObjectName(QString::fromUtf8("lnVr1"));
        lnVr1->setGeometry(QRect(260, 0, 20, 331));
        lnVr1->setFrameShape(QFrame::VLine);
        lnVr1->setFrameShadow(QFrame::Sunken);
        btConvert = new QPushButton(centralWidget);
        btConvert->setObjectName(QString::fromUtf8("btConvert"));
        btConvert->setGeometry(QRect(0, 260, 71, 21));
        spritesView = new MouseGraphicsView(centralWidget);
        spritesView->setObjectName(QString::fromUtf8("spritesView"));
        spritesView->setGeometry(QRect(280, 0, 71, 241));
        spritesView->setMouseTracking(false);
        spritesView->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignTop);
        btPaint = new QToolButton(centralWidget);
        btPaint->setObjectName(QString::fromUtf8("btPaint"));
        btPaint->setGeometry(QRect(80, 260, 71, 21));
        btPaint->setCheckable(true);
        btDump = new QToolButton(centralWidget);
        btDump->setObjectName(QString::fromUtf8("btDump"));
        btDump->setGeometry(QRect(160, 260, 71, 22));
        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 353, 23));
        menu_File = new QMenu(menuBar);
        menu_File->setObjectName(QString::fromUtf8("menu_File"));
        menu_Edit = new QMenu(menuBar);
        menu_Edit->setObjectName(QString::fromUtf8("menu_Edit"));
        MainWindow->setMenuBar(menuBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        MainWindow->setStatusBar(statusBar);

        menuBar->addAction(menu_File->menuAction());
        menuBar->addAction(menu_Edit->menuAction());
        menu_File->addAction(action_Open_Project);
        menu_File->addAction(action_Save_Project);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", 0, QApplication::UnicodeUTF8));
        action_Open_Project->setText(QApplication::translate("MainWindow", "&Open Project", 0, QApplication::UnicodeUTF8));
        action_Save_Project->setText(QApplication::translate("MainWindow", "&Save Project", 0, QApplication::UnicodeUTF8));
        btConvert->setText(QApplication::translate("MainWindow", "Convert", 0, QApplication::UnicodeUTF8));
        btPaint->setText(QApplication::translate("MainWindow", "Paint", 0, QApplication::UnicodeUTF8));
        btDump->setText(QApplication::translate("MainWindow", "Dump", 0, QApplication::UnicodeUTF8));
        menu_File->setTitle(QApplication::translate("MainWindow", "&File", 0, QApplication::UnicodeUTF8));
        menu_Edit->setTitle(QApplication::translate("MainWindow", "&Edit", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
