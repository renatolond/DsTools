#ifndef NEWPROJECTWINDOW_H
#define NEWPROJECTWINDOW_H

#include <QDialog>
#include <QString>

#include "mainwindow.h"

namespace Ui {
    class cNewProjectWindow;
}

class cNewProjectWindow : public QDialog
{
  Q_OBJECT

 public:
  explicit cNewProjectWindow(cMainController *parent = 0);
  ~cNewProjectWindow(void);

 private:
   Ui::cNewProjectWindow *ui;
   cMainController *m_controller;

 private slots:
   void ok_clicked(void);
   void cancel_clicked(void);
};

#endif // NEWPROJECTWINDOW_H
