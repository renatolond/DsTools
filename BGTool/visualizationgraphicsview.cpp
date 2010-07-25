#include "visualizationgraphicsview.h"
#include "mainwindow.h"

VisualizationGraphicsView::VisualizationGraphicsView(QWidget *parent) :
        QGraphicsView(parent)
{
    btPaintPressed = 0;
    imgData = 0;
    log = logger(__FILE__);
}

VisualizationGraphicsView::~VisualizationGraphicsView()
{
}

void VisualizationGraphicsView::mousePressEvent(QMouseEvent *e)
{
    if ( !scene() )
        return;

    if ( btPaintPressed )
    {
        QPoint p = e->pos();
        std::ostringstream outs;
        outs << p.x() << "," << p.y() << std::endl;
        outs << "Left? "<< (e->buttons()&Qt::LeftButton) << " Right? " << (e->buttons()&Qt::RightButton) << std::endl;
        log.log(__LINE__, outs);

        QList<QGraphicsItem *> items = scene()->items();
        QList<QGraphicsItem *>::iterator it;
        QGraphicsPixmapItem *pi;

        it = items.begin();
        while ( !(pi = dynamic_cast<QGraphicsPixmapItem*>(*it)) && it != items.end() )
        {
            it++;
        }

        p.setX(p.x()+horizontalScrollBar()->value());
        p.setX(p.x()/(sprite_width+imgData->visualization_grid_width));
        p.setY(p.y()/(sprite_height+imgData->visualization_grid_height));

        outs << "Sprite: " << p.x() << "," << p.y() << std::endl;
        log.log(__LINE__,outs);

        if ( imgData->selectedSprite.x() >= 0 )
        {
            QPixmap gridPix = pi->pixmap();
            QImage gridImg = gridPix.toImage();

            QImage spriteImg = imgData->spriteGrid;
            QPoint spritePt = imgData->selectedSprite;

            for ( int i = 0 ; i < sprite_height ; i++ )
            {
                for ( int j = 0 ; j < sprite_width ; j++ )
                {
                    gridImg.setPixel(j+p.x()*(sprite_width+imgData->visualization_grid_width),
                                     i+p.y()*(sprite_height+imgData->visualization_grid_height),
                                     spriteImg.pixel(j+spritePt.x(),i+spritePt.y()));
                }
            }
            gridPix = gridPix.fromImage(gridImg);
            pi->setPixmap(gridPix);

            imgData->bgmatrix[p.y()][p.x()] = imgData->selectedSpriteId;

        }

    }
}
