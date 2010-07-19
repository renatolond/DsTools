#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "images.h"
#include <iostream>
#include <vector>

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow {
    Q_OBJECT
public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

protected:
    void changeEvent(QEvent *e);

private:
    Ui::MainWindow *ui;
    imagesData *imgData;

private slots:
    void on_spritesView_customContextMenuRequested(QPoint pos);
    void on_pushButton_clicked();
};

#endif // MAINWINDOW_H
