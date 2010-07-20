#ifndef MOUSEGRAPHICSVIEW_H
#define MOUSEGRAPHICSVIEW_H

#include <QGraphicsView>
#include <iostream>
#include <QMouseEvent>
#include <QFlags>
#include <QGraphicsItem>
class MouseGraphicsView : public QGraphicsView
{
    Q_OBJECT
public:
    MouseGraphicsView(QWidget *parent = 0);
    ~MouseGraphicsView();
    QGraphicsScene *scene;

protected:
    void mousePressEvent(QMouseEvent *);
//    void changeEvent(QEvent *e);

private:
};

#endif // MOUSEGRAPHICSVIEW_H
