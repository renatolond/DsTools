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

void imagesData::findSprites(int pix_height, int pix_width, QImage &img, QImage &imgGrid, const QImage &emptySprite)
{

    int i; int j;
    int startI; int startJ;
    startI = startJ = 0;

    int spritesI = pix_height / sprite_height;
    int spritesJ = pix_width / sprite_width;

    createBgMatrix(spritesI,spritesJ);

    {
        QColor c;
        c.setAlpha(0);
        c.setRed(255);
        c.setGreen(0);
        c.setBlue(255);

        palette.push_back(c);
    }

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
                    QColor c;
                    int colorExists;

                    colorExists = 0;

                    c.setRgba(img.pixel(j*sprite_width  + l,
                                       i*sprite_height + k));

                    //std::cout << std::hex << c.alpha() << std::endl;
                    c.setRed(((c.red() >> 3) << 3));
                    c.setGreen(((c.green() >> 3) << 3));
                    c.setBlue(((c.blue() >> 3) << 3));
                    //  std::cout << std::hex << c.rgb() << std::endl;

                    if ( c.alpha() != 255 )
                    {
                        c.setAlpha(0);
                        c.setRed(255);
                        c.setGreen(0);
                        c.setBlue(255);
                    }

                    sprite.setPixel(l,k,
                                    c.rgb());
                    for ( QList<QColor>::iterator it = palette.begin() ; it != palette.end() ; it++ )
                    {
                        if ( *it == c )
                        {
                            colorExists = 1;
                            break;
                        }
                    }

                    if ( !colorExists )
                    {
                        palette.push_back(c);
                    }
                    imgGrid.setPixel(j*(sprite_width +visualization_grid_width) +l,
                                     i*(sprite_height+visualization_grid_height)+k,
                                     c.rgb());
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
                if ( sprite == emptySprite )
                    exists = 1;
            }

            if ( !exists )
            {
                std::ostringstream outs;
                outs << "New sprite at " << j*sprite_width << "," << i*sprite_height << std::endl;
                log.log(__LINE__, outs);
                sprites.push_back(sprite);
            }
        }
    }

    sprites.push_back(emptySprite);

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

void imagesData::fillPaletteView()
{
    QGraphicsView *pal = paletteView;
    QGraphicsScene *palScn = new QGraphicsScene(pal);
    pal->setScene(palScn);
    int width = pal->width()-5; // This way, we get rid of the scroll barz
    int height = pal->height()-5;
    width = (width/9)*9 -1; // This way, we get a right number of squares for the paletteView
    height = (height/9)*9 -1;
    QPixmap palPix(width, height);
    QImage palImg = QImage(palPix.width(), palPix.height(), spriteGrid.format());
    palImg.fill(QColor(0, 0, 0, 0).rgba());

    for ( int i = 0 ; i < palette.size() ; i++ )
    {
        int k = i*9, j = 0;
        while ( k > palPix.width() )
        {
            k -= palPix.width()+1; j+=9;
        }

        for ( int l = j ; l < j+8 ; l++ )
        {
            for ( int m = k ; m < k+8 ; m++ )
            {
                palImg.setPixel(m, l, palette.at(i).rgb());
            }
        }
    }
    palPix = palPix.fromImage(palImg);
    palScn->setSceneRect(0,0,palPix.width(), palPix.height());
    palScn->addPixmap(palPix);
    pal->show();
}

