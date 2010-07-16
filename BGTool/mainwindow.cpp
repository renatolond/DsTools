#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::changeEvent(QEvent *e)
{
    QMainWindow::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        ui->retranslateUi(this);
        break;
    default:
        break;
    }
}

void MainWindow::on_pushButton_clicked()
{
    QGraphicsView *w = ui->graphicsView;
    QGraphicsScene *scn = new QGraphicsScene(w);
    w->setScene(scn);
    QPixmap pix("/home/lond/sources/PF/gfx/teste.png");

    QImage img(pix.toImage());
    int newHeight = pix.height()/8 + pix.height();
    int newWidth = pix.height()/8 + pix.width();
    QImage imgGrid(newWidth, newHeight, img.format());

    std::cout << "Height " << newHeight << std::endl << "Width " << newWidth << std::endl;

    imgGrid.fill(QColor(0,0,0).rgb());

    {
        int i, i2, j, j2;
        for ( i = 0, i2 = 0 ; i < imgGrid.height() ;  )
        {
            for ( j = 0, j2 = 0 ; j < imgGrid.width() ; )
            {
                imgGrid.setPixel(j,i,img.pixel(j2,i2));

                j++;
                j2++;
                if (j % 7 == 0) j++;
            }

            i++;
            i2++;
            if (i % 7 == 0) i++;
        }
    }



    QPixmap pixGrid;
    pixGrid = QPixmap::fromImage(imgGrid);

    scn->setSceneRect(pixGrid.rect());
    scn->addPixmap(pixGrid);
    w->show();
}
