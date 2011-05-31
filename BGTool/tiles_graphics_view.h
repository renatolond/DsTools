#ifndef MOUSEGRAPHICSVIEW_H
#define MOUSEGRAPHICSVIEW_H

#include <QGraphicsView> // Base type

class cViewController;
class QMouseEvent;
class QWidget;

class cTilesGraphicsView : public QGraphicsView
{
    Q_OBJECT
public:
    cTilesGraphicsView(QWidget *parent = 0);
    ~cTilesGraphicsView();

    void set_view_controller(cViewController *view_controller);

protected:
    void mousePressEvent(QMouseEvent *);
    cViewController *m_view_controller;

private:
};

#endif // MOUSEGRAPHICSVIEW_H