void imagesData::importPng(QGraphicsView *vView, QGraphicsView *spView, QGraphicsView *selView, QGraphicsView *palView)
{
    visualizationView = vView;
    spritesView = spView;
    selectedView = selView;
    paletteView = palView;

    QPixmap pix("../gfx/teste.png");

    QImage img(pix.toImage());
    int newHeight = pix.height() + ((pix.height()/sprite_height)-1)*visualization_grid_height;
    int newWidth = pix.width() + ((pix.width()/sprite_width)-1)*visualization_grid_width;
    QImage imgGrid;
    imgGrid = QImage(newWidth,
                     newHeight,
                     img.format());
    visualizationGrid = imgGrid;

//    palette.push_back(QColor(0xF8, 0, 0xF8, 0)); // Transparent Color!

    std::ostringstream outs;
    outs << "Height " << newHeight <<"; Width " << newWidth << std::endl;
    log.log(__LINE__, outs);

    QImage emptySprite = QImage(sprite_width,sprite_height,img.format());
    emptySprite.fill(QColor(255,0,255).rgb());

    imgGrid.fill(QColor(0,0,0).rgb());
    findSprites(pix.height(), pix.width(), img, imgGrid, emptySprite); // also fill visualizationView and spriteView

    std::cout << "We have " << palette.size() << "colors in our palette!" << std::endl;

    fillPaletteView();

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

template < typename T >
        inline T highbit(T& t)
{
    return t = (((T)(-1)) >> 1) + 1;
}

template < typename T >
        std::ostream& bin(T& value, std::ostream &o)
{
    for ( T bit = highbit(bit); bit; bit >>= 1 )
    {
        o << ( ( value & bit ) ? '1' : '0' );
    }
    return o;
}

void imagesData::exportBG()
{
    std::string pal, tiles, map, cfile;
    std::ostringstream outs;
    outs << "../gfx/bin/bgtool" << index << "_Pal.bin";
    pal = outs.str();
    outs.str(std::string());
    outs.clear();
    outs << "../gfx/bin/bgtool" << index << "_Tiles.bin";
    tiles = outs.str();
    outs.str(std::string());
    outs.clear();
    outs << "../gfx/bin/bgtool" << index << "_Map.bin";
    map = outs.str();
    outs.str(std::string());
    outs.clear();
    outs << "../gfx/bin/bgtool" << index << ".c";
    cfile = outs.str();
    outs.str(std::string());
    outs.clear();

    // exporting palette
    FILE *sout = fopen(pal.c_str(), "wb");

    for ( QList<QColor>::iterator it = palette.begin() ; it != palette.end() ; it++ )
    {
        unsigned char high, low;
        high = 1;
        high = high << 5;
        high += ( it->blue() >> 3 );
        high = high << 2;
        high += ( it->green() >> 6 );

        unsigned char green = it->green() - ((it->green() >> 6)<<6);
        low = (green >> 3);
        low = low << 5;
        low += ( it->red() >> 3);

        unsigned char red, blue;
        red = it->red(); green = it->green(); blue = it->blue();

        fwrite(&low, 1, sizeof(low), sout);
        fwrite(&high, 1, sizeof(high), sout);
        //        std::cout << std::hex << (unsigned short int) low << std::endl;
        //        std::cout << std::hex << (unsigned short int) high << std::endl;
    }
    for ( int i = palette.size() ; i < 256 ; i++ )
    {
        unsigned char zero;
        zero = 0;
        fwrite(&zero, 1, sizeof(zero), sout);
        fwrite(&zero, 1, sizeof(zero), sout);
    }
    fclose(sout);

    //exporting tiles
    sout = fopen(tiles.c_str(), "wb");
    for ( std::vector<QImage>::iterator it = sprites.begin() ; it != sprites.end() ; it++ )
    {
        for ( int i = 0 ; i < 8 ; i++ )
        {
            for ( int j = 0 ; j < 8 ; j++ )
            {
                for ( unsigned char k = 0 ; k < palette.size() ; k++ )
                {
                    if ( it->pixel(j,i) == palette.at(k).rgb() )
                    {
                        fwrite(&k,1,sizeof(k),sout);
                        break;
                    }
                }
            }
        }
    }

    for ( int i = 0 ; i < 64 ; i++ )
    {
        unsigned char k = 0;
        fwrite(&k,1,sizeof(k),sout);
    }
    fclose(sout);

    //exporting map
    sout = fopen(map.c_str(), "wb");
    for ( int i = 0 ; i < bgmatrix_height ; i++ )
    {
        for ( int j = 0 ; j < bgmatrix_width ; j++ )
        {
            unsigned char k = bgmatrix[i][j];
            unsigned char zero = 0;
            fwrite(&k,1,sizeof(k),sout);
            fwrite(&zero, 1, sizeof(zero), sout);
        }
    }
    fclose(sout);

    std::filebuf fb;
    fb.open(cfile.c_str(), std::cout.out);
    std::ostream os(&fb);

    os << "#include <PA_BgStruct.h>" << std::endl;
    os << std::endl;
    os << "extern const char bgtool" << index << "_Tiles[];" << std::endl;
    os << "extern const char bgtool" << index << "_Map[];" << std::endl;
    os << "extern const char bgtool" << index << "_Pal[];" << std::endl;
    os << std::endl;
    os << "const PA_BgStruct bgtool" << index << " = {" << std::endl;
    os << "  PA_BgLarge," << std::endl;
    os << "  " << bgmatrix_width*8 << ", " << bgmatrix_height*8 << "," << std::endl;
    os << std::endl;
    os << "bgtool" << index << "_Tiles," << std::endl;
    os << "bgtool" << index << "_Map," << std::endl;
    os << "{bgtool" << index << "_Pal}," << std::endl;
    os << std::endl;
    os << sprites.size()*8*8 << "," << std::endl;
    os << "{" << bgmatrix_height*bgmatrix_width*2 << "}" << std::endl;
    os << "};" << std::endl;

    fb.close();
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

