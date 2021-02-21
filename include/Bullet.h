#pragma once

#include "Actor.h"

class Bullet : public Actor
{
public:
    Bullet(olc::vf2d pos, olc::vf2d velocity, float playerAngle, olc::Pixel color);

    void MoveBullet(float fElapsedTime);
    bool Collision(unsigned int width, unsigned int height);

private:
    // specifies the angle at which the bullet should be shot
    float mAngle;
};
