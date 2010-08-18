/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created: Wed Aug 18 18:38:17 2010
**      by: Qt User Interface Compiler version 4.6.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QLocale>
#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QHeaderView>
#include <QtGui/QMainWindow>
#include <QtGui/QMenu>
#include <QtGui/QMenuBar>
#include <QtGui/QStatusBar>
#include <QtGui/QTabWidget>
#include <QtGui/QWidget>
#include "tab_bgall.h"
#include "tabbg.h"

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *action_Open_Project;
    QAction *action_Save_Project;
    QWidget *centralWidget;
    QTabWidget *tabWidget;
    QWidget *tab0;
    Tab_BgAll *widget_all;
    QWidget *tab1;
    TabBG *widget0;
    QWidget *tab2;
    TabBG *widget1;
    QMenuBar *menuBar;
    QMenu *menu_File;
    QMenu *menu_Edit;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(430, 496);
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(MainWindow->sizePolicy().hasHeightForWidth());
        MainWindow->setSizePolicy(sizePolicy);
        MainWindow->setLocale(QLocale(QLocale::English, QLocale::UnitedStates));
        action_Open_Project = new QAction(MainWindow);
        action_Open_Project->setObjectName(QString::fromUtf8("action_Open_Project"));
        action_Save_Project = new QAction(MainWindow);
        action_Save_Project->setObjectName(QString::fromUtf8("action_Save_Project"));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        tabWidget = new QTabWidget(centralWidget);
        tabWidget->setObjectName(QString::fromUtf8("tabWidget"));
        tabWidget->setGeometry(QRect(0, 0, 426, 452));
        tab0 = new QWidget();
        tab0->setObjectName(QString::fromUtf8("tab0"));
        widget_all = new Tab_BgAll(tab0);
        widget_all->setObjectName(QString::fromUtf8("widget_all"));
        widget_all->setGeometry(QRect(0, 0, 416, 422));
        widget_all->setAutoFillBackground(false);
        tabWidget->addTab(tab0, QString());
        tab1 = new QWidget();
        tab1->setObjectName(QString::fromUtf8("tab1"));
        widget0 = new TabBG(tab1);
        widget0->setObjectName(QString::fromUtf8("widget0"));
        widget0->setGeometry(QRect(0, 0, 416, 422));
        tabWidget->addTab(tab1, QString());
        tab2 = new QWidget();
        tab2->setObjectName(QString::fromUtf8("tab2"));
        widget1 = new TabBG(tab2);
        widget1->setObjectName(QString::fromUtf8("widget1"));
        widget1->setGeometry(QRect(0, 0, 416, 422));
        tabWidget->addTab(tab2, QString());
        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 430, 21));
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

        tabWidget->setCurrentIndex(2);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", 0, QApplication::UnicodeUTF8));
        action_Open_Project->setText(QApplication::translate("MainWindow", "&Open Project", 0, QApplication::UnicodeUTF8));
        action_Save_Project->setText(QApplication::translate("MainWindow", "&Save Project", 0, QApplication::UnicodeUTF8));
        tabWidget->setTabText(tabWidget->indexOf(tab0), QApplication::translate("MainWindow", "Bg_All", 0, QApplication::UnicodeUTF8));
        tabWidget->setTabText(tabWidget->indexOf(tab1), QApplication::translate("MainWindow", "Bg_0", 0, QApplication::UnicodeUTF8));
        tabWidget->setTabText(tabWidget->indexOf(tab2), QApplication::translate("MainWindow", "Bg_1", 0, QApplication::UnicodeUTF8));
        menu_File->setTitle(QApplication::translate("MainWindow", "&File", 0, QApplication::UnicodeUTF8));
        menu_Edit->setTitle(QApplication::translate("MainWindow", "&Edit", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
