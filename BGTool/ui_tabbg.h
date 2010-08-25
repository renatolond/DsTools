/********************************************************************************
** Form generated from reading UI file 'tabbg.ui'
**
** Created: Tue Aug 24 22:37:38 2010
**      by: Qt User Interface Compiler version 4.6.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TABBG_H
#define UI_TABBG_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QFrame>
#include <QtGui/QGraphicsView>
#include <QtGui/QGridLayout>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QPushButton>
#include <QtGui/QSpacerItem>
#include <QtGui/QToolButton>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>
#include "spritesgraphicsview.h"
#include "visualizationgraphicsview.h"

QT_BEGIN_NAMESPACE

class Ui_TabBG
{
public:
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
    QSpacerItem *horizontalSpacer_3;
    QSpacerItem *horizontalSpacer_4;
    QSpacerItem *verticalSpacer;
    QSpacerItem *verticalSpacer_2;
    QPushButton *btExport;
    QFrame *line;
    QGridLayout *gridLayout;
    QGraphicsView *selectedView;
    QSpacerItem *horizontalSpacer_5;
    QSpacerItem *horizontalSpacer_6;
    QGraphicsView *paletteView;
    QFrame *line_2;

    void setupUi(QWidget *TabBG)
    {
        if (TabBG->objectName().isEmpty())
            TabBG->setObjectName(QString::fromUtf8("TabBG"));
        TabBG->resize(416, 452);
        TabBG->setMinimumSize(QSize(416, 452));
        TabBG->setMaximumSize(QSize(416, 452));
        layoutWidget = new QWidget(TabBG);
        layoutWidget->setObjectName(QString::fromUtf8("layoutWidget"));
        layoutWidget->setGeometry(QRect(0, 0, 412, 450));
        verticalLayout = new QVBoxLayout(layoutWidget);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setSizeConstraint(QLayout::SetNoConstraint);
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        horizontalLayout_2->setSizeConstraint(QLayout::SetFixedSize);
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
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(-1, -1, 0, -1);
        gridLayout_2 = new QGridLayout();
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
        QSizePolicy sizePolicy(QSizePolicy::Minimum, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(btDump->sizePolicy().hasHeightForWidth());
        btDump->setSizePolicy(sizePolicy);

        gridLayout_2->addWidget(btDump, 0, 4, 1, 1);

        btHighlight = new QPushButton(layoutWidget);
        btHighlight->setObjectName(QString::fromUtf8("btHighlight"));

        gridLayout_2->addWidget(btHighlight, 2, 0, 1, 1);

        btPaint = new QToolButton(layoutWidget);
        btPaint->setObjectName(QString::fromUtf8("btPaint"));
        sizePolicy.setHeightForWidth(btPaint->sizePolicy().hasHeightForWidth());
        btPaint->setSizePolicy(sizePolicy);
        btPaint->setCheckable(true);

        gridLayout_2->addWidget(btPaint, 0, 2, 1, 1);

        btExportPng = new QPushButton(layoutWidget);
        btExportPng->setObjectName(QString::fromUtf8("btExportPng"));

        gridLayout_2->addWidget(btExportPng, 2, 2, 1, 1);

        horizontalSpacer_3 = new QSpacerItem(10, 26, QSizePolicy::Minimum, QSizePolicy::Minimum);

        gridLayout_2->addItem(horizontalSpacer_3, 2, 3, 1, 1);

        horizontalSpacer_4 = new QSpacerItem(10, 26, QSizePolicy::Minimum, QSizePolicy::Minimum);

        gridLayout_2->addItem(horizontalSpacer_4, 2, 1, 1, 1);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_2->addItem(verticalSpacer, 3, 2, 1, 1);

        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_2->addItem(verticalSpacer_2, 1, 2, 1, 1);

        btExport = new QPushButton(layoutWidget);
        btExport->setObjectName(QString::fromUtf8("btExport"));
        QSizePolicy sizePolicy1(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(btExport->sizePolicy().hasHeightForWidth());
        btExport->setSizePolicy(sizePolicy1);

        gridLayout_2->addWidget(btExport, 2, 4, 1, 1);


        horizontalLayout->addLayout(gridLayout_2);

        line = new QFrame(layoutWidget);
        line->setObjectName(QString::fromUtf8("line"));
        line->setFrameShape(QFrame::VLine);
        line->setFrameShadow(QFrame::Sunken);

        horizontalLayout->addWidget(line);

        gridLayout = new QGridLayout();
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        gridLayout->setSizeConstraint(QLayout::SetNoConstraint);
        selectedView = new QGraphicsView(layoutWidget);
        selectedView->setObjectName(QString::fromUtf8("selectedView"));
        selectedView->setMinimumSize(QSize(71, 71));
        selectedView->setMaximumSize(QSize(71, 71));

        gridLayout->addWidget(selectedView, 0, 1, 1, 1);

        horizontalSpacer_5 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_5, 0, 2, 1, 1);

        horizontalSpacer_6 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_6, 0, 0, 1, 1);

        paletteView = new QGraphicsView(layoutWidget);
        paletteView->setObjectName(QString::fromUtf8("paletteView"));
        paletteView->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignTop);

        gridLayout->addWidget(paletteView, 2, 0, 1, 3);

        line_2 = new QFrame(layoutWidget);
        line_2->setObjectName(QString::fromUtf8("line_2"));
        QSizePolicy sizePolicy2(QSizePolicy::Expanding, QSizePolicy::Fixed);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(line_2->sizePolicy().hasHeightForWidth());
        line_2->setSizePolicy(sizePolicy2);
        line_2->setFrameShape(QFrame::HLine);
        line_2->setFrameShadow(QFrame::Sunken);

        gridLayout->addWidget(line_2, 1, 0, 1, 3);


        horizontalLayout->addLayout(gridLayout);


        verticalLayout->addLayout(horizontalLayout);


        retranslateUi(TabBG);

        QMetaObject::connectSlotsByName(TabBG);
    } // setupUi

    void retranslateUi(QWidget *TabBG)
    {
        TabBG->setWindowTitle(QApplication::translate("TabBG", "Form", 0, QApplication::UnicodeUTF8));
        btConvert->setText(QApplication::translate("TabBG", "Convert", 0, QApplication::UnicodeUTF8));
        btDump->setText(QApplication::translate("TabBG", "Dump", 0, QApplication::UnicodeUTF8));
        btHighlight->setText(QApplication::translate("TabBG", "Highlight", 0, QApplication::UnicodeUTF8));
        btPaint->setText(QApplication::translate("TabBG", "Paint", 0, QApplication::UnicodeUTF8));
        btExportPng->setText(QApplication::translate("TabBG", "Export PNG", 0, QApplication::UnicodeUTF8));
        btExport->setText(QApplication::translate("TabBG", "Export", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class TabBG: public Ui_TabBG {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TABBG_H
