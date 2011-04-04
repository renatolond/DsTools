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

#include <QPixmap>
#include <QGraphicsScene>
#include <QGraphicsView>

#define PATH "..\resources"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    sprite.clear();
    scene = new QGraphicsScene(this);
    ui->gv_Canvas = new QGraphicsView(scene);

    this->disable();

    connect(ui->btn_NewProject,SIGNAL(clicked()),this,SLOT(newProject()));
    connect(ui->btn_SaveProject,SIGNAL(clicked()),this,SLOT(saveProject()));
    connect(ui->btn_OpenProject,SIGNAL(clicked()),this,SLOT(openProject()));
    connect(ui->btn_CloseProject,SIGNAL(clicked()),this,SLOT(closeProject()));

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

    ui->btn_SaveProject->setDisabled(true);
    ui->btn_CloseProject->setDisabled(true);
}

void MainWindow::enable(void)
{
    ui->btn_NewProject->setDisabled(true);
    ui->btn_OpenProject->setDisabled(true);

    ui->btn_AddFrame->show();
    ui->btn_DeleteFrame->show();

    ui->btn_SaveProject->setEnabled(true);
    ui->btn_CloseProject->setEnabled(true);
}

void MainWindow::newProject()
{
   NewProjectWindow np(this);

   np.exec();

   qDebug() << "Leu " << sprite.getNome() << " ("
            << sprite.getWidth() << "x" << sprite.getHeight() << ")";
}

void MainWindow::closeProject()
{
    sprite.clear();
    disable();
}

void MainWindow::saveProject()
{
    QString filename = QFileDialog::getSaveFileName(this,
                            tr("Salvar Projeto"),"..\\",
                            tr("Arquivos XML (*.xml);;All Files (*)"));

    // mudar "..\\" pra pasta resources

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
                        tr("Abrir Projeto"), "..\\",
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
                qDebug() << "Frame" << children.at(j).toElement().attribute("path");

                sprite.addFrame(children.at(j).toElement().attribute("path"));
            }

            break;
        }
    }

    showFrame(0);

}

void MainWindow::showFrame(int i)
{

    QGraphicsView *pal = ui->gv_Canvas;
    QGraphicsScene *palScn = new QGraphicsScene(pal);
    pal->setScene(palScn);
    QPixmap palPix = palPix.fromImage(*sprite.getFrame(i));
    palScn->setSceneRect(0,0,palPix.width(), palPix.height());
    palScn->addPixmap(palPix);
    pal->show();


    //scene->addPixmap(QPixmap::fromImage(*sprite.getFrame(i)));

    //this->ui->gv_Canvas->setScene(scene);
    //this->ui->gv_Canvas->show();


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
