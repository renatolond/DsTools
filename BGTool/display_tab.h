#ifndef TAB_BGALL_H
#define TAB_BGALL_H

#include <QWidget>

namespace Ui {
    class cDisplayTab;
}

class cDisplayTab : public QWidget {
    Q_OBJECT
public:
    cDisplayTab(QWidget *parent = 0);
    ~cDisplayTab();
//    void completeImgData(imagesData*, imagesData*);
protected:
    void changeEvent(QEvent *e);

private:
    Ui::cDisplayTab *ui;
};

#endif // TAB_BGALL_H
