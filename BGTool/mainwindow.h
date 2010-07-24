#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "imagesData.h"

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
    void on_btExportPng_clicked();
    void on_btHighlight_clicked();
    void on_btDump_clicked();
    void on_btPaint_toggled(bool checked);
    void on_btConvert_clicked();
};

#endif // MAINWINDOW_H
