#ifndef OPENPROJECTWINDOW_H
#define OPENPROJECTWINDOW_H

#include <QDialog>
#include <QString>

#include "mainwindow.h"

namespace Ui {
    class OpenProjectWindow;
}

class OpenProjectWindow : public QDialog
{
    Q_OBJECT

public:
    explicit OpenProjectWindow(MainWindow *parent);
    ~OpenProjectWindow();

    void addSpriteOption(QString s);

private:
    Ui::OpenProjectWindow *ui;

    MainWindow *pai;

private slots:
    void okClicked();
    void cancelClicked();
};

#endif // OPENPROJECTWINDOW_H
