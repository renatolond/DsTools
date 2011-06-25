#ifndef OPENPROJECTWINDOW_H
#define OPENPROJECTWINDOW_H

#include <QDialog>
#include <QString>

#include "mainwindow.h"

namespace Ui {
    class cOpenProjectWindow;
}

class cOpenProjectWindow : public QDialog
{
  Q_OBJECT

 public:
  explicit cOpenProjectWindow(cMainController *parent);
  ~cOpenProjectWindow(void);
  void add_sprite_option(QString s);

 private:
  Ui::cOpenProjectWindow *ui;
  cMainController *m_controller;

 private slots:
  void ok_clicked(void);
  void cancel_clicked(void);
};

#endif // OPENPROJECTWINDOW_H
