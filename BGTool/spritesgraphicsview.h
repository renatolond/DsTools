#ifndef MOUSEGRAPHICSVIEW_H
#define MOUSEGRAPHICSVIEW_H

#include <QGraphicsView>
#include <iostream>
#include <QMouseEvent>
#include <QFlags>
#include <QGraphicsItem>
#include "imagesData.h"

class SpritesGraphicsView : public QGraphicsView
{
    Q_OBJECT
    logger log;
public:
    SpritesGraphicsView(QWidget *parent = 0);
    ~SpritesGraphicsView();
   // QGraphicsScene *scene;
    imagesData *imgData;

protected:
    void mousePressEvent(QMouseEvent *);
//    void changeEvent(QEvent *e);

private:
};

#endif // MOUSEGRAPHICSVIEW_H
