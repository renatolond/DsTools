#include "playercontroller.h"

PlayerController::PlayerController() :
        SpriteController()
{
    horizontalSpeed = verticalSpeed = 0;
    //acceleration = 0;
    verticalAcceleration = 0;
    //    breaking = 50;
    verticalBreaking = 50;
    jumpTime = -100;
}

PlayerController::PlayerController(int scr, int sprn) :
        SpriteController(scr, sprn)
{
    horizontalSpeed = verticalSpeed = 0;
    //    acceleration = 0;
    verticalAcceleration = 0;
    //    breaking = 50;
    verticalBreaking = 50;
    jumpTime = -100;
}

void PlayerController::isRunning(bool playerState)
{
    running = playerState;
}

void PlayerController::accelerateLeft()
{
    //    acceleration = -0.1f;
    //    breaking = 50;
    if ( running )
    {
        if ( horizontalSpeed > -maxHorizontalRunningSpeed )
        {
            horizontalSpeed -= horizontalRunningSpeedStep;
            horizontalDelta = -1;
        }
        else
            horizontalDelta = 0;
    }
    else
    {
        if ( horizontalSpeed > -maxHorizontalSpeed )
        {
            horizontalSpeed -= horizontalSpeedStep;
            horizontalDelta = -1;
        }
        else
            horizontalDelta = 0;
    }
}

void PlayerController::accelerateRight()
{
    if ( running )
    {
        if ( horizontalSpeed < maxHorizontalRunningSpeed )
        {
            horizontalSpeed += horizontalRunningSpeedStep;
            horizontalDelta = 1;
        }
        else
            horizontalDelta = 0;
    }
    else
    {
        if ( horizontalSpeed < maxHorizontalSpeed )
        {
            horizontalSpeed += horizontalSpeedStep;
            horizontalDelta = 1;
        }
        else
            horizontalDelta = 0;
    }
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
}

void PlayerController::applyGravity()
{
    verticalAcceleration = 1;
    verticalBreaking = 5;
}

void PlayerController::applyFriction()
{
    if ( fabs(horizontalSpeed) < horizontalSpeedStep )
        horizontalSpeed = 0;

    if ( horizontalSpeed > maxHorizontalSpeed )
        horizontalSpeed -= horizontalRunningSpeedStep;
    else if ( horizontalSpeed < -maxHorizontalSpeed )
        horizontalSpeed += horizontalRunningSpeedStep;
    else if ( horizontalSpeed > horizontalSpeedStep )
        horizontalSpeed -= horizontalSpeedStep;
    else if ( horizontalSpeed < -horizontalSpeedStep )
        horizontalSpeed += horizontalSpeedStep;

}

int PlayerController::getHorizontalSpeed()
{
    //    horizontalSpeed += acceleration - (horizontalSpeed) / breaking;

    if ( abs(horizontalSpeed) > eps )
    {
        if ( horizontalDelta * horizontalSpeed < 0 )
        {
            beginAnimation(1);
            if ( horizontalSpeed > 0 )
                hflip(1);
            else
                hflip(0);
        }
        else
        {
            beginAnimation(0);
            if ( horizontalSpeed > 0 )
                hflip(0);
            else
                hflip(1);
        }
    }
    else
    {
        stopAnimation();
    }

    //    acceleration = 0;
    //    breaking = 10;

    return int(horizontalSpeed);
}

int PlayerController::getVerticalSpeed()
{
    verticalSpeed += verticalAcceleration - (verticalSpeed) / verticalBreaking;

    if ( pos.y > screenSizeY+sizeY ) pos.y = -sizeY;

    if ( pos.y >= (screenSizeY-(3*tileSizeY)-sizeY) && verticalSpeed > 0)
    {
        verticalSpeed = 0;
        verticalAcceleration = 0;
        verticalBreaking = 10.0f;
    }

    return int(verticalSpeed);
}

bool PlayerController::isCenteredOnScreen()
{
    int x = pos.x;

    if ( x == (screenSizeX/2 - sizeX) )
        return true;
    return false;
}

int PlayerController::centerOnScreen(int speed)
{
    int x = pos.x;

    int dist = (screenSizeX/2 - sizeX) - x;
    if ( speed >= dist )
    {
        speed = speed - dist;
        x = (screenSizeX/2 - sizeX);
        pos.x = x;
    }
    else
    {
        x = speed+x;
        speed = 0;
        pos.x = x;
    }

    return speed;
}

int PlayerController::uncenterOnScreen(int speed, int scroll)
{
    int x = pos.x;

    if ( scroll > 0 )
        return speed;

    x = speed+x;
    if ( x <= 0 )
        x = 0;

    pos.x = x;

    return 0;
}
