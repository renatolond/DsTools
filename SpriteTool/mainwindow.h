#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsView>
#include <QGraphicsScene>

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
    void createSprite(QString nome);
    void enable(void);
    void disable(void);
    void showFrame(int i);
    void saveImages(void);
    void deleteImages(void);

private:
    Ui::MainWindow *ui;

    Sprite sprite;
    QStringList toDeleteFiles;
    QGraphicsScene *scene;
    int currentFrame;

    QTimer *timer;
    bool inAnimation;

private slots:
    void newProject();
    void saveProject();
    void openProject();
    void closeProject();
    void showRight();
    void showLeft();
    void manageArrows();
    void addFrame();
    void delFrame();
    void animate();
    void timedAnimation();
    void exportDS();

};

#endif // MAINWINDOW_H
