#ifndef PLAYERCONTROLLER_H
#define PLAYERCONTROLLER_H
#include "aabb.h"

#include <cmath>

#include "level-data.h"
#include "spritecontroller.h"

template <class T>
class cPlayerController : public AABB<T>
{
  //    double acceleration;
  //    double breaking;
  //    double verticalAcceleration;
  //    double verticalBreaking;
  //    double horizontalSpeed;
  //    double verticalSpeed;
  //    int horizontalDelta;
  //    bool running;
  //    int jumpTime;
  //    bool jumping;
public:
  SpriteController spr;

  cPlayerController();
  cPlayerController(Vector2<T> _pos, T _xw, T _yw, int scr, int sprn, const sLevelData *level_data);
  void Draw();
  //    void isRunning(bool playerState);
  bool isCenteredOnScreen();
  T centerOnScreen();
  T uncenterOnScreen(int scroll);
  void accelerateLeft();
  void accelerateRight();
  void IntegrateVerlet();

  T getParallaxX();
  void accelerateUp(int timer);
  //    void applyGravity();
  //    void applyFriction();
  T getHorizontalSpeed();
  //    int getVerticalSpeed(int timer);
  //    void horizontalAnimation(int horizontalSpeed);
  //    void ceaseMovement() { verticalSpeed = horizontalSpeed = 0; }
  T half_screen(void);
};

template <class T>
T cPlayerController<T>::half_screen(void)
{
  return (screenMaxX-screenMinX)/2;
}

template <class T>
void cPlayerController<T>::Draw()
{
  if(this->pos.x > this->m_level_data->m_world_max_width-half_screen()-this->xw)
  {
    spr.pos.x = (float)((this->pos.x-this->xw -
                         (this->m_level_data->m_world_max_width-(screenMaxX-screenMinX)))/multiplier);
  }
  else if(this->getParallaxX() > 0)
    spr.pos.x = (float)(((screenMaxX-screenMinX)/2 - 2*this->xw)/multiplier);
  else
    spr.pos.x = (float)((this->pos.x-this->xw)/multiplier);
  spr.pos.y = (float)((this->pos.y-this->yw)/multiplier);
  spr.render();
}

template <class T>
T cPlayerController<T>::getParallaxX()
{
  T parallax = this->pos.x - ((screenMaxX-screenMinX)/2 - this->xw);
  if(parallax > this->m_level_data->m_world_max_width-(screenMaxX-screenMinX)-this->xw)
    parallax = this->m_level_data->m_world_max_width-(screenMaxX-screenMinX)-this->xw;
  if(parallax > 0)
    return parallax/multiplier;
  return 0;
}

template <class T>
void cPlayerController<T>::IntegrateVerlet()
{
  AABB<T>::IntegrateVerlet();
  T dx = this->pos.x - this->oldPos.x;

  if ( dx > maxHorizontalSpeed )
    this->pos.x = this->oldPos.x + maxHorizontalSpeed;
  else if ( dx < -maxHorizontalSpeed )
    this->pos.x = this->oldPos.x - maxHorizontalSpeed;

  //    horizontalSpeed = this->pos.x - this->oldPos.x;
}

template <class T>
cPlayerController<T>::cPlayerController() :
  AABB<T>()
{
  //    horizontalSpeed = verticalSpeed = 0;
  //    //acceleration = 0;
  //    verticalAcceleration = 0;
  //    //    breaking = 50;
  //    verticalBreaking = 50;
  //    jumpTime = 0;
}

template <class T>
cPlayerController<T>::cPlayerController(Vector2<T> _pos,
                                        T _xw,
                                        T _yw,
                                        int scr,
                                        int sprn,
                                        const sLevelData *level_data):
  AABB<T>(_pos, _xw, _yw, level_data)
{
}

//void cPlayerController::isRunning(bool playerState)
//{
//    running = playerState;
//}
//
inline void modifySpeed(double &speed, int &delta, double maxSpeed, double speedStep, int signal)
{
  if ( signal*speed < maxSpeed )
  {
    speed += signal*speedStep;
    delta = 1*signal;
  }
  else
    delta = 0;
}

template <class T>
void cPlayerController<T>::accelerateLeft()
{
  this->pos.x -= horizontalSpeedStep;
}

template <class T>
void cPlayerController<T>::accelerateRight()
{
  this->pos.x += horizontalSpeedStep;
}

template <class T>
void cPlayerController<T>::accelerateUp(int timer)
{
  this->pos.y -= verticalSpeedStep;
  //    if ( fabs(verticalSpeed) > eps )
  //        return;
  //
  //    if ( timer - jumpTime < jumpDelay )
  //        return;
  //
  //    jumping = true;
  //
  //    beginAnimation(2);
  //
  //    int jumpHeight = 7*tileSizeY;
  //    verticalSpeed = -15;
  //    verticalSpeed += (screenSizeY-jumpHeight)/100*3.75;
  //    if ( horizontalSpeed >= maxHorizontalSpeed ) verticalSpeed += (horizontalSpeed - maxHorizontalSpeed)/20;
}
//
//void cPlayerController::applyGravity()
//{
//    //    verticalAcceleration = 1;
//    //    verticalBreaking = 5;
//    if( verticalSpeed < maxVerticalSpeed ) {
//        verticalSpeed += verticalSpeedStep;
//    }
//}
//
//void cPlayerController::applyFriction()
//{
//    if ( fabs(horizontalSpeed) < horizontalSpeedStep )
//        horizontalSpeed = 0;
//
//    if ( horizontalSpeed > maxHorizontalSpeed )
//        horizontalSpeed -= horizontalRunningSpeedStep;
//    else if ( horizontalSpeed < -maxHorizontalSpeed )
//        horizontalSpeed += horizontalRunningSpeedStep;
//    else if ( horizontalSpeed > horizontalSpeedStep )
//        horizontalSpeed -= horizontalSpeedStep;
//    else if ( horizontalSpeed < -horizontalSpeedStep )
//        horizontalSpeed += horizontalSpeedStep;
//
//}
//
//void cPlayerController::horizontalAnimation(int horizontalSpeed)
//{
//    if ( !jumping )
//    {
//        if ( abs(horizontalSpeed) > eps )
//        {
//            if ( horizontalDelta * horizontalSpeed < 0 )
//            {
//                beginAnimation(1);
//                if ( horizontalSpeed > 0 )
//                    hflip(1);
//                else
//                    hflip(0);
//            }
//            else
//            {
//                beginAnimation(0);
//                if ( horizontalSpeed > 0 )
//                    hflip(0);
//                else
//                    hflip(1);
//            }
//        }
//        else
//        {
//            stopAnimation();
//        }
//    }
//
//}
//
//
//int cPlayerController::getVerticalSpeed(int timer)
//{
//    //    verticalSpeed += verticalAcceleration - (verticalSpeed) / verticalBreaking;
//    //
//    //    if ( pos.y > screenSizeY+sizeY ) pos.y = -sizeY;
//
//    if ( pos.y+(int)verticalSpeed > (screenSizeY-(3*tileSizeY)-sizeY) )
//    {
//        horizontalAnimation(horizontalSpeed);
//        if ( verticalSpeed > verticalSpeedStep*2 )
//        {
//            jumping = false;
//            jumpTime = timer;
//        }
//        verticalSpeed = 0;
//        verticalAcceleration = 0;
//        verticalBreaking = 10.0f;
//        pos.y = (screenSizeY-(3*tileSizeY)-sizeY);
//    }
//
//    return int(verticalSpeed);
//}
//

#endif // PLAYERCONTROLLER_H
