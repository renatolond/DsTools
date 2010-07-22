#include "visualizationgraphicsview.h"
#include "mainwindow.h"

VisualizationGraphicsView::VisualizationGraphicsView(QWidget *parent) :
    QGraphicsView(parent)
{
    btPaintPressed = 0;
    scene = 0;
    imgData = 0;
}

VisualizationGraphicsView::~VisualizationGraphicsView()
{
}

void VisualizationGraphicsView::mousePressEvent(QMouseEvent *e)
{
    if ( !scene )
        return;

    if ( btPaintPressed )
    {
        QPoint p = e->pos();
        std::cout << p.x() << "," << p.y() << std::endl;
        std::cout << "Left? "<< (e->buttons()&Qt::LeftButton) << " Right? " << (e->buttons()&Qt::RightButton) << std::endl;

        QGraphicsItem *i = scene->itemAt(e->pos());
        QGraphicsPixmapItem *pi;
        if ( !(pi = dynamic_cast<QGraphicsPixmapItem*>(i)) )
            return;

        p.setX(p.x()+horizontalScrollBar()->value());
        p.setX(p.x()/9);
        p.setY(p.y()/9);

        std::cout << "Sprite: " << p.x() << "," << p.y() << std::endl;

        if ( imgData->selectedSprite.x() >= 0 )
        {
            QPixmap gridPix = pi->pixmap();
            QImage gridImg = gridPix.toImage();

            QImage spriteImg = imgData->spriteGrid;
            QPoint spritePt = imgData->selectedSprite;

            for ( int i = 0 ; i < 8 ; i++ )
            {
                for ( int j = 0 ; j < 8 ; j++ )
                {
                    gridImg.setPixel(j+p.x()*9,i+p.y()*9,spriteImg.pixel(j+spritePt.x(),i+spritePt.y()));
                }
            }
            gridPix = gridPix.fromImage(gridImg);
            pi->setPixmap(gridPix);

            imgData->bgmatrix[p.y()][p.x()] = imgData->selectedSpriteId;

        }

    }
}
