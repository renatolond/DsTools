#ifndef PLAYERCONTROLLER_H
#define PLAYERCONTROLLER_H

#include "spritecontroller.h"
#include "aabb.h"

#include <cmath>

template <class T>
        class PlayerController : public AABB<T>
{
    double acceleration;
    double breaking;
    double verticalAcceleration;
    double verticalBreaking;
    double horizontalSpeed;
    double verticalSpeed;
    int horizontalDelta;
    //    bool running;
    //    int jumpTime;
    //    bool jumping;
public:
    SpriteController spr;
    
    PlayerController();
    PlayerController(Vector2<T> _pos, T _xw, T _yw, int scr, int sprn);
    void Draw();
    //    void isRunning(bool playerState);
    bool isCenteredOnScreen();
    T centerOnScreen();
    T uncenterOnScreen(int scroll);
    void accelerateLeft();
    void accelerateRight();
    void IntegrateVerlet();
    //    void accelerateUp(int timer);
    //    void applyGravity();
    //    void applyFriction();
    T getHorizontalSpeed();
    //    int getVerticalSpeed(int timer);
    //    void horizontalAnimation(int horizontalSpeed);
    //    void ceaseMovement() { verticalSpeed = horizontalSpeed = 0; }
};

template <class T>
        void PlayerController<T>::Draw()
{
    spr.pos.x = (float)((this->pos.x - this->xw)/multiplier);
    spr.pos.y = (float)((this->pos.y - this->yw)/multiplier);
    spr.render();
}

template <class T>
        void PlayerController<T>::IntegrateVerlet()
{
    AABB<T>::IntegrateVerlet();
    if ( this->pos.x - this->oldPos.x > maxHorizontalSpeed )
        this->pos.x = this->oldPos.x + maxHorizontalSpeed;
    else if ( this->pos.x - this->oldPos.x < -maxHorizontalSpeed )
        this->pos.x = this->oldPos.x - maxHorizontalSpeed;
    
    //    horizontalSpeed = this->pos.x - this->oldPos.x;
}

template <class T>
        PlayerController<T>::PlayerController() :
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
        PlayerController<T>::PlayerController(Vector2<T> _pos, T _xw, T _yw, int scr, int sprn):
        AABB<T>(_pos, _xw, _yw)
        //        SpriteController(scr, sprn)
{
    //    horizontalSpeed = verticalSpeed = 0;
    //    //    acceleration = 0;
    //    verticalAcceleration = 0;
    //    //    breaking = 50;
    //    verticalBreaking = 50;
    //    jumpTime = -100;
}

//void PlayerController::isRunning(bool playerState)
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
        void PlayerController<T>::accelerateLeft()
{
    //    acceleration = -0.1f;
    //    breaking = 50;
    //    if ( running )
    //        modifySpeed(horizontalSpeed, horizontalDelta, maxHorizontalRunningSpeed, horizontalRunningSpeedStep, -1);
    //    else
    //        modifySpeed(horizontalSpeed, horizontalDelta, maxHorizontalSpeed, horizontalSpeedStep, -1);
    asm("mov r11,r11");
    this->pos.x -= horizontalSpeedStep;
}

template <class T>
        void PlayerController<T>::accelerateRight()
{
    //    if ( running )
    //        modifySpeed(horizontalSpeed, horizontalDelta, maxHorizontalRunningSpeed, horizontalRunningSpeedStep, 1);
    //    else
    //        modifySpeed(horizontalSpeed, horizontalDelta, maxHorizontalSpeed, horizontalSpeedStep, 1);
    this->pos.x += horizontalSpeedStep;
}

//void PlayerController::accelerateUp(int timer)
//{
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
//}
//
//void PlayerController::applyGravity()
//{
//    //    verticalAcceleration = 1;
//    //    verticalBreaking = 5;
//    if( verticalSpeed < maxVerticalSpeed ) {
//        verticalSpeed += verticalSpeedStep;
//    }
//}
//
//void PlayerController::applyFriction()
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
//void PlayerController::horizontalAnimation(int horizontalSpeed)
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
template <class T>
        T PlayerController<T>::getHorizontalSpeed()
{
    //    horizontalAnimation(horizontalSpeed);
    //    //    horizontalSpeed += acceleration - (horizontalSpeed) / breaking;
    //
    //    //    acceleration = 0;
    //    //    breaking = 10;
    //
    //    return int(horizontalSpeed);
    return this->pos.x - this->oldPos.x;
}
//
//int PlayerController::getVerticalSpeed(int timer)
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
template <class T>
        bool PlayerController<T>::isCenteredOnScreen()
{
    if ( fabs(this->pos.x - ((screenMaxX-screenMinX)/2 - this->xw)) < eps )
        return true;
    return false;
}
////
template <class T>
        T PlayerController<T>::centerOnScreen()
{
    T px;

    px = this->pos.x + this->xw - ((screenMaxX-screenMinX)/2);
    T speed = this->pos.x - this->oldPos.x;

    if ( px > 0 )
    {
        //T dist;
        //dist = this->pos.x - ((screenMaxX-screenMinX)/2);
        this->pos.x = (screenMaxX-screenMinX)/2 - this->xw;
        this->oldPos.x = this->pos.x - speed;
//
        return speed;
        // -x, 0, -1, 0
    }
//    //    int x = pos.x;
//    //
//    if ( this->pos.x > (screenMaxX-screenMinX)/2.0 )
//        this->pos.x = ((screenMaxX-screenMinX)/2.0);
//
//
//    //    if ( speed >= dist )
//    //    {
//    //        ret = speed - dist;
//    //        this->pos.x = ((screenMaxX-screenMinX)/2 - this->xw*2);
//    //    }
//    //    else
//    //    {
//    //        ret = 0;
//    //        this->pos.x += speed;
//    //    }
//    //    this->oldPos.x = this->pos.x - speed;
//
    return 0;
}
//
template <class T>
T PlayerController<T>::uncenterOnScreen(int scroll)
{
//    int x = pos.x;
//
    if ( scroll > 0 )
    {
        asm("mov r11, r11");
        T speed = this->pos.x - this->oldPos.x;
        this->pos.x = (screenMaxX-screenMinX)/2 - this->xw;
        this->oldPos.x = this->pos.x - speed;

        return speed;
    }
//
//    x = speed+x;
//    if ( x <= 0 )
//        x = 0;
//
//    pos.x = x;
//
    return 0;
}

#endif // PLAYERCONTROLLER_H
