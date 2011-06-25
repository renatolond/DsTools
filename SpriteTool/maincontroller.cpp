#include "maincontroller.h"
#include "mainwindow.h"
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
#define TIMEINTERVAL 250
#define EXPORTFOLDER "../gfx/bin/"
#define SPRITEFORMAT "_Sprite.bin"
#define PALLETEFORMAT "_Pal.bin"

cMainController::cMainController(cMainWindow *window)
{

  m_window = window;
  m_sprite.clear();
  m_scene = new QGraphicsScene(this);
  m_current_frame = -1;

  m_timer = new QTimer(this);

  connect(m_timer,SIGNAL(timeout()),this,SLOT(timed_animation()));
  connect(m_scene,SIGNAL(changed(QList<QRectF>)),m_window,SLOT(manage_bounds()));
}

int cMainController::get_current_frame(void)
{
  return m_current_frame;
}

void cMainController::add_current_frame(void)
{
  m_current_frame++;
}

void cMainController::sub_current_frame(void)
{
  m_current_frame--;
}

int cMainController::get_sprite_size(void)
{
  return m_sprite.size();
}

QGraphicsScene* cMainController::get_scene(void)
{
  return m_scene;
}

void cMainController::clear_scene(void)
{
  m_scene->clear();
}

void cMainController::add_frame_to_scene(int i)
{
  QImage img = * m_sprite.get_frame(i);

  m_scene->addPixmap(QPixmap::fromImage(img.scaled(64,64,Qt::KeepAspectRatio,
                                                   Qt::FastTransformation)));

  m_current_frame = i;
}

cMainWindow* cMainController::get_main_window_ref(void)
{
  return m_window;
}

void cMainController::new_project()
{
  cNewProjectWindow np(this);

  np.exec();

  m_window->call_manage_bounds();
}

void cMainController::close_project()
{
  m_sprite.clear();
  m_to_delete_files.clear();

  m_scene = new QGraphicsScene(this);
  m_current_frame = -1;

  m_window->reset();
}

