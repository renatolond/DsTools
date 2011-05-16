#ifndef NEWPROJECTWINDOW_H
#define NEWPROJECTWINDOW_H

#include <QDialog>
#include <QString>
#include "sprite.h"
#include "mainwindow.h"

namespace Ui {
    class NewProjectWindow;
}

class NewProjectWindow : public QDialog
{
    Q_OBJECT

public:
    explicit NewProjectWindow(MainWindow *parent);
    ~NewProjectWindow();

private:
    Ui::NewProjectWindow *ui;

    MainWindow *pai;

private slots:
    void okClicked();
    void cancelClicked();

};

#endif // NEWPROJECTWINDOW_H
