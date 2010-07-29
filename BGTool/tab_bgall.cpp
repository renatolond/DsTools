#include "tab_bgall.h"
#include "ui_tab_bgall.h"

Tab_BgAll::Tab_BgAll(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::tab_bgall)
{
    ui->setupUi(this);
}

Tab_BgAll::~Tab_BgAll()
{
    delete ui;
}

void Tab_BgAll::changeEvent(QEvent *e)
{
    QWidget::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        ui->retranslateUi(this);
        break;
    default:
        break;
    }
}
