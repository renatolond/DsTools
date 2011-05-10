#ifndef TABBG_H
#define TABBG_H

#include <QWidget> // Base type

namespace Ui {
    class cDrawingTab;
}

class cBackground;
class cViewController;

class cDrawingTab : public QWidget {
    Q_OBJECT
public:
    cDrawingTab(QWidget *parent = 0);
    ~cDrawingTab();
    void setIndex(int i);
    void set_background(cBackground *bg);

protected:
    void changeEvent(QEvent *e);
    cBackground *m_background;
    cViewController *m_view_controller;

private:
    Ui::cDrawingTab *ui;
    int index;

private slots:
    void on_btHighlight_toggled(bool checked);
    void on_btExport_clicked();
    void on_btExportPng_clicked();
    void on_btDump_clicked();
    void on_btPaint_toggled(bool checked);
    void on_btConvert_clicked();
    void on_bt_hflip_toggled(bool checked);
    void on_bt_vflip_toggled(bool checked);
};

#endif // TABBG_H
