#ifndef TABBG_H
#define TABBG_H

#include <QWidget>
#include "imagesData.h"

namespace Ui {
    class TabBG;
}

class cBackground;

class TabBG : public QWidget {
    Q_OBJECT
public:
    TabBG(QWidget *parent = 0);
    ~TabBG();
    imagesData *imgData;
    void setIndex(int i);
    void set_background(cBackground *bg);

protected:
    void changeEvent(QEvent *e);
    cBackground *m_background;

private:
    Ui::TabBG *ui;
    int index;

private slots:
    void on_btHighlight_toggled(bool checked);
    void on_btExport_clicked();
    void on_btExportPng_clicked();
    void on_btHighlight_clicked();
    void on_btDump_clicked();
    void on_btPaint_toggled(bool checked);
    void on_btConvert_clicked();
};

#endif // TABBG_H
