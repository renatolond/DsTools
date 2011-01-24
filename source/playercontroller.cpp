#include "playercontroller.h"

PlayerController::PlayerController() :
        SpriteController()
{
    horizontalSpeed = verticalSpeed = 0;
    acceleration = 0;
    verticalAcceleration = 0;
    breaking = 50;
    verticalBreaking = 50;
    jumpTime = -100;
}

PlayerController::PlayerController(int scr, int sprn) :
        SpriteController(scr, sprn)
{
    horizontalSpeed = verticalSpeed = 0;
    acceleration = 0;
    verticalAcceleration = 0;
    breaking = 50;
    verticalBreaking = 50;
    jumpTime = -100;
}

void PlayerController::isRunning(bool playerState)
{
    running = playerState;
}

void PlayerController::accelerateLeft()
{
    acceleration = -0.1f;
    breaking = 50;
}

void PlayerController::accelerateRight()
{
    acceleration = 0.1f;
    breaking = 50;
}

void PlayerController::accelerateUp(int timer)
{
    if ( abs(verticalSpeed) < eps && abs(verticalAcceleration) < eps )
    {
        verticalSpeed = -5;
        jumpTime = timer;
    }
    else if ( timer - jumpTime < 250 )
    {
        verticalSpeed = -5;
    }
    PA_OutputText(1, 1, 6, "jumpTime vs Time: %d %d",jumpTime, timer);
}

void PlayerController::applyGravity()
{
    verticalAcceleration = 1;
    verticalBreaking = 5;
}

int PlayerController::getHorizontalSpeed()
{
    horizontalSpeed += acceleration - (horizontalSpeed) / breaking;

    if ( abs(horizontalSpeed) > eps )
    {
        beginAnimation(0);
        if ( horizontalSpeed > 0 )
            hflip(0);
        else
            hflip(1);
    }
    else
    {
        stopAnimation();
    }

    acceleration = 0;
    breaking = 10;

    return int(horizontalSpeed);
}

int PlayerController::getVerticalSpeed()
{
    verticalSpeed += verticalAcceleration - (verticalSpeed) / verticalBreaking;

    if ( pos.y > 192+sizeY ) pos.y = -sizeY;

    if ( pos.y > 168-sizeY && verticalSpeed > 0)
    {
        verticalSpeed = 0;
        verticalAcceleration = 0;
        verticalBreaking = 10.0f;
    }

    return int(verticalSpeed);
}
