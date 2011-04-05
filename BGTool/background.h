#ifndef BACKGROUND_H
#define BACKGROUND_H

#include <QHash>
#include <QString>
#include <QVector>

class QColor;
class QImage;
struct sGlobalData;
typedef unsigned int QRgb;

enum eSpriteFlipping
{
  NO_FLIPPING,
  VERTICAL_FLIPPING,
  HORIZONTAL_FLIPPING,
  VERTICAL_AND_HORIZONTAL_FLIPPING
};

struct sSpriteInfo
{
  int sprite_index;
  eSpriteFlipping sprite_flipping;
};

class cBackground
{
 protected:
  QVector< QVector<sSpriteInfo> > m_map_matrix;
  QVector<QImage *> m_sprites;
  QVector<QRgb> m_palette;
  QHash<QRgb, int> m_color_hash;
  QString m_name;
  QColor *m_neutral;
  sGlobalData *m_global_data;
  void find_sprites(QImage &p);
  void find_palette(QImage &p);
  void push_back_map_matrix(int y, int sprite_index, eSpriteFlipping sprite_flipping);
  void insert_into_palette(QColor c);
  int insert_into_sprites(QImage *sprite, eSpriteFlipping &sprite_flipping);
 public:
  cBackground(QString name, int size_x, int size_y, sGlobalData *global_data);
  void import_image(QString path);
  void export_to_ds();
};

#endif // BACKGROUND_H
