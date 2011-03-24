#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

class cProject;

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
    cProject *m_project;

private:
    Ui::MainWindow *ui;

private slots:

private slots:
    void on_actionNew_Project_triggered();
    void on_tabWidget_currentChanged(int index);
};

#endif // MAINWINDOW_H
