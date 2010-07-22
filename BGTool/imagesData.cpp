#include "images.h"

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

