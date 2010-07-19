#ifndef IMAGES_H
#define IMAGES_H

#include <QPixmap>

class imagesData
{
public:
    imagesData(QImage visualization, QImage sprite) : visualizationGrid(visualization), spriteGrid(sprite)
    {
    }

    QImage &visualizationGrid;
    QImage &spriteGrid;
};

#endif // IMAGES_H
