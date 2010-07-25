#ifndef VISUALIZATIONGRAPHICSVIEW_H
#define VISUALIZATIONGRAPHICSVIEW_H
#include <QGraphicsView>
#include <iostream>
#include <QMouseEvent>
#include <QFlags>
#include <QGraphicsItem>
#include <QScrollBar>
#include <imagesData.h>

class VisualizationGraphicsView : public QGraphicsView
{
    Q_OBJECT
    logger log;
public:
    VisualizationGraphicsView(QWidget *parent = 0);
    ~VisualizationGraphicsView();
  //  QGraphicsScene *scene;
    int btPaintPressed;
    imagesData *imgData;

protected:
    void mousePressEvent(QMouseEvent *);
//    void changeEvent(QEvent *e);

private:
};

#endif // VISUALIZATIONGRAPHICSVIEW_H
