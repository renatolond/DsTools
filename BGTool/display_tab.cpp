#include "display_tab.h" // Class definition

// Project libraries
#include "ui_display_tab.h"
// End of Project libraries

cDisplayTab::cDisplayTab(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::cDisplayTab)
{
    ui->setupUi(this);
}

cDisplayTab::~cDisplayTab()
{
    delete ui;
}
//void Tab_BgAll::completeImgData(imagesData* dataImg0, imagesData* dataImg1)
//{
//    QGraphicsPixmapItem *p0, *p1;
//    QGraphicsItem *gi;

//    p0 = p1 = 0;

//    if ( dataImg0 != 0 && dataImg0->visualizationView != 0 )
//    {
//	gi = dataImg0->visualizationView->scene()->items().at(0);
//	if ( !(p0 = dynamic_cast<QGraphicsPixmapItem*>(gi)) )
//	{
//	    return;
//	}
//    }

//    if ( dataImg1 != 0 && dataImg1->visualizationView != 0 )
//    {
//	gi = dataImg1->visualizationView->scene()->items().at(0);
//	if ( !(p1 = dynamic_cast<QGraphicsPixmapItem*>(gi)) )
//	{
//	    return;
//	}
//    }

//    QGraphicsView *w = ui->graphicsView;
//    QGraphicsScene *scn = new QGraphicsScene(w);
//    w->setScene(scn);
//    if ( p1 != 0 )
//    {
//	scn->setSceneRect(p1->pixmap().rect());
//	scn->addPixmap(p1->pixmap());
//    }
//    if ( p0 != 0 )
//    {
//	scn->addPixmap(p0->pixmap());
//    }
//    w->show();
//}
void cDisplayTab::changeEvent(QEvent *e)
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