void cMainController::save_project()
{
  QString filename = QFileDialog::getSaveFileName(m_window,
                       tr("Salvar Projeto"),PATH,
                       tr("Arquivos XML (*.xml);;All Files (*)"));

  if(filename.isEmpty())
    return;

  QFile* file = new QFile(filename);

  QDomDocument doc("xmldocument");

  QDomElement docElem;

  if(!file->open(QIODevice::ReadOnly)) //file doesnt exists
  {
    docElem = doc.createElement("SpriteTool");
    doc.appendChild(docElem);

  }
  else    //get de file content
  {
    QString errormsg;
    int column,line;

    if(!doc.setContent(file, &errormsg, &line, &column))
    {
      return;
    }

    file->close();

    docElem = doc.documentElement();
  }

  delete_images();
  save_images();

  QDomNodeList nodeList = docElem.elementsByTagName("Sprite");
  QDomElement e;

  bool achou = false;

  for(int i(0); i < nodeList.size(); i++)
  {
    e = nodeList.at(i).toElement();

    if(e.attribute("name") == m_sprite.get_nome())
    {
      e.setAttribute("sizex",m_sprite.get_width());
      e.setAttribute("sizey",m_sprite.get_height());

      //delete all the children, and re add them all later

      while(e.childNodes().length() > 0)
        e.removeChild(e.firstChild());

      achou = true;

      break;
    }
  }

  if(!achou) //creat a new node to be 'e'
  {

    QDomNodeList list = docElem.elementsByTagName("SpriteTool");
    QDomElement pai;

    if(list.isEmpty())        //theres no SpriteTool nodes in the root
    {
      if(docElem.tagName() == "SpriteTool")      //case 1: the root is this search goal
      {
        pai = docElem;
      }
      else                                       //case 2: this file has never been opened in ST
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
    e.setAttribute("name",m_sprite.get_nome());

    e.setAttributeNode(sizex);
    e.setAttribute("sizex",m_sprite.get_width());

    e.setAttributeNode(sizey);
    e.setAttribute("sizey",m_sprite.get_height());

    pai.appendChild(e);

  }

  // add new children to 'e' based on the current frames

  for (int j(0); j < m_sprite.size(); ++j)
  {
    QDomElement child = doc.createElement("Frame");
    QDomAttr id = doc.createAttribute("id");
    QDomAttr path = doc.createAttribute("path");

    child.setAttributeNode(id);
    child.setAttribute("id",j);

    child.setAttributeNode(path);
    child.setAttribute("path",m_sprite.get_path(j));

    e.appendChild(child);

  }

  file->open(QIODevice::WriteOnly);

  QTextStream out(file);
  doc.save(out,0);

}

void cMainController::open_project()
{
  QString filename = QFileDialog::getOpenFileName(m_window,
                      tr("Abrir Projeto"), "..\\SpriteTool/resources",
                      tr("XML Files (*xml);;All Files (*)"));

  if(filename.isEmpty())
    return;

  QFile *file = new QFile(filename);

  if(!file->open(QIODevice::ReadOnly))
  {
    QMessageBox::information(m_window, tr("Não foi possível abrir o arquivo"),
                                 file->errorString());
    return;
  }

  QDomDocument doc("xmldocument");
  QDomElement docElem;

  QString errormsg;
  int column,line;

  if(!doc.setContent(file, &errormsg, &line, &column))
  {
    return;
  }

  file->close();

  docElem = doc.documentElement();

  cOpenProjectWindow ow(this);

  QDomNodeList nodelist = docElem.elementsByTagName("Sprite");

  if(nodelist.isEmpty())
  {
    QMessageBox::information(m_window,tr("Erro"),"Não existem projetos de Sprite no arquivo");
    return;
  }

  for(int i(0); i < nodelist.size(); ++i)
  {
    QDomElement e = nodelist.at(i).toElement();

    ow.add_sprite_option(e.attribute("name"));
  }

  ow.exec();

  if(m_sprite.get_nome() == "")
    return;

  for(int i(0); i < nodelist.size(); ++i)
  {
    QDomElement e = nodelist.at(i).toElement();

    if(e.attribute("name") == m_sprite.get_nome())
    {
      m_sprite.set_width(e.attribute("sizex").toInt());
      m_sprite.set_height(e.attribute("sizey").toInt());

      // add frames in child nodes
      QDomNodeList children = e.childNodes();

      for(int j(0); j < children.size(); ++j)
      {
      // send the full path to add_frame method

        QString imgname = children.at(j).toElement().attribute("path");
        QString filepath = PATH + m_sprite.get_nome();

        m_sprite.add_frame(filepath+"/"+imgname);
      }

      break;
    }
  }

  m_window->show_frame(0);
  m_current_frame = 0;

}



void cMainController::timed_animation()
{
   // qDebug() << "currentframe do timer:" << currentFrame;

  if(m_current_frame < m_sprite.size())
  {
    m_window->show_frame(m_current_frame);

    m_current_frame++;
  }
  else
  {
    m_current_frame = 0;
  }

  m_timer->start();

}

void cMainController::animate()
{

  if(!m_window->in_animation())
  {
    m_timer->setInterval(TIMEINTERVAL);
    m_timer->start();

    m_window->set_animation_mode();
  }
  else
  {
    m_timer->stop();

    m_window->set_edit_mode();
  }

}

void cMainController::create_sprite(QString nome, int w, int h)
{
  m_sprite = cSprite(nome,w,h);

  m_window->enable();
}

void cMainController::create_sprite(QString nome)
{
  m_sprite = cSprite(nome);

  m_window->enable();
}

void cMainController::add_frame()
{ 
  QString filename = QFileDialog::getOpenFileName(m_window,
                        tr("Abrir Projeto"), PATH,
                        tr("PNG Files (*png);;All Files (*)"));

  if(filename.isEmpty())
    return;

  // this method retrieves the frame's full path and creates the image
  // the path is not changed until the end of the workflow (in save_images)

  m_sprite.add_frame(filename);

  if(m_sprite.size() == 1)
  {
    m_current_frame = 0;
    m_window->show_frame(m_current_frame);
  }

  // check if the file has been already put in deletelist
  QString imgname = filename.split("/").last();

  m_to_delete_files.removeOne(imgname);

  m_window->call_manage_bounds();
}

QRgb cMainController::toR5G5B5A1(QColor c, QColor * neutral)
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

QVector<QRgb> cMainController::get_palette(QImage &image)
{
  QVector<QRgb> palette;
  QColor * m_neutral;

  m_neutral = new QColor(Qt::magenta);
  m_neutral->setAlpha(0);     // 0 means not visible
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


void cMainController::export_to_DS(void)
{
  QVector<QImage> pImg;
  QString pal, spr;

  pal = EXPORTFOLDER + m_sprite.get_nome() + PALLETEFORMAT;

  // exporting palette
  QFile file_pal(pal);

  if(file_pal.open(QIODevice::WriteOnly | QFile::Truncate))
  {
    QDataStream out(&file_pal);

    int k = 0;

    for(int i(0); i < m_sprite.size(); ++i)
    {
      QVector<QRgb> palette = get_palette(*m_sprite.get_frame(i));

      pImg.push_back(m_sprite.get_frame(i)->convertToFormat(QImage::Format_Indexed8,
                                                            palette, Qt::AvoidDither));

      for(int j(0); j < palette.size(); ++j)
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

    for(int j(k); j < 256; ++j)
    {
      unsigned char zero;
      zero = 0;
      out.writeRawData((const char *)&zero, 1);
      out.writeRawData((const char *)&zero, 1);
    }
  }

  file_pal.close();

  spr = EXPORTFOLDER + m_sprite.get_nome() + SPRITEFORMAT;

  //exporting sprite
  QFile file_spr(spr);

  if(file_spr.open(QIODevice::WriteOnly | QFile::Truncate))
  {
    QDataStream out(&file_spr);

    int paletteBias = 0;

    for(int it(0); it < m_sprite.size(); ++it)
    {
      QImage img = pImg.at(it);

      for(int i(0); i < m_sprite.get_height()/8; ++i)
      {
        for(int j(0); j < m_sprite.get_width()/8; ++j)
        {
          for(int ii(0); ii < 8; ++ii)
          {
            for(int jj(0); jj < 8; ++jj)
            {
              unsigned char color_index;

              if(img.pixelIndex(8*j+jj,8*i+ii) == 0)
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
}

void cMainController::save_images()
{
  //Save the image files on resources/projectname folder.

  QString filepath = PATH + m_sprite.get_nome();

  if(!QDir(filepath).exists())
    QDir().mkdir(filepath);

  for(int i(0); i < m_sprite.size(); ++i)
  {
    QImage* img = m_sprite.get_frame(i);
    QString imgname = m_sprite.get_path(i).split("/").last();

    m_sprite.set_path(i,imgname);
    img->save(filepath+"/"+imgname);
  }

}

void cMainController::delete_images()
{
  //Delete the image files from resources/projectname folder.

  while(!m_to_delete_files.isEmpty())
  {
    QString imgname = m_to_delete_files.first();

    m_to_delete_files.removeFirst();

    QString filepath = PATH + m_sprite.get_nome();
    QDir().remove(filepath+"/"+imgname);
  }
}

void cMainController::reset_current_frame(void)
{
  m_current_frame = -1;
  clear_scene();

  m_window->call_manage_bounds(); //
}

void cMainController::del_frame()
{  

  QString imgname = m_sprite.get_path(m_current_frame).split("/").last();

  m_to_delete_files.push_back(imgname);

  int del_position = m_window->delete_procedure(m_current_frame);
  m_sprite.del_frame(del_position);
}
