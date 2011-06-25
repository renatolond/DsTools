#ifndef SPRITE_H
#define SPRITE_H

#include <QString>
#include <QVector>

class QImage;

class cSprite
{
 private:
  QString m_nome;
  int m_width;
  int m_height;
  QVector<QImage *> m_frame;
  QVector<QString> m_path;

 public:
  cSprite();
  cSprite(QString nome);
  cSprite(QString nome, int width, int height);
  QString get_nome();
  int get_width();
  int get_height();
  void set_width(int w);
  void set_height(int h);
  void set_path(int i, QString str);
  QImage* get_frame(int i);
  QString get_path(int i);
  void clear(void);
  int size(void);
  void add_frame(QString path);
  void del_frame(int pos);
};

#endif // SPRITE_H
