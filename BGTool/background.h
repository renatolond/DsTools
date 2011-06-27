#ifndef BACKGROUND_H
#define BACKGROUND_H

#include <QHash>
#include <QString>
#include <QVector>

class QColor;
class QDomDocument;
class QDomElement;
class QImage;
struct sGlobalData;
typedef unsigned int QRgb;

enum eTileFlipping
{
  NO_FLIPPING,
  VERTICAL_FLIPPING,
  HORIZONTAL_FLIPPING,
  VERTICAL_AND_HORIZONTAL_FLIPPING
};

struct sMapInfo
{
  int m_tile_index;
  eTileFlipping m_tile_flipping;
};

enum eTileCollision
{
  COLLISION_EMPTY,
  COLLISION_FULL,
  COLLISION_45,
  COLLISION_45H,
  COLLISION_45V,
  COLLISION_45VH
};

struct sTileInfo
{
  QImage *m_tile;
  eTileCollision m_tile_collision;
};

class cBackground
{
 protected:
  QVector< QVector<sMapInfo> > m_map_matrix;
  //QVector<QImage *> m_tile;
  QVector<QRgb> m_palette;
  QVector<sTileInfo> m_tile_collision;
  QHash<QRgb, int> m_color_hash;
  QString m_name;
  QColor *m_neutral;
  void find_tile(QImage &p);
  void find_palette(QImage &p);
  void push_back_map_matrix(int y, int tile_index, eTileFlipping tile_flipping);
  void insert_into_palette(QColor c);
  int insert_into_tiles(QImage *tile, eTileFlipping &tile_flipping);
  void clear_background(void);
 public:
  cBackground(QString name, int size_x, int size_y, sGlobalData *global_data);
  sGlobalData *m_global_data;
  void import_image(QString path);
  void export_map_to_ds();
  void export_to_ds();
  const QVector<QRgb>& get_palette(void);
  const QVector<sTileInfo>& get_tiles(void);
  const QVector< QVector<sMapInfo> >& get_map_matrix(void);
  void set_map_matrix(int x, int y, int tile_index, eTileFlipping tile_flipping);
  void export_to_xml(QDomDocument *xml_document, QDomElement *backgrounds_node);
};

#endif // BACKGROUND_H
