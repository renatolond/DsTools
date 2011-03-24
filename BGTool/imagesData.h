#ifndef IMAGES_H
#define IMAGES_H

#include <QVector>

//TIRAR
#include <QImage>
#include <QPoint>
#include <QColor>
#include <QGraphicsView>
#include <iostream>
#include <fstream>
#include <QGraphicsItem>
#include <QBitmap>
//FIMTIRAR

const int sprite_height = 8;
const int sprite_width  = 8;
const int sprites_per_line = 4;

struct logger;

class imagesData
{
    void findSprites(int pix_height, int pix_width, QImage &img, QImage &imgGrid, QImage &emptySprite);
    logger *log;
public:
    imagesData(QImage visualization, QImage sprite);

    ~imagesData();

    void importPng(QGraphicsView *, QGraphicsView *, QGraphicsView *, QGraphicsView *, QString);
    void exportBG();
    void createBgMatrix(int height, int width);
    void dumpBgMatrix();
    void setSelectedSprite(QImage s);
    void highlightSelectedSprite(bool checked);
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
    QVector<QImage> sprites;
    int visualization_grid_height,visualization_grid_width;
    int sprite_grid_height, sprite_grid_width;
    QVector<QRgb> nPalette;
    int index;
};

#endif // IMAGES_H
