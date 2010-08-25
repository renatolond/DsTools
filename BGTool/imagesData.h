#ifndef IMAGES_H
#define IMAGES_H

#include <QPixmap>
#include <iostream>
#include <fstream>
#include <QGraphicsView>
#include <QGraphicsItem>
#include <QGraphicsPixmapItem>
#include <QFileDialog>
#include <QBitmap>
#include <vector>
#include "logger.h"
#include <cstdio>

const int sprite_height = 8;
const int sprite_width  = 8;
const int sprites_per_line = 4;

class imagesData
{
    void findSprites(int pix_height, int pix_width, QImage &img, QImage &imgGrid, const QImage &emptySprite);
    logger log;
public:
    imagesData(QImage visualization, QImage sprite) : visualizationGrid(visualization), spriteGrid(sprite)
    {
        log = logger(__FILE__);
        bgmatrix_width = bgmatrix_height = 0;
        selectedSprite.setX(-1);
        selectedSprite.setY(-1);
        selectedSpriteId = -1;
        visualization_grid_height = visualization_grid_width = 1;
        sprite_grid_height = sprite_grid_width = 1;
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

    void importPng(QGraphicsView *, QGraphicsView *, QGraphicsView *, QGraphicsView *, QString);
    void exportBG();
    void createBgMatrix(int height, int width);
    void dumpBgMatrix();
    void setSelectedSprite(QImage s);
    void highlightSelectedSprite();
    void exportPng();
    void fillPaletteView();

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
    QGraphicsView *paletteView;
    std::vector<QImage> sprites;
    int visualization_grid_height,visualization_grid_width;
    int sprite_grid_height, sprite_grid_width;
    QList<QColor> palette;
    int index;
};

#endif // IMAGES_H
