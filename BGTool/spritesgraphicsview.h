#ifndef MOUSEGRAPHICSVIEW_H
#define MOUSEGRAPHICSVIEW_H

#include <QGraphicsView> // Base type

class cViewController;
class QMouseEvent;
class QWidget;

class SpritesGraphicsView : public QGraphicsView
{
    Q_OBJECT
public:
    SpritesGraphicsView(QWidget *parent = 0);
    ~SpritesGraphicsView();

    void set_view_controller(cViewController *view_controller);

protected:
    void mousePressEvent(QMouseEvent *);
    cViewController *m_view_controller;

private:
};

#endif // MOUSEGRAPHICSVIEW_H
