#ifndef SPRITECONTROLLER_H
#define SPRITECONTROLLER_H

#include <PA9.h>
#include <vector>

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
public:
    SpriteController();
    SpriteController(int scr, int sprn);
    void addAnimation(int start, int end, int baseVelocity);
    void beginAnimation(int index);
    void stopAnimation();
private:
    std::vector<anim> animations;
    int currentAnimation;
};

#endif // SPRITECONTROLLER_H
