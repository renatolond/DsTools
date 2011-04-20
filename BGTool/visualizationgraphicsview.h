#ifndef VISUALIZATIONGRAPHICSVIEW_H
#define VISUALIZATIONGRAPHICSVIEW_H

#include <QGraphicsView> // Base type

class cViewController;
class QMouseEvent;
class QWidget;

class VisualizationGraphicsView : public QGraphicsView
{
    Q_OBJECT
public:
    VisualizationGraphicsView(QWidget *parent = 0);
    ~VisualizationGraphicsView();

    void set_view_controller(cViewController *view_controller);

protected:
    void mousePressEvent(QMouseEvent *);
    cViewController *m_view_controller;

private:
};

#endif // VISUALIZATIONGRAPHICSVIEW_H
