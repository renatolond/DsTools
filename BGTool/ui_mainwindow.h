/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created: Sun Jul 25 16:57:04 2010
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
#include <QtGui/QFrame>
#include <QtGui/QGraphicsView>
#include <QtGui/QGridLayout>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QMainWindow>
#include <QtGui/QMenu>
#include <QtGui/QMenuBar>
#include <QtGui/QPushButton>
#include <QtGui/QSpacerItem>
#include <QtGui/QStatusBar>
#include <QtGui/QToolButton>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>
#include "spritesgraphicsview.h"
#include "visualizationgraphicsview.h"

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *action_Open_Project;
    QAction *action_Save_Project;
    QWidget *centralWidget;
    QWidget *layoutWidget;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout_2;
    VisualizationGraphicsView *visualizationView;
    QFrame *lnVr1;
    SpritesGraphicsView *spritesView;
    QFrame *lnHz1;
    QHBoxLayout *horizontalLayout;
    QGridLayout *gridLayout_2;
    QPushButton *btConvert;
    QSpacerItem *horizontalSpacer;
    QSpacerItem *horizontalSpacer_2;
    QToolButton *btDump;
    QPushButton *btHighlight;
    QToolButton *btPaint;
    QPushButton *btExportPng;
    QSpacerItem *verticalSpacer;
    QSpacerItem *horizontalSpacer_3;
    QSpacerItem *horizontalSpacer_4;
    QSpacerItem *verticalSpacer_2;
    QFrame *line;
    QGraphicsView *selectedView;
    QMenuBar *menuBar;
    QMenu *menu_File;
    QMenu *menu_Edit;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(400, 410);
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
        layoutWidget = new QWidget(centralWidget);
        layoutWidget->setObjectName(QString::fromUtf8("layoutWidget"));
        layoutWidget->setGeometry(QRect(0, 0, 396, 364));
        verticalLayout = new QVBoxLayout(layoutWidget);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        visualizationView = new VisualizationGraphicsView(layoutWidget);
        visualizationView->setObjectName(QString::fromUtf8("visualizationView"));
        visualizationView->setMinimumSize(QSize(261, 245));
        visualizationView->setMaximumSize(QSize(261, 245));
        visualizationView->setAlignment(Qt::AlignHCenter|Qt::AlignTop);

        horizontalLayout_2->addWidget(visualizationView);

        lnVr1 = new QFrame(layoutWidget);
        lnVr1->setObjectName(QString::fromUtf8("lnVr1"));
        lnVr1->setFrameShape(QFrame::VLine);
        lnVr1->setFrameShadow(QFrame::Sunken);

        horizontalLayout_2->addWidget(lnVr1);

        spritesView = new SpritesGraphicsView(layoutWidget);
        spritesView->setObjectName(QString::fromUtf8("spritesView"));
        spritesView->setMinimumSize(QSize(45, 241));
        spritesView->setMaximumSize(QSize(45, 241));
        spritesView->setMouseTracking(false);
        spritesView->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignTop);

        horizontalLayout_2->addWidget(spritesView);


        verticalLayout->addLayout(horizontalLayout_2);

        lnHz1 = new QFrame(layoutWidget);
        lnHz1->setObjectName(QString::fromUtf8("lnHz1"));
        lnHz1->setFrameShape(QFrame::HLine);
        lnHz1->setFrameShadow(QFrame::Sunken);

        verticalLayout->addWidget(lnHz1);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(-1, -1, 0, -1);
        gridLayout_2 = new QGridLayout();
        gridLayout_2->setSpacing(6);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        btConvert = new QPushButton(layoutWidget);
        btConvert->setObjectName(QString::fromUtf8("btConvert"));

        gridLayout_2->addWidget(btConvert, 0, 0, 1, 1);

        horizontalSpacer = new QSpacerItem(10, 26, QSizePolicy::Minimum, QSizePolicy::Minimum);

        gridLayout_2->addItem(horizontalSpacer, 0, 1, 1, 1);

        horizontalSpacer_2 = new QSpacerItem(10, 26, QSizePolicy::Minimum, QSizePolicy::Minimum);

        gridLayout_2->addItem(horizontalSpacer_2, 0, 3, 1, 1);

        btDump = new QToolButton(layoutWidget);
        btDump->setObjectName(QString::fromUtf8("btDump"));
        QSizePolicy sizePolicy1(QSizePolicy::Minimum, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(btDump->sizePolicy().hasHeightForWidth());
        btDump->setSizePolicy(sizePolicy1);

        gridLayout_2->addWidget(btDump, 0, 4, 1, 1);

        btHighlight = new QPushButton(layoutWidget);
        btHighlight->setObjectName(QString::fromUtf8("btHighlight"));

        gridLayout_2->addWidget(btHighlight, 2, 0, 1, 1);

        btPaint = new QToolButton(layoutWidget);
        btPaint->setObjectName(QString::fromUtf8("btPaint"));
        sizePolicy1.setHeightForWidth(btPaint->sizePolicy().hasHeightForWidth());
        btPaint->setSizePolicy(sizePolicy1);
        btPaint->setCheckable(true);

        gridLayout_2->addWidget(btPaint, 0, 2, 1, 1);

        btExportPng = new QPushButton(layoutWidget);
        btExportPng->setObjectName(QString::fromUtf8("btExportPng"));

        gridLayout_2->addWidget(btExportPng, 2, 2, 1, 1);

        verticalSpacer = new QSpacerItem(20, 10, QSizePolicy::Minimum, QSizePolicy::Minimum);

        gridLayout_2->addItem(verticalSpacer, 1, 2, 1, 1);

        horizontalSpacer_3 = new QSpacerItem(10, 26, QSizePolicy::Minimum, QSizePolicy::Minimum);

        gridLayout_2->addItem(horizontalSpacer_3, 2, 3, 1, 1);

        horizontalSpacer_4 = new QSpacerItem(10, 26, QSizePolicy::Minimum, QSizePolicy::Minimum);

        gridLayout_2->addItem(horizontalSpacer_4, 2, 1, 1, 1);

        verticalSpacer_2 = new QSpacerItem(10, 26, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_2->addItem(verticalSpacer_2, 3, 2, 1, 1);


        horizontalLayout->addLayout(gridLayout_2);

        line = new QFrame(layoutWidget);
        line->setObjectName(QString::fromUtf8("line"));
        line->setFrameShape(QFrame::VLine);
        line->setFrameShadow(QFrame::Sunken);

        horizontalLayout->addWidget(line);

        selectedView = new QGraphicsView(layoutWidget);
        selectedView->setObjectName(QString::fromUtf8("selectedView"));
        selectedView->setMinimumSize(QSize(71, 71));
        selectedView->setMaximumSize(QSize(71, 71));

        horizontalLayout->addWidget(selectedView);


        verticalLayout->addLayout(horizontalLayout);

        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 400, 19));
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
        btDump->setText(QApplication::translate("MainWindow", "Dump", 0, QApplication::UnicodeUTF8));
        btHighlight->setText(QApplication::translate("MainWindow", "Highlight", 0, QApplication::UnicodeUTF8));
        btPaint->setText(QApplication::translate("MainWindow", "Paint", 0, QApplication::UnicodeUTF8));
        btExportPng->setText(QApplication::translate("MainWindow", "Export PNG", 0, QApplication::UnicodeUTF8));
        menu_File->setTitle(QApplication::translate("MainWindow", "&File", 0, QApplication::UnicodeUTF8));
        menu_Edit->setTitle(QApplication::translate("MainWindow", "&Edit", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
