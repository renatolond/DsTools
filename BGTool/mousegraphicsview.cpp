#include "mousegraphicsview.h"

MouseGraphicsView::MouseGraphicsView(QWidget *parent) :
    QGraphicsView(parent)
{
}

MouseGraphicsView::~MouseGraphicsView()
{
}

/*void MouseGraphicsView::changeEvent(QEvent *e)
{
    QGraphicsView::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
//        ui->retranslateUi(this);
        break;
    default:
        break;
    }
}
*/
