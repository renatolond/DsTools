#ifndef IMAGES_H
#define IMAGES_H

#include <QPixmap>
#include <iostream>
#include <QGraphicsView>
#include <QGraphicsItem>
#include <QGraphicsPixmapItem>
#include <vector>

class imagesData
{
public:
    imagesData(QImage visualization, QImage sprite) : visualizationGrid(visualization), spriteGrid(sprite)
    {
        bgmatrix_width = bgmatrix_height = 0;
        selectedSprite.setX(-1);
        selectedSprite.setY(-1);
        selectedSpriteId = -1;
    }

    ~imagesData()
    {
        if ( bgmatrix_height || bgmatrix_width )
        {
            for ( int i = 0 ; i < bgmatrix_height ; i++ )
            {
                delete[] bgmatrix[i];
            }
        }
        delete[] bgmatrix;
    }

    void importPng(QGraphicsView *, QGraphicsView *, QGraphicsView *);
    void createBgMatrix(int height, int width);
    void dumpBgMatrix();
    void setSelectedSprite(QImage s);
    void highlightSelectedSprite();
    void exportPng();

    QImage visualizationGrid;
    QImage spriteGrid;
    int **bgmatrix;
    int bgmatrix_width;
    int bgmatrix_height;
    QPoint selectedSprite;
    int selectedSpriteId;
    QGraphicsView *selectedView;
    QGraphicsView *visualizationView;
    QGraphicsView *spritesView;
    std::vector<QImage> sprites;
};

#endif // IMAGES_H
