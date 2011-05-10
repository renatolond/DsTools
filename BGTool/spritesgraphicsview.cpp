#include "spritesgraphicsview.h" // Class definition

// QT libraries
#include <QMouseEvent>
//#include <QFlags>
//#include <QGraphicsItem>
// End of QT libraries

// Project libraries
#include "viewcontroller.h"
// End of Project libraries

SpritesGraphicsView::SpritesGraphicsView(QWidget *parent) :
  QGraphicsView(parent)
{
  m_view_controller = NULL;
}

SpritesGraphicsView::~SpritesGraphicsView()
{
}

void SpritesGraphicsView::set_view_controller(cViewController *view_controller)
{
  m_view_controller = view_controller;
}


void SpritesGraphicsView::mousePressEvent(QMouseEvent *e)
{
  if(!m_view_controller)
    return;

  if(e->buttons() == Qt::LeftButton)
    m_view_controller->sprites_view_clicked(e->x(), e->y());
}
