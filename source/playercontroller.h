#ifndef PLAYERCONTROLLER_H
#define PLAYERCONTROLLER_H

#include "spritecontroller.h"

#include <cmath>

#define eps 0.0001f

class PlayerController : public SpriteController
{
//    double acceleration;
//    double breaking;
    double verticalAcceleration;
    double verticalBreaking;
    double horizontalSpeed;
    double verticalSpeed;
    int horizontalDelta;
    bool running;
    int jumpTime;
    bool jumping;
public:
    PlayerController();
    PlayerController(int scr, int sprn);
    void isRunning(bool playerState);
    bool isCenteredOnScreen();
    int centerOnScreen(int speed);
    int uncenterOnScreen(int speed, int scroll);
    void accelerateLeft();
    void accelerateRight();
    void accelerateUp(int timer);
    void applyGravity();
    void applyFriction();
    int getHorizontalSpeed();
    int getVerticalSpeed(int timer);
    void horizontalAnimation(int horizontalSpeed);
    void ceaseMovement() { verticalSpeed = horizontalSpeed = 0; }
};

#endif // PLAYERCONTROLLER_H
