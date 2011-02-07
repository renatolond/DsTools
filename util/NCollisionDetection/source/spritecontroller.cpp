#include "spritecontroller.h"

SpriteController::SpriteController() :
	Sprite()
{
    currentAnimation = -1;
}

SpriteController::SpriteController(int scr, int sprn) :
    Sprite(scr, sprn)
{
    currentAnimation = -1;
}

void SpriteController::addAnimation(int start, int end, int baseVelocity)
{
    animations.push_back(anim(start,end,baseVelocity));
}

void SpriteController::beginAnimation(int index)
{
    if ( currentAnimation == index ) return;
    anim a = animations[index];
    startanim(a.start,a.end,a.baseVelocity,ANIM_UPDOWN);
    currentAnimation = index;
}

void SpriteController::stopAnimation()
{
    currentAnimation = -1;
    stopanim();
    frame(0);
}

