#include "playercontroller.h"

PlayerController::PlayerController() :
        SpriteController()
{
    horizontalSpeed = verticalSpeed = 0;
    //acceleration = 0;
    verticalAcceleration = 0;
    //    breaking = 50;
    verticalBreaking = 50;
    jumpTime = 0;
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

void PlayerController::accelerateLeft()
{
    //    acceleration = -0.1f;
    //    breaking = 50;
    if ( running )
        modifySpeed(horizontalSpeed, horizontalDelta, maxHorizontalRunningSpeed, horizontalRunningSpeedStep, -1);
    else
        modifySpeed(horizontalSpeed, horizontalDelta, maxHorizontalSpeed, horizontalSpeedStep, -1);
}

void PlayerController::accelerateRight()
{
    if ( running )
        modifySpeed(horizontalSpeed, horizontalDelta, maxHorizontalRunningSpeed, horizontalRunningSpeedStep, 1);
    else
        modifySpeed(horizontalSpeed, horizontalDelta, maxHorizontalSpeed, horizontalSpeedStep, 1);
}

void PlayerController::accelerateUp(int timer)
{
    if ( fabs(verticalSpeed) > eps )
        return;

    if ( timer - jumpTime < jumpDelay )
        return;

    jumping = true;

    beginAnimation(2);

    int jumpHeight = 7*tileSizeY;
    verticalSpeed = -15;
    verticalSpeed += (screenSizeY-jumpHeight)/100*3.75;
    if ( horizontalSpeed >= maxHorizontalSpeed ) verticalSpeed += (horizontalSpeed - maxHorizontalSpeed)/20;
}

void PlayerController::applyGravity()
{
    //    verticalAcceleration = 1;
    //    verticalBreaking = 5;
    if( verticalSpeed < maxVerticalSpeed ) {
        verticalSpeed += verticalSpeedStep;
    }
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

void PlayerController::horizontalAnimation(int horizontalSpeed)
{
    if ( !jumping )
    {
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
    }

}

int PlayerController::getHorizontalSpeed()
{
    horizontalAnimation(horizontalSpeed);
    //    horizontalSpeed += acceleration - (horizontalSpeed) / breaking;

    //    acceleration = 0;
    //    breaking = 10;

    return int(horizontalSpeed);
}

int PlayerController::getVerticalSpeed(int timer)
{
    //    verticalSpeed += verticalAcceleration - (verticalSpeed) / verticalBreaking;
    //
    //    if ( pos.y > screenSizeY+sizeY ) pos.y = -sizeY;

    if ( pos.y+(int)verticalSpeed > (screenSizeY-(3*tileSizeY)-sizeY) )
    {
        horizontalAnimation(horizontalSpeed);
        if ( verticalSpeed > verticalSpeedStep*2 )
        {
            jumping = false;
            jumpTime = timer;
        }
        verticalSpeed = 0;
        verticalAcceleration = 0;
        verticalBreaking = 10.0f;
        pos.y = (screenSizeY-(3*tileSizeY)-sizeY);
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
