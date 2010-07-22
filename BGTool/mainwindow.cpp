#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    imgData = new imagesData(QImage(),QImage());
    ui->spritesView->imgData = ui->visualizationView->imgData = imgData;
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

void MainWindow::on_spritesView_customContextMenuRequested(QPoint pos)
{
    std::cout << "Click at: " << pos.x() << "," << pos.y() << std::endl;
}

void MainWindow::on_btConvert_clicked()
{
    QGraphicsView *w = ui->visualizationView;
    QGraphicsView *s = ui->spritesView;
    QGraphicsScene *scn = ui->visualizationView->scene = new QGraphicsScene(w);
    QGraphicsScene *sScn = ui->spritesView->scene = new QGraphicsScene(s);

    w->setScene(scn);
    s->setScene(sScn);

    QPixmap pix("/home/lond/sources/PF/gfx/teste.png");

    QImage img(pix.toImage());
    int newHeight = pix.height()/8-1 + pix.height();
    int newWidth = pix.width()/8-1 + pix.width();
    QImage imgGrid;
    imgGrid = QImage(newWidth, newHeight, img.format());
    imgData->visualizationGrid = imgGrid;

    std::cout << "Height " << newHeight << "; Width " << newWidth << std::endl;

    imgGrid.fill(QColor(0,0,0).rgb());
    QImage spriteGrid;
    {
        std::vector<QImage> sprites;

        int i; int j;
        int startI; int startJ;
        startI = startJ = 0;

        int spritesI = pix.height() / 8;
        int spritesJ = pix.width() / 8;

        imgData->createBgMatrix(spritesI,spritesJ);

        for ( i = 0 ; i < spritesI ; i++ )
        {
            for ( j = 0 ; j < spritesJ ; j++ )
            {
                QImage sprite = QImage(8,8,img.format());
                for ( int k = 0 ; k < 8 ; k++ )
                {
                    for ( int l = 0 ; l < 8 ; l++ )
                    {
                        sprite.setPixel(l,k,img.pixel(j*8 + l,i*8+k));
                        imgGrid.setPixel(j*9+l,i*9+k, img.pixel(j*8 + l,i*8+k));
                    }
                }

                QImage sprite2, sprite3, sprite4;
                sprite2 = sprite.transformed(QTransform().rotate(90));
                sprite3 = sprite.transformed(QTransform().rotate(180));
                sprite4 = sprite.transformed(QTransform().rotate(270));
                int exists = 0;
                int id = 0;

                for ( std::vector<QImage>::iterator it = sprites.begin(); it != sprites.end() ; it++ )
                {
                    if ( (*it == sprite) || (*it == sprite2) || (*it == sprite3) || (*it == sprite4) )
                    {
                        exists = 1;
                        break;
                    }
                    id++;
                }
                imgData->bgmatrix[i][j] = id;

                if ( !exists )
                {
                    std::cout << "New sprite at " << j*8 << "," << i*8 << std::endl;
                    sprites.push_back(sprite);
                }
            }
        }

        imgData->dumpBgMatrix();

        std::cout << "Total sprites: " << sprites.size() << std::endl;
        spriteGrid = QImage(8*4+4, 8*((sprites.size()+3)/4)+((sprites.size()+3)/4), img.format());
        spriteGrid.fill(QColor(255,0,255).rgb());
        int m = 0;
        int n = 0;
        for ( std::vector<QImage>::iterator it = sprites.begin(); it != sprites.end() ; it++ )
        {
            for ( int k = 0 ; k < 8 ; k++ )
            {
                for ( int l = 0 ; l < 8 ; l++ )
                {
                    spriteGrid.setPixel(l+m*9,k+n*9,(*it).pixel(l,k));
                }
            }

            if ( m != 3 ) m++;
            else { m = 0; n++; }
        }
    }

    QImage emptySprite = QImage(8,8,img.format());
    emptySprite.fill(QColor(255,0,255).rgb());

    imgData->selectedView = ui->selectedView;
    imgData->setSelectedSprite(emptySprite);

    imgData->spriteGrid = spriteGrid;
    QPixmap pixGrid;
    pixGrid = QPixmap::fromImage(imgGrid);
    QPixmap pixSprGrid;
    pixSprGrid = QPixmap::fromImage(spriteGrid);

    scn->setSceneRect(pixGrid.rect());
    scn->addPixmap(pixGrid);

    sScn->setSceneRect(pixSprGrid.rect());
    sScn->addPixmap(pixSprGrid);
    w->show();
    s->show();

}

void MainWindow::on_btPaint_toggled(bool checked)
{
    ui->visualizationView->btPaintPressed = checked;
}

void MainWindow::on_btDump_clicked()
{
    imgData->dumpBgMatrix();
}
