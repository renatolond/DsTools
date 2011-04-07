#ifndef VIEWCONTROLLER_H
#define VIEWCONTROLLER_H

class cBackground;
class QGraphicsView;
class SpritesGraphicsView;
class VisualizationGraphicsView;
struct sGlobalData;

class cViewController
{
  cBackground *m_background;
  QGraphicsView *m_palette_view;
  QGraphicsView *m_selected_sprite_view;
  sGlobalData *m_global_data;
  SpritesGraphicsView *m_sprites_view;
  VisualizationGraphicsView *m_editor_view;
  int m_sprites_per_row;
  int m_sprites_per_column;

 public:
  cViewController(void);
  void set_background(cBackground *background);
  void set_editor_view(VisualizationGraphicsView *editor_view);
  void set_global_data(sGlobalData *global_data);
  void set_palette_view(QGraphicsView *palette_view);
  void set_selected_sprite_view(QGraphicsView *selected_sprite_view);
  void set_sprites_view(SpritesGraphicsView *sprites_view);
  void update_editor_view(void);
  void update_palette_view(void);
  void update_selected_sprite_view(void);
  void update_sprites_view(void);
  void update_views(void);
};

#endif // VIEWCONTROLLER_H
