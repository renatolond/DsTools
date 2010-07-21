#ifndef IMAGES_H
#define IMAGES_H

#include <QPixmap>
#include <iostream>

class imagesData
{
public:
    imagesData(QImage visualization, QImage sprite) : visualizationGrid(visualization), spriteGrid(sprite)
    {
        bgmatrix_width = bgmatrix_height = 0;
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

    void createBgMatrix(int height, int width);
    void dumpBgMatrix();

    QImage &visualizationGrid;
    QImage &spriteGrid;
    int **bgmatrix;
    int bgmatrix_width;
    int bgmatrix_height;
};

#endif // IMAGES_H
