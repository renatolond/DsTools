#include "spritesgraphicsview.h"

SpritesGraphicsView::SpritesGraphicsView(QWidget *parent) :
    QGraphicsView(parent)
{
//    scene = 0;
    imgData = 0;
    log = logger(__FILE__);
}

SpritesGraphicsView::~SpritesGraphicsView()
{
}

void SpritesGraphicsView::mousePressEvent(QMouseEvent *e)
{
    if ( !scene() )
        return;

    std::ostringstream outs;
    outs << e->pos().x() << "," << e->pos().y() << std::endl;
    outs << "Left? "<< (e->buttons()&Qt::LeftButton) << " Right? " << (e->buttons()&Qt::RightButton) << std::endl;
    log.log(__LINE__, outs);

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

    if ( imgData->selectedSprite.x() >= 0 )
    {
        QGraphicsItem *i = scene()->itemAt(imgData->selectedSprite);

        if ( QGraphicsRectItem *r = dynamic_cast<QGraphicsRectItem *>(i) )
        {
            scene()->removeItem(r);
        }
    }

    QImage selSprite = QImage(sprite_width,sprite_height,t.format());
    {
        int spriteI, spriteJ;
        spriteI = e->pos().y() / (sprite_height+imgData->sprite_grid_height);
        spriteJ = e->pos().x() / (sprite_width+imgData->sprite_grid_width);
        for ( int i = 0 ; i < sprite_height ; i++ )
        {
            for ( int j = 0 ; j < sprite_width ; j++ )
            {
                selSprite.setPixel(j, i, t.pixel(j+spriteJ*(sprite_width+imgData->sprite_grid_width),
                                                 i+spriteI*(sprite_height+imgData->sprite_grid_height)));
            }
        }
    }
    imgData->setSelectedSprite(selSprite);

    int j, k;
    j = e->pos().x() / (sprite_width+imgData->sprite_grid_width);
    k = e->pos().y() / (sprite_height+imgData->sprite_grid_height);

    imgData->selectedSprite.setX(j*(sprite_width+imgData->sprite_grid_width));
    imgData->selectedSprite.setY(k*(sprite_height+imgData->sprite_grid_height));
    imgData->selectedSpriteId = (imgData->selectedSprite.y()*sprites_per_line + imgData->selectedSprite.x())/(sprite_width+imgData->sprite_grid_width);
    outs << "Selected id: " << imgData->selectedSpriteId << std::endl;
    log.log(__LINE__, outs);
    QPen l;
    l.setColor(Qt::yellow);
    l.setWidth(2);
    scene()->addRect(j*(sprite_width+imgData->sprite_grid_width)-1,
                     k*(sprite_height+imgData->sprite_grid_height)-1,
                     (sprite_width+imgData->sprite_grid_width),
                     (sprite_height+imgData->sprite_grid_height), l);
}