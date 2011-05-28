#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "newprojectwindow.h"
#include "openprojectwindow.h"

#include <QDebug>
#include <QFileDialog>
#include <QFile>
#include <QMessageBox>
#include <QDataStream>
#include <QtXml/QDomDocument>
#include <QtXml/QDomElement>
#include <QDir>
#include <QTimer>
#include <QRgb>
#include <QColor>
#include <QHash>

#define PATH "../SpriteTool/resources/"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    sprite.clear();
    scene = new QGraphicsScene(this);
    currentFrame = -1;
    ui->gv_Canvas->setParent(this);
    ui->gv_Canvas->setScene(scene);

    this->disable();

    connect(ui->btn_NewProject,SIGNAL(clicked()),this,SLOT(newProject()));
    connect(ui->btn_SaveProject,SIGNAL(clicked()),this,SLOT(saveProject()));
    connect(ui->btn_OpenProject,SIGNAL(clicked()),this,SLOT(openProject()));
    connect(ui->btn_CloseProject,SIGNAL(clicked()),this,SLOT(closeProject()));
    connect(ui->btn_Right,SIGNAL(clicked()),this,SLOT(showRight()));
    connect(ui->btn_Left,SIGNAL(clicked()),this,SLOT(showLeft()));
    connect(scene,SIGNAL(changed(QList<QRectF>)),this,SLOT(manageArrows()));
    connect(ui->btn_AddFrame,SIGNAL(clicked()),this,SLOT(addFrame()));
    connect(ui->btn_DeleteFrame,SIGNAL(clicked()),this,SLOT(delFrame()));
    connect(ui->btn_Animate,SIGNAL(clicked()),this,SLOT(animate()));
    connect(ui->btn_Export,SIGNAL(clicked()),this,SLOT(exportDS()));

    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(timedAnimation()));

    inAnimation = false;

}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::disable(void)
{
    ui->btn_NewProject->setEnabled(true);
    ui->btn_OpenProject->setEnabled(true);

    ui->btn_AddFrame->hide();
    ui->btn_DeleteFrame->hide();
    ui->btn_Animate->hide();
    ui->btn_Right->hide();
    ui->btn_Left->hide();
    ui->btn_Export->hide();

    ui->btn_SaveProject->setDisabled(true);
    ui->btn_CloseProject->setDisabled(true);

}

void MainWindow::enable(void)
{
    ui->btn_NewProject->setDisabled(true);
    ui->btn_OpenProject->setDisabled(true);

    ui->btn_AddFrame->show();
    ui->btn_DeleteFrame->show();
    ui->btn_Animate->show();
    ui->btn_Right->show();
    ui->btn_Left->show();
    ui->btn_Export->show();

    ui->btn_SaveProject->setEnabled(true);
    ui->btn_CloseProject->setEnabled(true);
}

void MainWindow::newProject()
{
   NewProjectWindow np(this);

   np.exec();

   qDebug() << "Leu " << sprite.getNome() << " ("
            << sprite.getWidth() << "x" << sprite.getHeight() << ")";

   this->manageArrows();
}

void MainWindow::closeProject()
{
    sprite.clear();    
    toDeleteFiles.clear();

    scene = new QGraphicsScene(this);
    currentFrame = -1;
    ui->gv_Canvas->setParent(this);
    ui->gv_Canvas->setScene(scene);

    disable();

}

