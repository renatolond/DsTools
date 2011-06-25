#ifndef MAINCONTROLLER_H
#define MAINCONTROLLER_H

#include "sprite.h"

#include <QRgb>
#include <QColor>
#include <QGraphicsScene>


class cMainWindow;

class cMainController: public QObject
{
  Q_OBJECT

 public:
   cMainController(cMainWindow *window);

   void create_sprite(QString nome, int w, int h);
   void create_sprite(QString nome);
   void save_images(void);
   void delete_images(void);
   int get_current_frame(void);
   void add_current_frame(void);
   void sub_current_frame(void);
   void reset_current_frame(void);
   int get_sprite_size(void);
   void clear_scene(void);
   void add_frame_to_scene(int i);
   cMainWindow* get_main_window_ref(void);
   QGraphicsScene* get_scene(void);
   QRgb toR5G5B5A1(QColor c, QColor * neutral);
   QVector<QRgb> get_palette(QImage &image);


 private:
   cMainWindow *m_window;
   QStringList m_to_delete_files;
   QGraphicsScene *m_scene;
   int m_current_frame;
   cSprite m_sprite;

   QTimer *m_timer;
   bool m_in_animation;

 private slots:
   void new_project();
   void save_project();
   void open_project();
   void close_project();
   void add_frame();
   void del_frame();
   void animate();
   void timed_animation();
   void export_to_DS();
};

#endif // MAINCONTROLLER_H
