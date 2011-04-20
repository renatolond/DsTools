#include "visualizationgraphicsview.h" // Class definition

// QT libraries
#include <QMouseEvent>
//#include <QFlags>
//#include <QGraphicsItem>
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

void VisualizationGraphicsView::mousePressEvent(QMouseEvent *e)
{
  if(!m_view_controller)
    return;

  if(e->buttons() == Qt::RightButton)
    m_view_controller->editor_view_clicked(e->x(), e->y());
}
