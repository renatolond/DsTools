#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    imgData = new imagesData(QImage(),QImage());
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
    QGraphicsView *w = ui->visualizationView;
    QGraphicsScene *scn = new QGraphicsScene(w);

    w->setScene(scn);
    QPixmap pix("/home/lond/sources/PF/gfx/teste.png");

    QImage img(pix.toImage());
    int newHeight = pix.height()/8 + pix.height();
    int newWidth = pix.width()/8 + pix.width();
    QImage imgGrid;
    imgGrid = QImage(newWidth, newHeight, img.format());
    imgData->visualizationGrid = imgGrid;

    std::cout << "Height " << newHeight << std::endl << "Width " << newWidth << std::endl;

    imgGrid.fill(QColor(0,0,0).rgb());

    {
        int i, i2, j, j2;
        int it, jt;
        it = jt = 8;

        for ( i = 0, i2 = 0 ; i < imgGrid.height() ;  )
        {
            jt = 8;
            for ( j = 0, j2 = 0 ; j < imgGrid.width() ; )
            {
                imgGrid.setPixel(j,i,img.pixel(j2,i2));

                j++;
                j2++;
                jt--;
                if (jt == 0) { jt = 8; j++; }
            }

            i++;
            i2++;
            it--;
            if (it == 0) { it = 8; i++; }
        }
    }

    QPixmap pixGrid;
    pixGrid = QPixmap::fromImage(imgGrid);

    scn->setSceneRect(pixGrid.rect());
    scn->addPixmap(pixGrid);
    w->show();
}
