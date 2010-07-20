#include "mousegraphicsview.h"

MouseGraphicsView::MouseGraphicsView(QWidget *parent) :
    QGraphicsView(parent)
{
}

MouseGraphicsView::~MouseGraphicsView()
{
}

void MouseGraphicsView::mousePressEvent(QMouseEvent *e)
{
    std::cout << e->pos().x() << "," << e->pos().y() << std::endl;
    std::cout << "Left? "<< (e->buttons()&Qt::LeftButton) << " Right? " << (e->buttons()&Qt::RightButton) << std::endl;

    QGraphicsItem *i = scene->itemAt(e->pos());
    QGraphicsPixmapItem *p;
    std::cout << i->type() << std::endl;
    if ( p = dynamic_cast<QGraphicsPixmapItem*>(i) )
    {
        std::cout << "OK!" << std::endl;
    }

    QImage t = p->pixmap().toImage();
    int j, k;
    j = e->pos().x() / 9;
    k = e->pos().y() / 9;
    QPen l;
    l.setColor(Qt::yellow);
    l.setWidth(2);

    scene->addRect(j*9-1, k*9-1, 9, 9, l);
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
