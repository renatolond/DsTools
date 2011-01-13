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
	if ( it == items.end() ) return;
	// Encontramos assim o Pixmap que está sendo usado no VisualizationGrid

        p.setX(p.x()+horizontalScrollBar()->value());
        p.setX(p.x()/(sprite_width+imgData->visualization_grid_width));
        p.setY(p.y()/(sprite_height+imgData->visualization_grid_height));

	outs << "Sprite: " << p.x() << "," << p.y() << std::endl;
        log.log(__LINE__,outs);

        if ( imgData->selectedSprite.x() >= 0 )
        {
            QPixmap gridPix = pi->pixmap();

            QPoint spritePt = imgData->selectedSprite;

	    QBitmap bitMask = QBitmap(gridPix.mask());
	    QPainter painter;


	    int mySpriteIndex;
	    mySpriteIndex = (spritePt.y() / (sprite_height+imgData->sprite_grid_height));
	    mySpriteIndex *= (imgData->spriteGrid.width()+1) / (sprite_width+imgData->sprite_grid_width);
	    mySpriteIndex += (spritePt.x() / (sprite_width+imgData->sprite_grid_width));
	    // Simplemente o índice do sprite que foi selecionado. Desse modo, podemos facilmente
	    // acessar os sprites no vetor. Sprites esses que já estão indexados pela paletta.
	    // Ou seja, basta usarmos o índice na hora de usá-los.

	    painter.begin(&bitMask);
	    for ( int i = 0 ; i < sprite_height ; i++ )
            {
                for ( int j = 0 ; j < sprite_width ; j++ )
                {
		    int cIndex = imgData->sprites[mySpriteIndex].pixelIndex(j,i);
		    QColor srcColor = QColor::fromRgba(imgData->nPalette[cIndex]);

		    int x;
		    int y;

		    x = j+p.x()*(sprite_width+imgData->visualization_grid_width);
		    y = i+p.y()*(sprite_height+imgData->visualization_grid_height);
		    // Aqui nós desenhamos o alpha mask do visualizationGrid.
		    // Caso a cor tenha alpha, ela é desenhado como transparente,
		    // pois no DS só há um bit de transparência.
		    if ( srcColor.alpha() != 255 )
		    {
			painter.setPen(Qt::color0);
			painter.drawPoint(x, y);
		    }
		    else
		    {
			painter.setPen(Qt::color1);
			painter.drawPoint(x, y);
		    }
		    imgData->visualizationGrid.setPixel(x, y, cIndex);
                }
            }
	    painter.end();

	    gridPix = gridPix.fromImage(imgData->visualizationGrid);
	    gridPix.setMask(bitMask);
            pi->setPixmap(gridPix);

            imgData->bgmatrix[p.y()][p.x()] = imgData->selectedSpriteId;
	} // end if ( imgData->selectedSprite.x() >= 0 )
    } // end if ( btPaintPressed )
    else
    {
	// Somente para testar o efeito de mudar uma cor num objeto com formato 8-bit indexed.
	// Apagar depois dos testes!
	QList<QGraphicsItem *> items = scene()->items();
	QList<QGraphicsItem *>::iterator it;
	QGraphicsPixmapItem *pi;

	it = items.begin();
	while ( !(pi = dynamic_cast<QGraphicsPixmapItem*>(*it)) && it != items.end() )
	{
	    it++;
	}
	if ( it == items.end() ) return;

	QPixmap gridPix ;
	QColor q = Qt::darkMagenta;
	imgData->visualizationGrid.setColor(2,q.rgba());
	gridPix = gridPix.fromImage(imgData->visualizationGrid);
	pi->setPixmap(gridPix);

    }
}
