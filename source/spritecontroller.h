#ifndef SPRITECONTROLLER_H
#define SPRITECONTROLLER_H

#include <PA9.h>
#include <vector>

#include "constants.h"

struct anim
{
    int start;
    int end;
    int baseVelocity;
    anim(int s, int e, int bv):
	    start(s), end(e), baseVelocity(bv)
    {
    }
};

class SpriteController : public PA::Sprite
{
protected:
    int sizeX;
    int sizeY;
public:
    SpriteController();
    SpriteController(int scr, int sprn);
    void addAnimation(int start, int end, int baseVelocity);
    void beginAnimation(int index);
    inline void create(void* gfx, int shape, int size, int paln){
        PA::Sprite::create(gfx, shape, size, paln);
        sizeX = sizeY = 0;
        if ( shape == 0 )
        {
            if ( size == 0 )
                sizeX = sizeY = 8;
            if ( size == 1 )
                sizeX = sizeY = 16;
            if ( size == 2 )
                sizeX = sizeY = 32;
            if ( size == 3 )
                sizeX = sizeY = 64;
        }
    }
    inline void create(u16 gfx, int shape, int size, int paln)
    {
        PA::Sprite::create(gfx, shape, size, paln);
        sizeX = sizeY = 0;
        if ( shape == 0 )
        {
            if ( size == 0 )
                sizeX = sizeY = 8;
            if ( size == 1 )
                sizeX = sizeY = 16;
            if ( size == 2 )
                sizeX = sizeY = 32;
            if ( size == 3 )
                sizeX = sizeY = 64;
        }
    }

    void stopAnimation();
private:
    std::vector<anim> animations;
    int currentAnimation;
};

#endif // SPRITECONTROLLER_H
