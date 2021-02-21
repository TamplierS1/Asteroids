#include "Bullet.h"

Bullet::Bullet(olc::vf2d pos, olc::vf2d velocity, float playerAngle, olc::Pixel color)
{
    mPos = pos;
    mVelocity = velocity;
    mAngle = playerAngle;
    mColor = color;
    // NOTICE: all other unititialized Actor member variables does not matter, we will not use them
}

void Bullet::MoveBullet(float fElapsedTime)
{
    mPos.x += mVelocity.x * sin(mAngle) * fElapsedTime;
    mPos.y += mVelocity.y * cos(mAngle) * fElapsedTime;
}

bool Bullet::Collision(unsigned int width, unsigned int height)
{
    bool collisionX = mPos.x < 0.0f || mPos.x > width;
    bool collisionY = mPos.y < 0.0f || mPos.y > height;

    return collisionX || collisionY;
}