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
    imagesData *imgData;

protected:
    void changeEvent(QEvent *e);
    void setSelectedSprite(QImage);

private:
    Ui::MainWindow *ui;

private slots:
    void on_btHighlight_clicked();
    void on_btDump_clicked();
    void on_btPaint_toggled(bool checked);
    void on_btConvert_clicked();
    void on_spritesView_customContextMenuRequested(QPoint pos);
};

#endif // MAINWINDOW_H
