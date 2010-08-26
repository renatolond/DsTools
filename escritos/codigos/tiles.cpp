void MainWindow::on_pushButton_clicked()
{
    QGraphicsView *w = ui->visualizationView;
    QGraphicsView *s = ui->spritesView;
    QGraphicsScene *scn = new QGraphicsScene(w);
    QGraphicsScene *sScn = new QGraphicsScene(s);

    w->setScene(scn);
    s->setScene(sScn);
    QPixmap pix("../gfx/teste.png");

    QImage img(pix.toImage());
    int newHeight = pix.height()/8-1 + pix.height();
    int newWidth = pix.width()/8-1 + pix.width();
    QImage imgGrid;
    imgGrid = QImage(newWidth, newHeight, img.format());

    std::cout << "Height " << newHeight << std::endl << "Width " << newWidth << std::endl;

    imgGrid.fill(QColor(0,0,0).rgb());
    QImage spriteGrid;
    {
        std::vector<QImage> sprites;

        int i; int j;
        int startI; int startJ; startI = startJ = 0;

        int spritesI = pix.height() / 8;
        int spritesJ = pix.width() / 8;

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

                int exists = 0;

                for ( std::vector<QImage>::iterator it = sprites.begin(); it != sprites.end() ; it++ )
                {
                    if ( (*it == sprite) )
                    {
                        exists = 1;
                        break;
                    }
                }

                if ( !exists )
                {
                    std::cout << "New sprite at " << j*8 << "," << i*8 << std::endl;
                    sprites.push_back(sprite);
                }
            }
        }

        spriteGrid = QImage(8*4+4, 2*sprites.size()+(2*sprites.size()/8-1), img.format());
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