void MainWindow::saveProject()
{
    QString filename = QFileDialog::getSaveFileName(this,
                            tr("Salvar Projeto"),PATH,
                            tr("Arquivos XML (*.xml);;All Files (*)"));

    if (filename.isEmpty())
        return;

    qDebug() << "file: " << filename;

    QFile* file = new QFile(filename);

    QDomDocument doc("xmldocument");

    QDomElement docElem;

    if (!file->open(QIODevice::ReadOnly)) //nao existe um arquivo ainda
    {

        qDebug() << "Arquivo novo, criando no SpriteTool";

        docElem = doc.createElement("SpriteTool");
        doc.appendChild(docElem);

    }
    else    //existe um arquivo, pegar o conteudo existente
    {

        qDebug() << "Arquivo existe, usando setcontent";

        QString errormsg;
        int column,line;

        if (!doc.setContent(file, &errormsg, &line, &column))
        {
           qDebug() << errormsg << line << column;
           return;
        }

        file->close();

        docElem = doc.documentElement();
    }

    this->deleteImages();
    this->saveImages();

    qDebug() << "raiz" << doc.documentElement().tagName();

    QDomNodeList nodeList = docElem.elementsByTagName("Sprite");
    QDomElement e;

    bool achou = false;

    for (int i = 0; i < nodeList.size(); i++)
    {
        qDebug() << "Sprite " << i;

        e = nodeList.at(i).toElement();

        qDebug() << e.attribute("name");

        if (e.attribute("name") == this->sprite.getNome())
        {
            qDebug() << "achou!";

            e.setAttribute("sizex",sprite.getWidth());
            e.setAttribute("sizey",sprite.getHeight());

            //se achou, deleta todos os filhos de e, e readiciona depois

            while (e.childNodes().length() > 0)
                e.removeChild(e.firstChild());

            achou = true;

            break;
        }
    }

    if (!achou) //cria um no vazio do pai pra ser o e
    {
        qDebug() << "não achou tags sprite";

        QDomNodeList list = docElem.elementsByTagName("SpriteTool");
        QDomElement pai;

        if (list.isEmpty())        //se não achou filhos da raiz sendo SpriteTool nodes
        {
            if (docElem.tagName() == "SpriteTool")      //ou a raiz é o nó procurado
                pai = docElem;
            else                                        //ou o arquivo nunca foi usado no ST, cria-se o no
            {
                pai = doc.createElement("SpriteTool");

                docElem.appendChild(pai);
            }

        }
        else
        {
            pai = list.at(0).toElement();
        }

        e = doc.createElement("Sprite");

        QDomAttr name = doc.createAttribute("name");
        QDomAttr sizex = doc.createAttribute("sizex");
        QDomAttr sizey = doc.createAttribute("sizey");

        e.setAttributeNode(name);
        e.setAttribute("name",sprite.getNome());

        e.setAttributeNode(sizex);
        e.setAttribute("sizex",sprite.getWidth());

        e.setAttributeNode(sizey);
        e.setAttribute("sizey",sprite.getHeight());

        pai.appendChild(e);

        qDebug() << "criou o no" << e.tagName() << "em " << pai.tagName();

    }

    //adiciona novos filhos em e a partir dos frames atuais

    for (int j = 0; j < sprite.size(); j++)
    {
        QDomElement child = doc.createElement("Frame");
        QDomAttr id = doc.createAttribute("id");
        QDomAttr path = doc.createAttribute("path");

        child.setAttributeNode(id);
        child.setAttribute("id",j);

        child.setAttributeNode(path);
        child.setAttribute("path",sprite.getPath(j));

        qDebug() << sprite.getPath(j);
        qDebug() << child.attribute("path","erro!");

        e.appendChild(child);

     }

    qDebug() << "Salvando modificações";

    file->open(QIODevice::WriteOnly);

    QTextStream out(file);
    doc.save(out,0);

    qDebug() << "fim!";
}

