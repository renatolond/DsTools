#ifndef VIEWCONTROLLER_H
#define VIEWCONTROLLER_H

#include <QVector>

class cBackground;
class QGraphicsView;
class SpritesGraphicsView;
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
  QGraphicsView *m_palette_view;
  QGraphicsView *m_selected_sprite_view;
  sGlobalData *m_global_data;
  SpritesGraphicsView *m_sprites_view;
  VisualizationGraphicsView *m_editor_view;
  QVector<sAction *> m_undo_buffer;
  bool m_paint_mode;
  int m_sprites_per_row;
  int m_sprites_per_column;
  int m_selected_sprite;
 protected:
  void get_map_coords_from_view_coords(int x, int y, int &map_x, int &map_y);
  void get_view_coords_from_map_coords(int map_x, int map_y, int &x, int &y);

 public:
  cViewController(void);
  void set_background(cBackground *background);
  void set_editor_view(VisualizationGraphicsView *editor_view);
  void set_global_data(sGlobalData *global_data);
  void set_paint_mode(bool status);
  void set_palette_view(QGraphicsView *palette_view);
  void set_selected_sprite_view(QGraphicsView *selected_sprite_view);
  void set_sprites_view(SpritesGraphicsView *sprites_view);

  void dump_map_matrix(void);
  void editor_view_clicked(int x, int y);
  void editor_view_clicked_paint(int x, int y);
  void export_background(void);
  void export_to_png(void);
  void highlight_selected_sprite(void);
  void sprites_view_clicked(int x, int y);
  void turn_off_highlight(void);
  void update_editor_view(void);
  void update_palette_view(void);
  void update_selected_sprite_view(void);
  void update_sprites_view(void);
  void update_views(void);

};

#endif // VIEWCONTROLLER_H
