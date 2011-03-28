#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "sprite.h"


namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void createSprite(QString nome, int w, int h);
    void enable(void);
    void disable(void);

private:
    Ui::MainWindow *ui;

    Sprite sprite;

private slots:
    void on_btn_AddFrame_clicked();
    void newProject();
    void saveProject();
    void openProject();
    void closeProject();
};

#endif // MAINWINDOW_H
