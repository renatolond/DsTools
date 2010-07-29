#ifndef TAB_BGALL_H
#define TAB_BGALL_H

#include <QWidget>

namespace Ui {
    class tab_bgall;
}

class Tab_BgAll : public QWidget {
    Q_OBJECT
public:
    Tab_BgAll(QWidget *parent = 0);
    ~Tab_BgAll();

protected:
    void changeEvent(QEvent *e);

private:
    Ui::tab_bgall *ui;
};

#endif // TAB_BGALL_H
