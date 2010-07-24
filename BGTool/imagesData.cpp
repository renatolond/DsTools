#include "imagesData.h"

void imagesData::createBgMatrix(int height, int width)
{
    bgmatrix_height = height;
    bgmatrix_width = width;
    bgmatrix = new int*[bgmatrix_height];
    for ( int i = 0 ; i < bgmatrix_height ; i++ )
    {
        bgmatrix[i] = new int[bgmatrix_width];
    }
}

void imagesData::importPng(QGraphicsView *vView, QGraphicsView *spView, QGraphicsView *selView)
{
    visualizationView = vView;
    spritesView = spView;
    selectedView = selView;

    QGraphicsView *w = visualizationView;
    QGraphicsView *s = spritesView;
    QGraphicsScene *scn = new QGraphicsScene(w);
    QGraphicsScene *sScn = new QGraphicsScene(s);

    w->setScene(scn);
    s->setScene(sScn);

    QPixmap pix("../gfx/teste.png");

    QImage img(pix.toImage());
    int newHeight = pix.height()/8-1 + pix.height();
    int newWidth = pix.width()/8-1 + pix.width();
    QImage imgGrid;
    imgGrid = QImage(newWidth, newHeight, img.format());
    visualizationGrid = imgGrid;

    std::cout << "Height " << newHeight << "; Width " << newWidth << std::endl;

    imgGrid.fill(QColor(0,0,0).rgb());
    {
        int i; int j;
        int startI; int startJ;
        startI = startJ = 0;

        int spritesI = pix.height() / 8;
        int spritesJ = pix.width() / 8;

        createBgMatrix(spritesI,spritesJ);

        for ( i = 0 ; i < spritesI ; i++ )
        {
            for ( j = 0 ; j < spritesJ ; j++ )
            {
                QImage sprite = QImage(8,8,img.format());
                for ( int k = 0 ; k < 8 ; k++ )
                {
                    for ( int l = 0 ; l < 8 ; l++ )
                    {
                        sprite.setPixel(l,k,img.pixel(j*8 + l,i*8+k));
                        imgGrid.setPixel(j*9+l,i*9+k, img.pixel(j*8 + l,i*8+k));
                    }
                }

                QImage sprite2, sprite3, sprite4;
//                sprite2 = sprite.transformed(QTransform().rotate(90));
//                sprite3 = sprite.transformed(QTransform().rotate(180));
//                sprite4 = sprite.transformed(QTransform().rotate(270));
                int exists = 0;
                int id = 0;

                for ( std::vector<QImage>::iterator it = sprites.begin(); it != sprites.end() ; it++ )
                {
                    if ( (*it == sprite) || (*it == sprite2) || (*it == sprite3) || (*it == sprite4) )
                    {
                        exists = 1;
                        break;
                    }
                    id++;
                }
                bgmatrix[i][j] = id;

                if ( !exists )
                {
                    std::cout << "New sprite at " << j*8 << "," << i*8 << std::endl;
                    sprites.push_back(sprite);
                }
            }
        }

        dumpBgMatrix();

        std::cout << "Total sprites: " << sprites.size() << std::endl;
        spriteGrid = QImage(8*4+4, 8*((sprites.size()+3)/4)+((sprites.size()+3)/4), img.format());
        spriteGrid.fill(QColor(255,0,255).rgb());
        int m = 0;
        int n = 0;
        for ( std::vector<QImage>::iterator it = sprites.begin(); it != sprites.end() ; it++ )
        {
            for ( int k = 0 ; k < 8 ; k++ )
            {
                for ( int l = 0 ; l < 8 ; l++ )
                {
                    spriteGrid.setPixel(l+m*9,k+n*9,(*it).pixel(l,k));
                }
            }

            if ( m != 3 ) m++;
            else { m = 0; n++; }
        }
    }

    QImage emptySprite = QImage(8,8,img.format());
    emptySprite.fill(QColor(255,0,255).rgb());

    setSelectedSprite(emptySprite);

    QPixmap pixGrid;
    pixGrid = QPixmap::fromImage(imgGrid);
    QPixmap pixSprGrid;
    pixSprGrid = QPixmap::fromImage(spriteGrid);

    scn->setSceneRect(pixGrid.rect());
    scn->addPixmap(pixGrid);

    sScn->setSceneRect(pixSprGrid.rect());
    sScn->addPixmap(pixSprGrid);
    w->show();
    s->show();
}

