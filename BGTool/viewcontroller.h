#ifndef VIEWCONTROLLER_H
#define VIEWCONTROLLER_H

#include <QVector>

class cBackground;
class QGraphicsRectItem;
class QGraphicsView;
class QGraphicsRectItem;
class cTilesGraphicsView;
class VisualizationGraphicsView;
struct sGlobalData;


struct sAction
{
  enum eActionType
  {
    PAINT
  };

  eActionType type;
  int x;
  int y;
  int n_x;
  int n_y;
};

class cViewController
{
  cBackground *m_background;
  QGraphicsRectItem *m_selected_tile_rect;
  QGraphicsView *m_palette_view;
  QGraphicsView *m_selected_tile_view;
  sGlobalData *m_global_data;
  cTilesGraphicsView *m_tiles_view;
  VisualizationGraphicsView *m_editor_view;
  QVector<sAction *> m_undo_buffer;
  bool m_selected_tile_vflip;
  bool m_selected_tile_hflip;
  bool m_paint_mode;
  int m_tiles_per_column;
  int m_tiles_per_row;
  int m_selected_tile_index;
 protected:
  void get_tile_coords_from_view_coords(int x, int y, int &map_x, int &map_y);
  void get_view_coords_from_tile_coords(int map_x, int map_y, int &x, int &y);

 public:
  cViewController(void);
  void set_background(cBackground *background);
  void set_editor_view(VisualizationGraphicsView *editor_view);
  void set_global_data(sGlobalData *global_data);
  void set_paint_mode(bool status);
  void set_palette_view(QGraphicsView *palette_view);
  void set_selected_tile_view(QGraphicsView *selected_tile_view);
  void set_selected_tile_hflip(bool status);
  void set_selected_tile_vflip(bool status);
  void set_tiles_view(cTilesGraphicsView *tiles_view);

  void dump_map_matrix(void);
  void editor_view_clicked(int x, int y);
  void editor_view_clicked_paint(int x, int y);
  void export_background(void);
  void export_to_png(void);
  void highlight_selected_tile(void);
  void tiles_view_clicked(int x, int y);
  void turn_off_highlight(void);
  void update_editor_view(void);
  void update_palette_view(void);
  void update_selected_tile_view(void);
  void update_tiles_view(void);
  void update_views(void);

};

#endif // VIEWCONTROLLER_H
