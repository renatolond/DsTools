#include "tiles_graphics_view.h" // Class definition

// QT libraries
#include <QMouseEvent>
//#include <QFlags>
//#include <QGraphicsItem>
// End of QT libraries

// Project libraries
#include "viewcontroller.h"
// End of Project libraries

cTilesGraphicsView::cTilesGraphicsView(QWidget *parent) :
  QGraphicsView(parent)
{
  m_view_controller = NULL;
}

cTilesGraphicsView::~cTilesGraphicsView()
{
}

void cTilesGraphicsView::set_view_controller(cViewController *view_controller)
{
  m_view_controller = view_controller;
}


void cTilesGraphicsView::mousePressEvent(QMouseEvent *e)
{
  if(!m_view_controller)
    return;

  if(e->buttons() == Qt::LeftButton)
    m_view_controller->tiles_view_clicked(e->x(), e->y());
}
