#ifndef ITEMCONTROLLER_H
#define ITEMCONTROLLER_H

template <class T>
class cItemController : public AABB<T>
{
public:
  SpriteController spr;
  void Draw();
};

template <class T>
void cItemController<T>::Draw()
{
  spr.render();
}

#endif // ITEMCONTROLLER_H