void MainWindow::openProject()
{
    QString filename = QFileDialog::getOpenFileName(this,
                        tr("Abrir Projeto"), "..\\SpriteTool/resources",
                        tr("XML Files (*xml);;All Files (*)"));

    if (filename.isEmpty())
        return;

    QFile *file = new QFile(filename);

    if(!file->open(QIODevice::ReadOnly))
    {
        QMessageBox::information(this, tr("Não foi possível abrir o arquivo"),
                                 file->errorString());
        return;
    }

    QDomDocument doc("xmldocument");
    QDomElement docElem;

    QString errormsg;
    int column,line;

    if (!doc.setContent(file, &errormsg, &line, &column))
    {
       qDebug() << errormsg << line << column;
       return;
    }

    file->close();

    docElem = doc.documentElement();

    OpenProjectWindow ow(this);

    QDomNodeList nodelist = docElem.elementsByTagName("Sprite");

    if (nodelist.isEmpty())
    {
        QMessageBox::information(this,tr("Erro"),"Não existem projetos de Sprite no arquivo");
        return;
    }

    for (int i = 0; i < nodelist.size(); i++)
    {
        QDomElement e = nodelist.at(i).toElement();

        ow.addSpriteOption(e.attribute("name"));
    }

    ow.exec();

    if (sprite.getNome() == "")
        return;

    for (int i = 0; i < nodelist.size(); i++)
    {
        QDomElement e = nodelist.at(i).toElement();

        if (e.attribute("name") == sprite.getNome())
        {
            sprite.setWidth(e.attribute("sizex").toInt());
            sprite.setHeight(e.attribute("sizey").toInt());

            //percorrer os filhos e adicionar os frames
            QDomNodeList children = e.childNodes();

            for (int j = 0; j < children.size(); j++)
            {
                qDebug() << "OPEN: Frame" << children.at(j).toElement().attribute("path");

                //mandar o caminho completo pro addframe

                QString imgname = children.at(j).toElement().attribute("path");
                QString filepath = PATH + sprite.getNome();

                sprite.addFrame(filepath+"/"+imgname);
            }

            break;
        }
    }

    showFrame(0);

    manageArrows();

}

void MainWindow::showFrame(int i)
{
    scene->clear();

    QImage img = * sprite.getFrame(i);

    scene->addPixmap(QPixmap::fromImage(img.scaled(64,64,Qt::KeepAspectRatio,Qt::FastTransformation)));

    this->ui->gv_Canvas->setScene(scene);
    this->ui->gv_Canvas->show();

    this->currentFrame = i;
}

void MainWindow::showLeft()
{
    currentFrame--;

    this->showFrame(currentFrame);

    manageArrows();

}

void MainWindow::showRight()
{
    currentFrame++;

    this->showFrame(currentFrame);

    manageArrows();

}

void MainWindow::manageArrows()
{
    if (inAnimation) return;

    qDebug() << "manageArrows: currentFrame" << currentFrame;
    qDebug() << "manageArrows: sprite size" << sprite.size();

    if (sprite.size() == 1)
    {
        ui->btn_Left->setDisabled(true);
        ui->btn_Right->setDisabled(true);

        return;
    }

    if (currentFrame <= 0)
        ui->btn_Left->setDisabled(true);
    else
        ui->btn_Left->setEnabled(true);

    if (currentFrame >= sprite.size()-1)
        ui->btn_Right->setDisabled(true);
    else
        ui->btn_Right->setEnabled(true);
}

void MainWindow::timedAnimation()
{
   // qDebug() << "currentframe do timer:" << currentFrame;

    if (currentFrame < sprite.size())
    {
        this->showFrame(currentFrame);
        currentFrame++;
    }
    else
    {
        currentFrame = 0;
    }

    timer->start();

}

void MainWindow::animate()
{

    if (ui->btn_Animate->text() == "Animate")
    {
        ui->btn_Animate->setText("Stop");

        ui->btn_AddFrame->setDisabled(true);
        ui->btn_DeleteFrame->setDisabled(true);
        ui->btn_Left->setDisabled(true);
        ui->btn_Right->setDisabled(true);
        ui->btn_CloseProject->setDisabled(true);
        ui->btn_SaveProject->setDisabled(true);
        ui->btn_Export->setDisabled(true);

        timer->setInterval(250);
        timer->start();

        inAnimation = true;
    }
    else if (ui->btn_Animate->text() == "Stop")
    {
        ui->btn_Animate->setText("Animate");

        this->showFrame(0);

        timer->stop();
        inAnimation = false;

        ui->btn_AddFrame->setEnabled(true);
        ui->btn_DeleteFrame->setEnabled(true);
        ui->btn_Left->setEnabled(true);
        ui->btn_Right->setEnabled(true);
        ui->btn_CloseProject->setEnabled(true);
        ui->btn_SaveProject->setEnabled(true);
        ui->btn_Export->setEnabled(true);
    }

}

