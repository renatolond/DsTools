#include "spritesgraphicsview.h"

SpritesGraphicsView::SpritesGraphicsView(QWidget *parent) :
    QGraphicsView(parent)
{
//    scene = 0;
    imgData = 0;
}

SpritesGraphicsView::~SpritesGraphicsView()
{
}

void SpritesGraphicsView::mousePressEvent(QMouseEvent *e)
{
    if ( !scene() )
        return;

    std::cout << e->pos().x() << "," << e->pos().y() << std::endl;
    std::cout << "Left? "<< (e->buttons()&Qt::LeftButton) << " Right? " << (e->buttons()&Qt::RightButton) << std::endl;

    QGraphicsItem *i = scene()->itemAt(e->pos());
    QGraphicsPixmapItem *p;

    if ( QGraphicsRectItem *r = dynamic_cast<QGraphicsRectItem *>(i) )
    {
        scene()->removeItem(r);
        return;
    }

    if ( !(p = dynamic_cast<QGraphicsPixmapItem*>(i)) )
        return;

    QImage t = p->pixmap().toImage();
    int j, k;
    j = e->pos().x() / 9;
    k = e->pos().y() / 9;

    if ( imgData->selectedSprite.x() >= 0 )
    {
        QGraphicsItem *i = scene()->itemAt(imgData->selectedSprite);

        if ( QGraphicsRectItem *r = dynamic_cast<QGraphicsRectItem *>(i) )
        {
            scene()->removeItem(r);
        }
    }

    QImage selSprite = QImage(8,8,t.format());
    {
        int spriteI, spriteJ;
        spriteI = e->pos().y() / 9;
        spriteJ = e->pos().x() / 9;
        for ( int i = 0 ; i < 8 ; i++ )
        {
            for ( int j = 0 ; j < 8 ; j++ )
            {
                selSprite.setPixel(j, i, t.pixel(j+spriteJ*9,i+spriteI*9));
            }
        }
    }
    imgData->setSelectedSprite(selSprite);

    imgData->selectedSprite.setX(j*9);
    imgData->selectedSprite.setY(k*9);
    imgData->selectedSpriteId = (imgData->selectedSprite.y()*4 + imgData->selectedSprite.x())/9;
    std::cout << "Selected id: " << imgData->selectedSpriteId << std::endl;
    QPen l;
    l.setColor(Qt::yellow);
    l.setWidth(2);
    scene()->addRect(j*9-1, k*9-1, 9, 9, l);
}
