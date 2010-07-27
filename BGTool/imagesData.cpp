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

void imagesData::findSprites(int pix_height, int pix_width, QImage &img, QImage &imgGrid)
{

    int i; int j;
    int startI; int startJ;
    startI = startJ = 0;

    int spritesI = pix_height / sprite_height;
    int spritesJ = pix_width / sprite_width;

    createBgMatrix(spritesI,spritesJ);

    for ( i = 0 ; i < spritesI ; i++ )
    {
        for ( j = 0 ; j < spritesJ ; j++ )
        {
            QImage sprite = QImage(sprite_width,
                                   sprite_height,
                                   img.format());
            for ( int k = 0 ; k < sprite_height ; k++ )
            {
                for ( int l = 0 ; l < sprite_width ; l++ )
                {
                    sprite.setPixel(l,k,
                                    img.pixel(j*sprite_width  + l,
                                              i*sprite_height + k));
                    imgGrid.setPixel(j*(sprite_width +visualization_grid_width) +l,
                                     i*(sprite_height+visualization_grid_height)+k,
                                     img.pixel(j*sprite_width  + l,
                                               i*sprite_height + k));
                }
            }

            QImage sprite2, sprite3, sprite4;
            //sprite2 = sprite.transformed(QTransform().scale(-1, 1));
            //sprite3 = sprite.transformed(QTransform().scale( 1,-1));
            //sprite4 = sprite.transformed(QTransform().scale(-1,-1));
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
                std::ostringstream outs;
                outs << "New sprite at " << j*sprite_width << "," << i*sprite_height << std::endl;
                log.log(__LINE__, outs);
                sprites.push_back(sprite);
            }
        }
    }

    //dumpBgMatrix();

    std::ostringstream outs;
    outs << "Total sprites: " << sprites.size() << std::endl;
    log.log(__LINE__, outs);
    int sprites_per_column = (sprites.size()/sprites_per_line) + ((sprites.size()%sprites_per_line)?1:0);

    spriteGrid = QImage(sprite_width*sprites_per_line + (sprites_per_line-1)*sprite_grid_width,
                        sprite_height*sprites_per_column + (sprites_per_column-1)*sprite_grid_height,
                        img.format());
    spriteGrid.fill(QColor(255,0,255).rgb());
    int m = 0;
    int n = 0;
    for ( std::vector<QImage>::iterator it = sprites.begin(); it != sprites.end() ; it++ )
    {
        for ( int k = 0 ; k < sprite_height ; k++ )
        {
            for ( int l = 0 ; l < sprite_width ; l++ )
            {
                spriteGrid.setPixel(m*(sprite_width+sprite_grid_width)   + l,
                                    n*(sprite_height+sprite_grid_height) + k,
                                    (*it).pixel(l,k));
            }
        }

        if ( m != sprites_per_line-1 ) m++;
        else { m = 0; n++; }
    }
}

void imagesData::importPng(QGraphicsView *vView, QGraphicsView *spView, QGraphicsView *selView)
{
    visualizationView = vView;
    spritesView = spView;
    selectedView = selView;

    QPixmap pix("../gfx/teste.png");

    QImage img(pix.toImage());
    int newHeight = pix.height() + ((pix.height()/sprite_height)-1)*visualization_grid_height;
    int newWidth = pix.width() + ((pix.width()/sprite_width)-1)*visualization_grid_width;
    QImage imgGrid;
    imgGrid = QImage(newWidth,
                     newHeight,
                     img.format());
    visualizationGrid = imgGrid;


    std::ostringstream outs;
    outs << "Height " << newHeight <<"; Width " << newWidth << std::endl;
    log.log(__LINE__, outs);

    imgGrid.fill(QColor(0,0,0).rgb());
    findSprites(pix.height(), pix.width(), img, imgGrid); // also fill visualizationView and spriteView

    QImage emptySprite = QImage(sprite_width,sprite_height,img.format());
    emptySprite.fill(QColor(255,0,255).rgb());

    setSelectedSprite(emptySprite);

    QPixmap pixGrid;
    pixGrid = QPixmap::fromImage(imgGrid);
    QGraphicsView *w = visualizationView;
    QGraphicsScene *scn = new QGraphicsScene(w);
    w->setScene(scn);
    scn->setSceneRect(pixGrid.rect());
    scn->addPixmap(pixGrid);
    w->show();

    QPixmap pixSprGrid;
    pixSprGrid = QPixmap::fromImage(spriteGrid);
    QGraphicsView *s = spritesView;
    QGraphicsScene *sScn = new QGraphicsScene(s);
    s->setScene(sScn);
    sScn->setSceneRect(pixSprGrid.rect());
    sScn->addPixmap(pixSprGrid);
    s->show();
}

void imagesData::exportPng()
{
    QImage exportImg = QImage(bgmatrix_width*sprite_width,
                              bgmatrix_height*sprite_height,
                              sprites[0].format());

    for ( int i = 0 ; i < bgmatrix_height ; i++ )
    {
        for ( int j = 0 ; j < bgmatrix_width ; j++ )
        {
            for ( int k = 0 ; k < sprite_height ; k++ )
            {
                for ( int l = 0 ; l < sprite_width ; l++ )
                {
                    exportImg.setPixel(j*sprite_width  + l,
                                       i*sprite_height + k,
                                       sprites[bgmatrix[i][j]].pixel(l,k));
                }
            }
        }
    }

    QPixmap pm = QPixmap::fromImage(exportImg);
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

                visualizationView->scene()->addRect(j*(sprite_width+visualization_grid_width)-1,
                                                    i*(sprite_height+visualization_grid_height)-1,
                                                    (sprite_width+visualization_grid_width),
                                                    (sprite_height+visualization_grid_height), l);
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
    repeatI = selectedView->height()/sprite_height;
    repeatJ = selectedView->width()/sprite_width;

    QGraphicsView *sel = selectedView;
    QGraphicsScene *selScn = new QGraphicsScene(sel);
    sel->setScene(selScn);
    QPixmap selPix(sel->width(), sel->height());
    QImage selImg = QImage(selPix.width(), selPix.height(), s.format());
    selImg.fill(QColor(0,0,0).rgb());
    for ( boxI = 0 ; boxI < sel->height() ; boxI++ )
    {
        for ( boxJ = 0 ; boxJ < sel->width() ; boxJ++ )
        {
            if ( boxI/repeatI >= s.height() || boxJ/repeatJ >= s.width() )
            {
                selImg.setPixel(boxJ, boxI, QColor(255,255,255).rgb());
                continue;
            }
            if ( boxI/repeatI != (boxI+1)/repeatI )
                continue;
            if ( boxJ/repeatJ != (boxJ+1)/repeatJ )
                continue;
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
    std::ostringstream outs;
    outs << "Starting dump.. " << bgmatrix_height << "x" << bgmatrix_width << std::endl;
    for ( int i = 0 ; i < bgmatrix_height ; i++ )
    {
        for ( int j = 0 ; j < bgmatrix_width ; j++ )
        {
            outs << " ";
            if ( bgmatrix[i][j] < 10 ) std::cout << "0";
            outs << bgmatrix[i][j] << " ";
        }
        outs << std::endl;
    }

    log.log(__LINE__, outs);
}

