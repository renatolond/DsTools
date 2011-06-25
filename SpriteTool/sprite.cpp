#include "sprite.h" // Class definition

#include <QImage>

cSprite::cSprite()
{
}

cSprite::cSprite(QString nome, int width, int height)
{
  m_nome = nome;
  m_width = width;
  m_height = height;
}

cSprite::cSprite(QString nome)
{
  m_nome = nome;
}

QString cSprite::get_nome()
{
  return m_nome;
}

int cSprite::get_height()
{
  return m_height;
}

int cSprite::get_width()
{
  return m_width;
}

void cSprite::set_height(int h)
{
  m_height = h;
}

void cSprite::set_width(int w)
{
  m_width = w;
}

void cSprite::set_path(int i, QString str)
{
  m_path[i] = str;
}

QImage* cSprite::get_frame(int i)
{
  return m_frame[i];
}

QString cSprite::get_path(int i)
{
  return m_path[i];
}

int cSprite::size()
{
  return m_path.size();
}

void cSprite::add_frame(QString path)
{
  QImage *img = new QImage(path);

  m_frame.push_back(img);
  m_path.push_back(path);
}

void cSprite::del_frame(int pos)
{
  QImage *img = m_frame[pos];

  m_frame.remove(pos);
  m_path.remove(pos);

  delete(img);
}

void cSprite::clear()
{
  m_nome = "";
  m_width = 0;
  m_height = 0;

  for(int i(0); i < m_frame.size(); ++i)
  {
    delete(m_frame[i]);

    m_path[i] = "";
  }
}

