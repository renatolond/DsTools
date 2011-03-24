#ifndef BACKGROUND_H
#define BACKGROUND_H

#include <QVector>
#include <QString>

class QColor;
class QImage;
struct sGlobalData;
typedef unsigned int QRgb;

class cBackground
{
 protected:
  QVector< QVector<QImage *> > m_map_matrix;
  QVector<QImage *> m_sprites;
  QVector<QColor *> m_palette;
  QString m_name;
  sGlobalData *m_global_data;
  void find_sprites(QImage &p);
  void fill_map_matrix();
  void insert_into_palette(QColor* c);
 public:
  cBackground(QString name, sGlobalData *global_data);
  void import_image(QString path);
  void export_to_ds();
};

#endif // BACKGROUND_H