void MainWindow::createSprite(QString nome, int w, int h)
{
    this->sprite = Sprite(nome,w,h);

    this->enable();
}

void MainWindow::createSprite(QString nome)
{
    this->sprite = Sprite(nome);

    this->enable();
}

void MainWindow::addFrame()
{
    QString filename = QFileDialog::getOpenFileName(this,
                        tr("Abrir Projeto"), PATH,
                        tr("PNG Files (*png);;All Files (*)"));

    if (filename.isEmpty())
        return;

    qDebug() << "adicionando o frame" << filename;

    //o addFrame recebe o caminho inteiro do frame pq a imagem vai ser construida
    //dentro da função. O caminho é mudado so pro nome do arquivo no SaveImages
    //como pos processamento, na hora que tudo e salvo.

    sprite.addFrame(filename);

    if (sprite.size() == 1)
    {
        currentFrame = 0;
        this->showFrame(currentFrame);
    }

    //chamar o managearrows
    this->manageArrows();

    //verifica se o arquivo adicionado ja tinha sido apagado
    QString imgname = filename.split("/").last();

    //procura e remove uma ocorrencia daquela string, se tiver
    toDeleteFiles.removeOne(imgname);
}

QRgb toR5G5B5A1(QColor c, QColor * neutral)
{
    if (c.alpha()!= 255)
    {
        c = *neutral;
        c.setAlpha(255);
    }

  unsigned int color;
  color = c.red();
  color = color >> 3;
  color = color << 3;
  c.setRed(color);

  color = c.green();
  color = color >> 3;
  color = color << 3;
  c.setGreen(color);

  color = c.blue();
  color = color >> 3;
  color = color << 3;
  c.setBlue(color);

  return c.rgba();
}

QVector<QRgb> get_palette(QImage &image)
{
    QVector<QRgb> palette;
    QColor * m_neutral;

  m_neutral = new QColor(Qt::magenta);
  m_neutral->setAlpha(0); // 0 significa que a cor não é visível
  m_neutral->setRed(255);
  m_neutral->setGreen(0);
  m_neutral->setBlue(255);

  palette.push_back(m_neutral->rgba());

  QColor c;
  c.setRgba(toR5G5B5A1(*m_neutral, m_neutral));

  QHash<QRgb,int> m_color_hash;

  m_color_hash[c.rgba()] = 0;

  for(int i(0); i < image.height(); i++)
  {
    for(int j(0); j < image.width(); j++)
    {
      c.setRgba(toR5G5B5A1(image.pixel(j, i), m_neutral));
      if(!m_color_hash.contains(c.rgba()))
      {
        m_color_hash[c.rgba()] = palette.size();
        palette.push_back(c.rgba());
      }
    }
  }

  return palette;
}


