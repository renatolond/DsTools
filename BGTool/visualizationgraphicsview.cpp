#include "visualizationgraphicsview.h" // Class definition

// QT libraries
#include <QMouseEvent>
#include <QScrollBar>
// End of QT libraries

// Project libraries
#include "viewcontroller.h"
// End of Project libraries

VisualizationGraphicsView::VisualizationGraphicsView(QWidget *parent) :
        QGraphicsView(parent)
{
}

VisualizationGraphicsView::~VisualizationGraphicsView()
{
}

void VisualizationGraphicsView::set_view_controller(cViewController *view_controller)
{
  m_view_controller = view_controller;
}

void VisualizationGraphicsView::mousePressEvent(QMouseEvent *e)
{
  if(!m_view_controller)
    return;

  if(e->buttons() == Qt::RightButton)
    m_view_controller->editor_view_clicked(e->x()+horizontalScrollBar()->value(), e->y());
}
