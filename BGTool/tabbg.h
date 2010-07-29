#ifndef TABBG_H
#define TABBG_H

#include <QWidget>
#include "imagesData.h"

namespace Ui {
    class TabBG;
}

class TabBG : public QWidget {
    Q_OBJECT
public:
    TabBG(QWidget *parent = 0);
    ~TabBG();
    imagesData *imgData;

protected:
    void changeEvent(QEvent *e);

private:
    Ui::TabBG *ui;

private slots:
    void on_btExportPng_clicked();
    void on_btHighlight_clicked();
    void on_btDump_clicked();
    void on_btPaint_toggled(bool checked);
    void on_btConvert_clicked();
};

#endif // TABBG_H