void MainWindow::exportDS()
{
    QVector<QImage> pImg;

    QString pal, spr;

    pal = "../gfx/bin/" + sprite.getNome() + "_Pal.bin";

    // exporting palette
    QFile file_pal(pal);

    if (file_pal.open(QIODevice::WriteOnly | QFile::Truncate))
    {
        QDataStream out(&file_pal);

        int k = 0;
        //exporta a palette
        for (int i = 0; i < sprite.size();  i++)
        {

            QVector<QRgb> palette = get_palette(*sprite.getFrame(i));

            pImg.push_back(sprite.getFrame(i)->convertToFormat(QImage::Format_Indexed8, palette, Qt::AvoidDither));



            for ( int j = 0 ; j < palette.size() ; j++ )
            {
                QColor c;
                c = palette[j];

                unsigned char high, low;
                high = 1;
                high = high << 5;
                high += ( c.blue() >> 3 );
                high = high << 2;
                high += ( c.green() >> 6 );

                unsigned char green = c.green() - ((c.green() >> 6)<<6);
                low = (green >> 3);
                low = low << 5;
                low += ( c.red() >> 3);

                out.writeRawData((const char *)&low, 1);
                out.writeRawData((const char *)&high, 1);

            }

            k += palette.size();

        }

        for ( int j = k ; j < 256 ; j++ )
        {
            unsigned char zero;
            zero = 0;
            out.writeRawData((const char *)&zero, 1);
            out.writeRawData((const char *)&zero, 1);
        }
    }

    file_pal.close();

    qDebug() << "Palette exportada!";

    spr = "../gfx/bin/" + sprite.getNome() + "_Sprite.bin";

    //exportar o sprite
    QFile file_spr(spr);

    if (file_spr.open(QIODevice::WriteOnly | QFile::Truncate))
    {
        QDataStream out(&file_spr);

        int paletteBias = 0;

        for (int it = 0; it < sprite.size(); it++)
        {
            QImage img = pImg.at(it);

            for (int i = 0; i < sprite.getHeight()/8; i++)
            {
                for (int j = 0; j < sprite.getWidth()/8; j++)
                {
                    for (int ii = 0; ii < 8; ii++)
                    {
                        for (int jj = 0; jj < 8; jj++)
                        {
                            unsigned char color_index;

                            if (img.pixelIndex(8*j+jj,8*i+ii) == 0)
                                color_index = 0;
                            else
                                color_index = img.pixelIndex(8*j+jj,8*i+ii) + paletteBias;
                            out.writeRawData((const char *)&color_index,1);
                        }
                    }


                }
            }

            paletteBias += img.colorTable().size();
        }
    }

    file_spr.close();

    qDebug() << "Sprite Exportado!";

}

void MainWindow::saveImages()
{
    //salva as imagens na pasta resources/nomedoprojeto

    QString filepath = PATH + sprite.getNome();

    if (!QDir(filepath).exists())
        QDir().mkdir(filepath);

    for (int i = 0; i < sprite.size(); i++)
    {
        QImage* img = sprite.getFrame(i);

        QString imgname = sprite.getPath(i).split("/").last();

        sprite.setPath(i,imgname);
        qDebug() << "Mudando o xml p/" << imgname;

        img->save(filepath+"/"+imgname);
    }

}

void MainWindow::deleteImages()
{
    qDebug() << "entrou no deleteImages";

    while (!toDeleteFiles.isEmpty())
    {
        QString imgname = toDeleteFiles.first();
        toDeleteFiles.removeFirst();

        QString filepath = PATH + sprite.getNome();

        qDebug() << "deletar " << filepath;

        QDir().remove(filepath+"/"+imgname);
    }
}

void MainWindow::delFrame()
{
    // ao deletar um frame que ta sendo mostrado, voltar pro anterior
    // se for o primeiro, ir pro seguinte
    // se for o unico, deixar a tela em branco.

    qDebug() << "Path pra deletar: " << sprite.getPath(currentFrame);

    QString imgname = sprite.getPath(currentFrame).split("/").last();

    qDebug() << "Adicionando na dellist: " << imgname;

    this->toDeleteFiles.push_back(imgname);

    if (currentFrame != 0)
    {
        this->showLeft();
        sprite.delFrame(currentFrame+1);
    }
    else if (sprite.size() > 1)
    {
        this->showRight();
        sprite.delFrame(currentFrame-1);
    }
    else
    {
        sprite.delFrame(currentFrame);
        currentFrame = -1;

    }


}