void imagesData::exportPng()
{
    QImage exportImg = QImage(bgmatrix_width*8,bgmatrix_height*8,sprites[0].format());

    for ( int i = 0 ; i < bgmatrix_height ; i++ )
    {
        for ( int j = 0 ; j < bgmatrix_width ; j++ )
        {
            for ( int k = 0 ; k < 8 ; k++ )
            {
                for ( int l = 0 ; l < 8 ; l++ )
                {
                    exportImg.setPixel(j*8+l, i*8+k, sprites[bgmatrix[i][j]].pixel(l,k));
                }
            }
        }
    }

    QPixmap pm= QPixmap::fromImage(exportImg);
    pm.save("export.png");
}

void imagesData::highlightSelectedSprite()
{
    if ( selectedSpriteId < 0 ) return;

    QList<QGraphicsItem *> items = visualizationView->scene()->items();
    QList<QGraphicsItem *>::iterator it;
    for ( it = items.begin() ; it != items.end() ; it++ )
    {
        if ( dynamic_cast<QGraphicsPixmapItem*>(*it) == 0 )
        {
            visualizationView->scene()->removeItem(*it);
        }
    }

    for ( int i = 0 ; i < bgmatrix_height ; i++ )
    {
        for ( int j = 0 ; j < bgmatrix_width ; j++ )
        {
            if ( bgmatrix[i][j] == selectedSpriteId )
            {
                QPen l;
                l.setColor(Qt::yellow);
                l.setWidth(2);

                visualizationView->scene()->addRect(j*9-1, i*9-1, 9, 9, l);
            }
        }
    }
}

void imagesData::setSelectedSprite(QImage s)
{
    int spriteI, spriteJ;
    spriteI = spriteJ = 0;

    int boxI, boxJ;
    boxI = boxJ = 0;

    int repeatI, repeatJ;
    repeatI = selectedView->height()/8;
    repeatJ = selectedView->width()/8;

    QGraphicsView *sel = selectedView;
    QGraphicsScene *selScn = new QGraphicsScene(sel);
    sel->setScene(selScn);
    QPixmap selPix(sel->width(), sel->height());
    QImage selImg = QImage(selPix.width(), selPix.height(), s.format());
    selImg.fill(QColor(0,0,0).rgb());
    for ( boxI = 0 ; boxI < sel->height() ; boxI++ )
    {
        if ( boxI/repeatI != (boxI+1)/repeatI )
            continue;
        if ( boxI/repeatI >= s.height() )
            break;
        for ( boxJ = 0 ; boxJ < sel->width() ; boxJ++ )
        {
            if ( boxJ/repeatJ != (boxJ+1)/repeatJ )
                continue;
            if ( boxJ/repeatJ >= s.width() )
                break;
            selImg.setPixel(boxJ, boxI, s.pixel(boxJ/repeatJ, boxI/repeatI));

        }
    }
    selPix = selPix.fromImage(selImg);
    selScn->setSceneRect(0,0,repeatJ*s.width(), repeatI*s.height());
    selScn->addPixmap(selPix);
    sel->show();
}

void imagesData::dumpBgMatrix()
{
    std::cout << "Starting dump.. " << bgmatrix_height << "x" << bgmatrix_width << std::endl;
    for ( int i = 0 ; i < bgmatrix_height ; i++ )
    {
        for ( int j = 0 ; j < bgmatrix_width ; j++ )
        {
            std::cout << " ";
            if ( bgmatrix[i][j] < 10 ) std::cout << "0";
            std::cout << bgmatrix[i][j] << " ";
        }
        std::cout << std::endl;
    }

}

