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

	    QBitmap bitMask = QBitmap(gridPix.mask());
	    QPainter painter;

	    std::cout << "Sprite X: "<< spritePt.x() <<
		    ":: Sprite Y: " << spritePt.y() << std::endl;

	    for ( int i = 0 ; i < imgData->sprite_grid_height ; i++ )
	    {
		for ( int j = 0 ; j < imgData->sprite_grid_width ; j++ )
		{
		    std::cout << "My alpha value: " << spriteImg.pixel(j,i) << std::endl;
//			    ":: my blue " << spriteImg.pixel(j,i).blue() <<
//			    ":: my red " << spriteImg.pixel(j,i).red() <<
//			    ":: my green " << spriteImg.pixel(j,i).green() << std::endl;
		}
	    }
//	    painter.begin(&bitMask);
            for ( int i = 0 ; i < sprite_height ; i++ )
            {
                for ( int j = 0 ; j < sprite_width ; j++ )
                {
                    QColor srcColor;
		    srcColor.fromRgba(spriteImg.pixel(j+spritePt.x(),i+spritePt.y()));
		    if ( srcColor.alpha() != 255 )
		    {
//			painter.setPen(Qt::color0);
//			painter.drawPoint(j+p.x()*(sprite_width+imgData->visualization_grid_width),
//					  i+p.y()*(sprite_height+imgData->visualization_grid_height));
		    }
		    else
		    {
//			painter.setPen(Qt::color1);
//			painter.drawPoint(j+p.x()*(sprite_width+imgData->visualization_grid_width),
//					  i+p.y()*(sprite_height+imgData->visualization_grid_height));
		    }
                    gridImg.setPixel(j+p.x()*(sprite_width+imgData->visualization_grid_width),
                                     i+p.y()*(sprite_height+imgData->visualization_grid_height),
                                     srcColor.rgba());
                }
            }
            gridPix = gridPix.fromImage(gridImg);
//	    painter.end();
	    //gridPix.setMask(bitMask);
            pi->setPixmap(gridPix);

            imgData->bgmatrix[p.y()][p.x()] = imgData->selectedSpriteId;

        }

    }
}
