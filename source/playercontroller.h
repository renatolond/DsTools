#ifndef PLAYERCONTROLLER_H
#define PLAYERCONTROLLER_H

#include "spritecontroller.h"

#define eps 0.0001f

class PlayerController : public SpriteController
{
    double acceleration;
    double breaking;
    double verticalAcceleration;
    double verticalBreaking;
    double horizontalSpeed;
    double verticalSpeed;
    bool running;
    int jumpTime;
public:
    PlayerController();
    PlayerController(int scr, int sprn);
    void isRunning(bool playerState);
    void accelerateLeft();
    void accelerateRight();
    void accelerateUp(int timer);
    void applyGravity();
    int getHorizontalSpeed();
    int getVerticalSpeed();
};

#endif // PLAYERCONTROLLER_H