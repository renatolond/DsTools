#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

class cProject;
class cDrawingTab;
struct sGlobalData;

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow {
    Q_OBJECT
public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void create_level(QString project_name, int num_layers, int x, int y);

protected:
    void changeEvent(QEvent *e);
    cProject *m_project;

private:
    Ui::MainWindow *ui;
    void clear_active(void);
    cDrawingTab *m_tabbg_widgets[5];
    QWidget *m_tabs[5];
    sGlobalData *m_global_data;

private slots:

private slots:
    void on_actionNew_Project_triggered();
    void on_tabWidget_currentChanged(int index);
    void on_actionClose_Project_triggered();
    void on_actionSave_Project_triggered();
    void on_actionOpen_Project_triggered();
    void on_actionExport_All_triggered();
};

#endif // MAINWINDOW_H
