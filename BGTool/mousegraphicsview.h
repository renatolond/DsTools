#ifndef MOUSEGRAPHICSVIEW_H
#define MOUSEGRAPHICSVIEW_H

#include <QGraphicsView>

class MouseGraphicsView : public QGraphicsView
{
    Q_OBJECT
public:
    MouseGraphicsView(QWidget *parent = 0);
    ~MouseGraphicsView();

protected:
//    void changeEvent(QEvent *e);

private:
};

#endif // MOUSEGRAPHICSVIEW_H
