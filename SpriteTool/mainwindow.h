#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsView>
#include <QGraphicsScene>


class cMainController;

namespace Ui {
    class cMainWindow;
}

class cMainWindow : public QMainWindow
{
  Q_OBJECT

 public:
  cMainWindow(QWidget *parent = 0);
  ~cMainWindow(void);

  void enable(void);
  void disable(void);
  void show_frame(int i);
  void reset(void);
  int delete_procedure(int frame);
  bool in_animation(void);
  void set_animation_mode(void);
  void set_edit_mode(void);
  void call_manage_bounds(void);

 private:
  Ui::cMainWindow *ui;

  cMainController *m_controller;

 private slots:
  void show_right();
  void show_left();
  void manage_bounds();
};

#endif // MAINWINDOW_H
